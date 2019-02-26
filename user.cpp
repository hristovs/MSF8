#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"
#include <unistd.h>
using namespace std;
using namespace pqxx;

int main(){
    string selectQuery = "";
    cout << "Enter query: ";
    getline(cin,selectQuery);
    while(selectQuery!="quit"&&selectQuery!="4"){
        Select * aSelect = new Select(selectQuery);
        aSelect->setConnectionParameters("nurses", "nursesadmin", "password","63.35.110.243", 5432);
        aSelect->queryDatabase();
        delete aSelect;
        cout << "Enter query: ";
        getline(cin,selectQuery);
    }
    cout << "Program finishing!!!" << endl;
    return 0;
}
