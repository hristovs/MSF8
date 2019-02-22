#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class Select{
public:
    Select(string  selectParams);
    void setConnectionParameters(string dbname,string account, string password,string endpoint, int port);
    string queryDatabase();
    
private:
    string selectString;
    string connectionString;
    string returningString;    
    
};
