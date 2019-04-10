#include <iostream>
#include "queries.h"
#include <fstream>
using namespace pqxx;
using namespace std;


void dumpUniqueTasks(){
	auto tple = Query::uniqueEvents();
	int sz = std::get<0>(tple);
	string *results = std::get<1>(tple);
	fstream uTasks;
	uTasks.open("/home/sam/Desktop/Group8/MSF8/uniqueTasks.txt");

	for(int i = 0; i < sz; ++i){
		uTasks << results[i] << endl;
		cout<< "testing" << endl;
	}

	uTasks.close();
}


void breaksFile(){
	fstream breaksFile;
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




int main(){
	//breaksFile();
	dumpUniqueTasks();
}


/*

void indirectCare(){

}


void directCare(){



}
*/
