#ifndef __TEXT_QUERY_H__
#define __TEXT_QUERY_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <map>

using namespace std;
class TextQuery {
public:
    typedef std::vector<std::string>::size_type line_no;

    /* 从指定文件加载，导入内存 */
    void read_file(std::ifstream &is)
    {
        store_file(is);
        build_map();
    }

    std::set<line_no> run_query(const std::string&) const;
    std::string text_line(line_no) const;

private:
    void store_file(std::ifstream&);
    void build_map();

    std::vector<std::string> lines_of_text;
    std::map< std::string, std::set<line_no> > word_map;
};

class Query_base {
    friend class Query;
protected:
    typedef TextQuery::line_no line_no;
    virtual ~Query_base() { }
private:
    // eval returns the |set| of lines that this Query matches
    virtual std::set<line_no> eval(const TextQuery&) const = 0;
    // display prints the query
    virtual std::ostream& display(std::ostream& = std::cout) const = 0;
};
class Query {
    // these operators need access to the Query_base* constructor
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);

public:
    Query(const std::string&);
    Query(const Query &c): q(c.q), use(c.use) {
        ++*use;
    }

    ~Query() {
        decr_use();
    }

    Query& operator=(const Query&);

    // interface functions: will call corresponding Query_base operations
    std::set<TextQuery::line_no> eval(const TextQuery &t) const {
        return q->eval(t);
    }

    std::ostream &display(std::ostream &os) const {
        return q->display(os);
    }


private:
    Query(Query_base *query): q(query), use(new std::size_t(1)) { }

    Query_base *q;
    std::size_t *use;

    void decr_use() {
        if (--*use == 0) {
            delete q;
            delete use;
        }
    }
};

inline std::ostream& operator << (std::ostream &os, const Query &q)
{
    return q.display(os);
}

class WordQuery: public Query_base {
    friend class Query; // Query uses the WordQuery constructor
    WordQuery(const std::string &s): query_word(s) {}
    // concrete class: WordQuery defines all inherited pure virtual functions

    std::set<line_no> eval(const TextQuery &t) const {
        return t.run_query(query_word);
    }

    std::ostream& display (std::ostream &os) const {
        return os << query_word;
    }

    std::string query_word; // word for which to search
};

class NotQuery: public Query_base {
    friend Query operator~(const Query &);

    NotQuery(Query q) : query(q) {}

    // concrete class: NotQuery defines all inherited pure virtual functions
    std::set <line_no> eval(const TextQuery &) const;

    std::ostream &display(std::ostream &os) const {
        return os << "~(" << query << ")";
    }

    const Query query;
};

class BinaryQuery: public Query_base {
protected:
    BinaryQuery(Query left, Query right, std::string op): lhs(left), rhs(right), oper(op) { }
    // abstract class: BinaryQuery doesn't define eval
    std::ostream& display(std::ostream &os) const {
        return os << "(" << lhs << " " << oper << " "
                << rhs << ")";
    }

    const Query lhs, rhs; // right- and left-hand operands
    const std::string oper; // name of the operator
};

class AndQuery: public BinaryQuery {
    friend Query operator&(const Query&, const Query&);

    AndQuery (Query left, Query right) : BinaryQuery(left, right, "&") { }
    // concrete class: And Query inherits display and definesn remaining pure virtual
    std::set<line_no> eval(const TextQuery&) const;
};

class OrQuery: public BinaryQuery {
    friend Query operator|(const Query&, const Query&);

    OrQuery(Query left, Query right) : BinaryQuery(left, right, "|") { }
    // concrete class: OrQuery inherits display and defines remaining pure virtual
    std::set<line_no> eval(const TextQuery&) const;
};


inline Query operator & (const Query &lhs, const Query &rhs) {
    return new AndQuery(lhs, rhs);
}

inline Query operator | (const Query &lhs, const Query &rhs) {
    return new OrQuery(lhs, rhs);
}

inline Query operator ~ (const Query &oper) {
    return new NotQuery(oper);
}

// returns union of its operands' result sets
set<TextQuery::line_no>
OrQuery::eval(const TextQuery& file) const
{
    // virtual calls through the Query handle to get result sets for the operands
    set<line_no> right = rhs.eval(file), ret_lines = lhs.eval(file);
    ret_lines.insert(right.begin(), right.end());
    return ret_lines;
}

// returns intersection of its operands' result sets
set<TextQuery::line_no>
AndQuery::eval(const TextQuery& file) const
{
// virtual calls through the Query handle to get result sets for the operands
    set<line_no> left = lhs.eval(file),
            right = rhs.eval(file);
    set<line_no> ret_lines; // destination to hold results

    set_intersection(left.begin(), left.end(), right.begin(), right.end(),
            inserter(ret_lines, ret_lines.begin()));
    return ret_lines;
}

set<TextQuery::line_no>
NotQuery::eval(const TextQuery& file) const
{
    // virtual call through the Query handle to eval
    set<TextQuery::line_no> has_val = query.eval(file);
    set<line_no> ret_lines;
    // for each line in the input file, check whether that line is in has_val
    // if not, add that line number to ret_lines
    for (TextQuery::line_no n = 0; n != 1/*file.size()*/; ++n)
        if (has_val.find(n) == has_val.end())
            ret_lines.insert(n);
    return ret_lines;
}
#endif //__TEXT_QUERY_H__