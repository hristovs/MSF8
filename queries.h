#include <pqxx/pqxx>
#include <tuple>
//Query class provides a number of set and hardcoded db queries
using namespace std;
 class Query{
public:
	static double averageDuration(string username);
	static float averagePatients(string username);
	static float pscore(string username);
	static int *numberOfShift();
   // static int numberOfNurse();
    static int qualification(string username);
    static std::tuple<int, string *> nurseList();
    static int amountOfBreaks(string username);
    static double breaksAsTimePercentage(string username);
    static std::tuple<int, string*> uniqueEvents();

private:
	static bool isPresent(string *array, int size, string checkPresent);


};
