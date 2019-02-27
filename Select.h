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
	private:
		string selectString;
		string connectionString;
		result R;
		int returnStringSize;


};
