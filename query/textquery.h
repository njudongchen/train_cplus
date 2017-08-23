#ifndef TEXTQUERY_H
#define TEXTQUERY_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <memory>
#include <iostream>


using std::vector;
using std::string;
using std::ifstream;
using std::set;
using std::map;
using std::shared_ptr;
using std::ostream;
using std::cout;
using std::endl;

class QueryResult;

class TextQuery
{
    friend QueryResult;
public:
    using line_no=vector<string>::size_type;
    TextQuery(ifstream&);
    TextQuery()=default;
    QueryResult query(string word) const;
private:
    shared_ptr<vector<string>> content;
    shared_ptr<map<string,shared_ptr<set<line_no>>>> string_num_map;
};


/*
 * 保存查询后的结果
 */

class QueryResult
{
    friend ostream& operator <<(ostream& os,const QueryResult& res);
public:
    using line_no=vector<string>::size_type;
    QueryResult() {}
    shared_ptr<vector<string>> get_file() const
    {
        return result_content;
    }
    set<line_no>::iterator begin()
    {
        return result_set->begin();
    }
    set<line_no>::iterator end()
    {
        return result_set->end();
    }
    line_no size()
    {
        return result_set->size();
    }

    QueryResult(shared_ptr<vector<string>> ptr,string str,shared_ptr<set<line_no>>& res):
                result_content(ptr),out_str(str),result_set(res){}
private:
    shared_ptr<vector<string>> result_content;
    string out_str;
    shared_ptr<set<line_no>> result_set;
};


#endif // TEXTQUERY_H
