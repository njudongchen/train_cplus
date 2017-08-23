#include <iostream>
#include "textquery.h"
#include "drive_query.h"
#include "query_Interface.h"



using namespace std;

int main()
{
    ifstream fin("/home/dong/Program/query/storyDataFile");
    if(!fin)
    {
        cerr<<"file open fault"<<endl;
    }
    TextQuery file(fin);
    Query que=Query("alive") & ~Query("in");
    cout<<(que).eval(file)<<endl;
    return 0;
}

