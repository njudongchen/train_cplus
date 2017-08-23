#ifndef QUERY_H
#define QUERY_H

#include "textquery.h"
#include "querybase.h"

/*
 * 接口函数，包含虚基类的指针
 * 对于不同的操作绑定不同的派生类
 */


class Query{
    friend Query operator &(const Query &,const Query &);
    friend Query operator |(const Query &,const Query &);
    friend Query operator ~(const Query &);
public:
    Query()=default;
    Query(const string& str);
    Query(shared_ptr<QueryBase> ptr):quer_ptr(ptr){}
    QueryResult eval(TextQuery& file) const
    {
        return quer_ptr->eval(file);
    }
    string rep() const
    {
        return quer_ptr->rep();
    }

private:
    shared_ptr<QueryBase> quer_ptr;
};



#endif // QUERY_H
