#include <pqxx/pqxx>

//Query class provides a number of set and hardcoded db queries

 class Query{
public:
	static double averageDuration();
	static float averagePatients();
	static float pscore();
	static int *numberOfShift();
private:



};
