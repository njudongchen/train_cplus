#include "drive_query.h"


QueryResult WordQuery::eval(TextQuery &file) const
{
    return file.query(sear_str);
}

inline
string WordQuery::rep() const
{
    return sear_str;
}



QueryResult NotQuery::eval(TextQuery &text) const
{
    auto not_set=std::make_shared<set<line_no>>();
    QueryResult temp=query.eval(text);
    auto nz=temp.get_file()->size();
    auto begin=temp.begin();
    auto end=temp.end();
    for(unsigned int i=0;i<nz;++i)
    {
        if(begin!=end&&*begin==i)
        {
            ++begin;
        }
        else
        {
            not_set->insert(i);
        }
    }
    return QueryResult(temp.get_file(),rep(),not_set);
}

inline
string NotQuery::rep() const
{
    return "(~"+query.rep()+")";
}

inline
string BinaryQuery::rep() const
{
    return "("+lhs.rep()+flag+rhs.rep()+")";
}

QueryResult AndQuery::eval(TextQuery &text) const
{
    QueryResult l_res=lhs.eval(text);
    QueryResult r_res=rhs.eval(text);
    auto sum_set=std::make_shared<set<line_no>>();
    std::set_intersection(l_res.begin(),l_res.end(),
                             r_res.begin(),r_res.end(),
                             inserter(*sum_set,sum_set->begin()));
    return QueryResult(l_res.get_file(),rep(),sum_set);
}


QueryResult OrQuery::eval(TextQuery &text) const
{
    QueryResult l_res=lhs.eval(text);
    QueryResult r_res=rhs.eval(text);
    auto sum_set=std::make_shared<set<line_no>>();
    std::set_union(l_res.begin(),l_res.end(),
                             r_res.begin(),r_res.end(),
                             inserter(*sum_set,sum_set->begin()));
    return QueryResult(l_res.get_file(),rep(),sum_set);
}


Query operator &(const Query& lhs,const Query& rhs)
{
    return shared_ptr<QueryBase> (new AndQuery(lhs,rhs));

}

Query operator |(const Query& lhs,const Query& rhs)
{
    return shared_ptr<QueryBase>(new OrQuery(lhs,rhs));
}


Query operator ~(const Query& item)
{
   return shared_ptr<QueryBase>(new NotQuery(item));
}
