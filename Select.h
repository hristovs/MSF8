#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class Select{
public:
    Select(string  selectParams);
    ~Select(){delete &selectString;}
    int dataSize();
    void setConnectionParameters(string dbname,string account, string password,string endpoint, int port);
    void queryDatabase();
    void uniqueData();//show unique data
    string *resultString();//store data into string array
   // int selectFunctions(int selectFunctionNumber);//function selection.
    result returnResult();
private:
    string selectString;
    string connectionString;
    result R;
    int returnStringSize;
    
    
};
