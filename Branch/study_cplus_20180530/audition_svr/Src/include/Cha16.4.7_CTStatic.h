//
// Created by hubao on 2018/3/25.
//

#ifndef MYACCOUNT_CHA16_4_7_CLASSTEMPSTATIC_H_H
#define MYACCOUNT_CHA16_4_7_CLASSTEMPSTATIC_H_H

////////////////////////////////////////////////////////////////////
// 类模版的静态成员
////////////////////////////////////////////////////////////////////

template <class T>
class static_class{
public:
    int cmp(const T& ref_l, const T& ref_r){
        if(ref_l == ref_r){
            return 0;
        } else if(ref_l > ref_r){
            return 1;
        } else if(ref_l < ref_r){
            return -1;
        }
    }

public:
    static size_t ms_a;
    static string name;
};

template <class T>
int compare(const T& ref_l, const T& ref_r){
    if(ref_l == ref_r){
        return 0;
    } else if(ref_l > ref_r){
        return 1;
    }
    return -1;
};

/* 类模版的静态成员明确定义 */
template <class T>
size_t static_class<T>::ms_a = 10;
template <class T>
string static_class<T>::name = "hello";



////////////////////////////////////////////////////////////////////
// 类模版的特化版本
////////////////////////////////////////////////////////////////////

template <>
class static_class<char*>{
public:
    int cmp(char* l, char* r){
        return strcmp(l, r);
    }
};

template <>
int compare<const char*>(const char* const& ref_l, const char* const& ref_r){
    return strcmp(ref_l, ref_r);
}
#endif //MYACCOUNT_CHA16_4_7_CLASSTEMPSTATIC_H_H
