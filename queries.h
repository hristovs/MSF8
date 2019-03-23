#include <pqxx/pqxx>

 class Query{
public:
	int dataSize(pqxx::result R);
	double averageDuration();
	float averagePatients();
	float pscore();
	int *numberOfShift();
private:



};
