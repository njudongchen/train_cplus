#ifndef QUERYBASE_H
#define QUERYBASE_H

#include "textquery.h"
class Query;

/*
 * 虚基类，定义一种查询的方法，需要根据不同的派生类动态的绑定具体的实现
 */


class QueryBase{
    friend Query;
    virtual QueryResult eval(TextQuery&) const=0;
    virtual string rep() const=0;
protected:
    using line_no=vector<string>::size_type;
    virtual ~QueryBase(){};
};



#endif // QUERYBASE_H
