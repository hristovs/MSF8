#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"
#include <unistd.h>
#include "queries.h"
using namespace std;
using namespace pqxx;

int main(){
	double duration = Query::averageDuration();
    cout << "Program finishing!!!" << endl;
    return 0;
}
