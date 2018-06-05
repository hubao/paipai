//
// Created by hubao on 2018/4/1.
//

#ifndef MYACCOUNT_CHA14_OVERRIDEOPERATOR_H
#define MYACCOUNT_CHA14_OVERRIDEOPERATOR_H

#ifdef NORMAL_OVERRIDE          //普通重载
    class Sales_item {
    public:
        // 构造函数
        Sales_item(){}
        Sales_item(const Sales_item &rhs) :
                isbn(rhs.isbn),
                units_sold(rhs.units_sold),
                revenue(rhs.revenue) {}

        ~Sales_item() {}


        // 赋值操作符（=)
        Sales_item& operator=(const Sales_item& rhs)
        {
            isbn = rhs.isbn;
            units_sold = rhs.units_sold;
            revenue = rhs.revenue;

            return *this;
        }

        // 复合赋值操作符（+=、-=、*=、/=）
        Sales_item& operator+=(const Sales_item& rhs)
        {
            isbn += rhs.isbn;
            units_sold += rhs.units_sold;
            revenue += rhs.revenue;

            return *this;
        }

    private:
        std::string     isbn;
        unsigned int    units_sold;
        double          revenue;
    };

    /// 输入、输出操作符 (>>、<<)
    istream& operator>>(istream& lhs, Sales_item& rhs)
    {
        //⚠️ 1. 任何读操作都可能因为提供的值不正确而失败 2. 任何读入都可能碰到输入流中的文件结束或其他一些错误
        //重载输入操作符时，应该对输入进行检查（只需要在使用前检查一次，因为输入操作只要有一个错误，流状态将为false）
        double price;
        lhs >> rhs.isbn >> rhs.units_sold >> price;

        if(lhs)
            rhs.revenue = rhs.units_sold * price;
        else
            rhs = new Sales_item();

        return lhs;
    }
    ostream& operator<<(ostream& lhs, const Sales_item& rhs)
    {
        //⚠️ 一般而言，输出操作符应输出对象的内容，进行最小限度的格式化，它们不应该输出换行符。
        lhs << rhs.isbn << "\t"
            << rhs.units_sold << "\t"
            << rhs.revenue;
        return lhs;
    }


    /// 算术操作符（+、-、*、/)
    Sales_item& operator+(const Sales_item& lhs, const Sales_item& rhs)
    {
        Sales_item ret(lhs);

        //⚠️ 1.使用复合赋值操作符实现 2. 为了于内置+操作符一致，返回右值而非引用
        ret += rhs;
        return ret;
    }


    /// 比较操作符（>、>=、<、<=、==、!=), 对于小于等其他操作，因为不同isbn比较意义不大，暂不定义，第15章将给出使用单独的命名函数来比较
    bool operator==(const Sales_item& lhs, const Sales_item& rhs)
    {
        if(lhs.isbn == rhs.isbn
           && lhs.units_sold == rhs.units_sold
           && lhs.revenue == rhs.revenue){
            return true;
        }

        return false;
    }
    bool operator!=(const Sales_item& lhs, const Sales_item& rhs)
    {
        return !(lhs == rhs);
    }
#endif

#ifdef SPEC_OVERRIDE_INDEX      //特殊重载 - 下标操作符
    /// 下标操作常用于容器类 ([])
    class Foo {
    public:
        int &operator[] (const size_t)
        {
            if (data.size() <= size_t)
                throw out_of_range("越界");

            return data[size_t];
        }

        const int &operator[] (const size_t) const
        {
            if (data.size() <= size_t)
                throw out_of_range("越界");

            return data[size_t];
        }
    private:
        vector<int> data;
    };
#endif

