#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class Select{
	public:
		Select(string  selectParams);
		void setConnectionParameters(string dbname,string account, string password,string endpoint, int port);
		void queryDatabase();
        int dataSize(result r);//show datasize
        void uniqueData(result r);//show unique data
        string *resultString(result r);//store data into string array
        int selectFunctions(result r,int selectFunctionNumber);//function selection.
    
	private:
		string selectString;
		string connectionString;
		

};
