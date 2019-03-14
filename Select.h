#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class Select{
public:
    Select(string  selectParams);
    void setConnectionParameters(string dbname,string account, string password,string endpoint, int port);
    void queryDatabase();
    int dataSize();//show datasize
    void uniqueData();//show unique data
    string *resultString();//store data into string array
    int selectFunctions(int selectFunctionNumber);//function selection.
    double averageDuration();
    float averagePatients();
    float pscore();
    int *numberOfShift();
private:
    string selectString;
    string connectionString;
    result R;
    int returnStringSize;
    
    
};
