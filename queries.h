#include <pqxx/pqxx>

//Query class provides a number of set and hardcoded db queries
using namespace std;
 class Query{
public:
	static double averageDuration(string username);
	static float averagePatients(string username);
	static float pscore(string username);
	static int *numberOfShift();
    static int numberOfNurse();
    static int qualification(string username);
    static string *nurseList();
private:



};
