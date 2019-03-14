#include <iostream>
#include "Select.h"
#include <pqxx/pqxx>
#include <string>

using namespace std;

int main(){
	//this is just a little demo
	// to use, simply exit out of the provided menu by pressing 4
	// and you will see the average duration of a task
    string selectQuery = "select duration from t_events";
    //cout << "Enter query: ";
    //getline(cin,selectQuery);
        Select * aSelect = new Select(selectQuery);
        aSelect->setConnectionParameters("nurses", "nursesadmin", "password","63.35.110.243", 5432);
        aSelect->queryDatabase();
        string * results = aSelect->resultString();
        string delimiter = ": ";
        string tempString = " ";
        int averageDuration = 0;
        int averageDenominator = 0;
        int resultsLength = aSelect->dataSize(); // this int is there so i dont have to keep calling Select::dataSize();
        for(int i = 0; i <= resultsLength; ++i){
        	tempString = results[i];
        	if(!tempString.empty()){ // this if statement is there because for some reason the result string has empty lines
        		tempString = tempString.substr(tempString.find(delimiter) + 1);
        		averageDuration+= stoi(tempString);
        		++averageDenominator;
        	}
          	cout << i << "/" << resultsLength << " " << tempString << endl; 

        }
        double avrg = (averageDuration/averageDenominator)/60;
       // cout << "The average task takes: " << avrg << " minutes to complete!" <<  endl; //error handling
        delete aSelect;
}
