#ifndef DRIVE_QUERY
#define DRIVE_QUERY

#include "textquery.h"
#include "querybase.h"
#include "query_Interface.h"
#include "algorithm"

/*
 *基础的查询类，完成最简单的查询
 *
 */

class WordQuery:public QueryBase{
    friend Query;
    WordQuery(const string& str):sear_str(str){}
    QueryResult eval(TextQuery&) const override;
    string rep() const override;
    string sear_str;
};

/*
 * 在定义完成WordQuery之后才可以定义接口类的string类型的构造函数
 * 声明为const类型可以完成类似Query("dong")这样的构造
 */

inline
Query::Query(const string &str):quer_ptr(new WordQuery(str)){}



class NotQuery:public QueryBase{
    friend Query operator ~(const Query &);
    NotQuery(const Query &item):query(item){}
    QueryResult eval(TextQuery&) const override;
    string rep() const override;
    Query query;
};


class BinaryQuery:public QueryBase{
protected:
    BinaryQuery()=default;
    BinaryQuery(const Query& l,const Query& r,char fg):lhs(l),rhs(r),flag(fg){}
    string rep() const override;
    Query lhs;
    Query rhs;
    char flag; //二元运算符号
};


class AndQuery:public BinaryQuery{
    friend Query operator &(const Query &lhs,const Query &rhs);
    AndQuery(const Query &l,const Query &r):BinaryQuery(l,r,'&'){}
    QueryResult eval(TextQuery &) const override;
};

class OrQuery:public BinaryQuery{
    friend Query operator |(const Query &lhs,const Query &rhs);
    OrQuery(const Query &l,const Query &r):BinaryQuery(l,r,'|'){}
    QueryResult eval (TextQuery &) const override;
};



#endif // DRIVE_QUERY

