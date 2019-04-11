#include <iostream>
#include "queries.h"
#include <fstream>

using namespace pqxx;
using namespace std;


void dumpUniqueTasks(){
	fstream uTasks;
	uTasks.open("uniqueTasks.txt");
	auto tple = Query::uniqueEvents();
	int sz = std::get<0>(tple);
	string *results = std::get<1>(tple);
	for(int i = 0; i < sz; ++i){
		uTasks << results[i] << endl;
	}

	uTasks.close();
}


void breaksFile(){
	fstream breaksFile;
	breaksFile.open("breaksForEachNurse.txt");
	int amountOfNursesToExclude = 1;
	string* nursesToExclude = new string[amountOfNursesToExclude];
	nursesToExclude[0] = "gi64";
	auto tple = Query::nurseList(nursesToExclude, amountOfNursesToExclude);
	int sz = std::get<0>(tple);
	string *nurses = std::get<1>(tple);
	for(int i = 0; i < sz; ++i){
		breaksFile << "username: " << nurses[i] << " breaks: " << Query::amountOfBreaks(nurses[i]) << " percentage: " << Query::breaksAsTimePercentage(nurses[i])<< endl;
	}
	breaksFile.close();
}



void baselineCare(){
	fstream baselinePercentFile;
	baselinePercentFile.open("baselinePercentageForEachNurse.txt");
	int amountOfNursesToExclude = 1;
	string* nursesToExclude = new string[amountOfNursesToExclude];
	nursesToExclude[0] = "gi64";
	auto tple = Query::nurseList(nursesToExclude, amountOfNursesToExclude);
	int numberOfNurses = std::get<0>(tple);
	string *nurses = std::get<1>(tple);
	for(int i = 0; i < numberOfNurses; ++i){
		baselinePercentFile << "username: " << nurses[i] << " baseline percentage: " << Query::baselinePercentage(nurses[i]) << endl;
	}
	baselinePercentFile.close();
}


int main(){
	//breaksFile();
	//dumpUniqueTasks();
	baselineCare();
}

