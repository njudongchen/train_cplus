#include "textquery.h"
#include <sstream>

using std::istringstream;

/*
 * 将一个文件中每一个单词对应的行号放到一个set中，
 * 再讲单词和set的对应关系放到一个map中
 * 注意去掉单词后面的标点符号
 */



TextQuery::TextQuery(std::ifstream &fin)
{
    content=std::make_shared<vector<string>>();
    string_num_map=std::make_shared<map<string,shared_ptr<set<line_no>>>>();
    string str;
    line_no line_num=0;
    while(getline(fin,str))
    {
        content->push_back(str);
        istringstream streamstr(str);
        string line_str;
        while(streamstr>>line_str)
        {
          char ch=line_str[line_str.size()-1];
          if(ch<'A'||ch>'z'||(ch>'Z'&&ch<'a'))
              line_str.erase(line_str.end()-1,line_str.end());
          auto &set_iter=(*string_num_map)[line_str];
          if(!set_iter)
              set_iter.reset(new set<line_no>{line_num});
          set_iter->insert(line_num);
        }
        ++line_num;
    }
}

/*
 * 负责具体查询某一个单词
 * 注意如果没有查询到也需要生成一个空的set，而不是一个空指针
 */

QueryResult TextQuery::query(string word) const
{
    shared_ptr<set<line_no>> result_set=std::make_shared<set<line_no>>(); //生成一个空的set
    if(string_num_map!=NULL)
    {
        if(string_num_map->find(word)!=string_num_map->end())
            result_set=(*string_num_map)[word];
    }
    QueryResult res(content,word,result_set);
    return res;
}

ostream& operator<<(ostream &os,const QueryResult& res)
{
    os<<res.out_str<<" occurs "<<res.result_set->size()<<" times "<<endl;
    for(auto c:*(res.result_set))
    {
        os<<'\t'<<"(line "<<c+1<<")"<<(*res.result_content)[c]<<endl;
    }
    return os;
 }