#ifdef SPEC_OVERRIDE_MEMACCESS  //特殊重载 - 成员访问操作符
    // 成员访问操作符常用于智能指针类 (->、*)
    class Item_base {
    public:
        virtual Item_base* clone() const{
            return new Item_base(*this);
        }
    };

    class Sales_item {
    public:
        // 构造函数
        Sales_item(): p(0), use(new std::size_t(1)) { }
        Sales_item(const Item_base &item) : p(item.clone()), use(new std::size_t(1)) { }
        ~Sales_item() {if (--*use == 0) { delete p; delete use; }}

        /*
         * ⚠️ 拷贝构造申请内存，创建实例
         */
        Sales_item(const Sales_item &i) : p(i.p), use(i.use)
        {
            ++*use;
        }


        /*
         * ⚠️ 赋值操作符使用的时候类的实例已经创建，需要检查是否自身拷贝。
         */
        Sales_item& operator=(const Sales_item& rhs)
        {
            ++*rhs.use;    // 右（操作数）加左（操作数）减，防止自身赋值
            if (--*use == 0) {
                delete p;
                delete use;
            }

            p = rhs.p;     // 赋值
            use = rhs.use;
            return *this;  // 返回左操作数的引用。
        }


        // 重载指针操作符，返回指针，进行动态绑定
        const Item_base *operator->() const {
            if (p) return p;
            else throw std::logic_error("unbound Sales_item");
        }

        // 重载解引用操作符，返回引用，进行动态绑定
        const Item_base &operator*() const {
            if (p) return *p;
            else throw std::logic_error("unbound Sales_item");
        }

    private:
        Item_base *p;        // pointer to shared item
        std::size_t *use;    // pointer to shared use count
    };
#endif

#ifdef SPEC_OVERRIDE_AUTOOPER   //特殊重载 - 自增、自减操作符
    /// 自增、自减操作符常用于迭代器类
    class CheckedPtr{
        CheckedPtr(int* b, int* e) : front(b) , end(e)
        {
            curr = NULL;
        }

        ~CheckedPtr(){}

        /*
         * 补充知识 -- 内置类型自增、自减操作
         * 前自增返回修改以后的值；后自增返回修改之前的值
         * ++i 返回对i加一后的结果，i++ 返回 i，然后对i加一
         */

        // 前自增操作
        // 为了与内置类型前自增操作一致，返回自身引用
        CheckedPtr& operator++()
        {
            if(curr == end){
                throw out_of_range("out of range");
            }
            ++curr;
            return *this;
        }

        // 前自减操作
        // 为了与内置类型前自减操作一致，返回自身引用
        CheckedPtr& operator--()
        {
            if(curr == front){
                throw out_of_range("out of range");
            }
            --curr;
            return *this;
        }

        // 后自增操作
        // 1. 为了与内置类型后自增操作一致，返回拷贝的对象
        // 2. 为了区别前自增，函数增加一个无用形参
        CheckedPtr operator++(int)
        {
            CheckedPtr ret(*this);
            ++*this;
            return ret;
        }

        // 后自减操作
        // 1. 为了与内置类型后自减操作一致，返回拷贝的对象
        // 2. 为了区别前自增，函数增加一个无用形参
        CheckedPtr operator--(int)
        {
            CheckedPtr ret(*this);
            --*this;
            return ret;
        }
    private:
        int *curr;
        int *front;
        int *end;
    };
#endif

#ifdef SPEC_OVERRIDE_CALL       //特殊重载 - 调用操作符
    //调用操作符用于表示操作的类（重载了调用操作符的类被称为函数对象）
    class absInt{
    public:
        int operator()(int value){
            return value > 0 ? value : -value;
        }
    };
#endif

#ifdef SPEC_OVERRIDE_TRANS      //特殊重载 - 转换操作符
    //转换操作符用于希望减少操作符定义的类
    // 如某个叫smallInt的类，希望定义和int类型的所有操作（算术及其对应的复合操作、比较操作共16个）
    // 每个操作的左右操作数分别可由int和smallInt来充当，如 int+smallInt、smallInt+int和smallInt+smallInt，所以总共需要定义48个操作符
    class smallInt{
    public:
        //⚠️ 1.operator后跟要转为的类型 2.不能指定返回类型 3.形参必须为空
        operator int() const{
            return val;
        }
    };
#endif

#endif //MYACCOUNT_CHA14_OVERRIDEOPERATOR_H
