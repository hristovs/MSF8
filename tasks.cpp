#include <iostream>
#include "queries.h"
#include <fstream>
using namespace pqxx;
using namespace std;

int main(){
	ofstream breaksFile;
	breaksFile.open("breaksForEachNurse.txt");
	string breakString = "break";
	string *nurses = Query::nurseList();
	int numberOfNurses = Query::numberOfNurse();
	//int breakArray = new int[numberOfNurses];
	for(int i = 0; i < numberOfNurses; ++i){
		breaksFile << "username: " << nurses[i] << " breaks: " << Query::amountOfBreaks(nurses[i]) << " percentage: " << Query::breaksAsTimePercentage(nurses[i])<< endl;
	}
	breaksFile.close();
}