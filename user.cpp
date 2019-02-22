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
    
    Select * aSelect = new Select(selectQuery);
    aSelect->setConnectionParameters("nurses", "nursesadmin", "password","63.35.110.243", 5432);
    aSelect->queryDatabase();
    //    while(aSelect->notFinished){
    //    usleep(1000);
    //        }
    delete aSelect;
    
    cout << "Program finishing!!!" << endl;
    return 0;
}
