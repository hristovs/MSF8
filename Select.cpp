#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"
#include <cstring>
#include "queries.h"
using namespace pqxx;
using namespace std;
int rowSize;
Select::Select(string selectParams){
    selectString = selectParams;
}


int Select::dataSize(){//calculate the size of the array.
    int ArraySize = 0;
    if (R.begin()==R.end()) {
        result::const_iterator row=R.begin();
        for(int i=0;i<row.size();i++){
            ArraySize++;//get the column size from database.
        }
    }
    else{
        for(result::const_iterator row = R.begin(); row!=R.end(); row++){
            rowSize++;
            for(int i=0;i<row.size();i++){
                ArraySize++;//get the column size from database.
            }
        }
    }
    return ArraySize;
}


void Select::queryDatabase(){//char selectFunctionNumber;
    try{
        string sql = selectString;
        connection C(connectionString);
        if (C.is_open()) {
            //cout << "Opened database successfully: " << C.dbname() <<"\n"<< endl;
        }
        else {
            cout << "Can't open database" << endl;
        }
        nontransaction N(C);
        R= N.exec(sql);
        C.disconnect();
    }catch(const exception &e){
        cerr<< e.what() << endl;
    }
}

void Select::uniqueData(){
    int flag=0;
    string inserts = ": ";
    for(result::const_iterator row = R.begin()+1; row<=R.end(); row++){
        for(int i=0;i<row.size();i++){
            if(flag==1){
                if (!row[i].is_null()&&!(row-1)[i].is_null()){
                    if((row-1)[i].as<string>()!=row[i].as<string>())//print out unique column name.
                        cout<<R.column_name(i)+inserts+row[i].as<string>()<<endl;
                    else
                        cout<<R.column_name(i)+inserts+" Empty "<<endl;
                }
            }
            else{
                if (row[i].is_null())
                    cout<<R.column_name(i)+inserts+" Empty "<<endl;
                else{
                    cout<<R.column_name(i)+inserts+row[i].as<string>()<<endl;
                    flag=1;
                }
            }
        }
        cout<<endl;
    }
}


string *Select::resultString(){
    string* results;
    int j=0;//counter for the column name.
    int arraySize = dataSize();
    results = new string[arraySize];//init new string array with column size.
    string inserts = ":";//better visulization, comment them if we don't want to print the data.
    for(result::const_iterator row = R.begin(); row!=R.end(); row++){//this doesn't cause any error anymore!!!!
        for(int i=0;i<row.size();i++){
            if(!row[i].is_null()){
                results[j]=R.column_name(i)+inserts+row[i].as<string>();//this is to store the data in one string
                //cout<<results[j]<<endl;
            }
            else
                results[j]=R.column_name(i)+inserts+"Empty";
            j++;
        }
    }
    return results;
}

void Select::setConnectionParameters(string dbname,string account, string password, string endpoint, int port){
    string db = "dbname=";
    string usr = " user=";
    string pass = " password=";
    string addr = " hostaddr=";
    string portno = " port=";
    connectionString =db+dbname+usr+account+pass+password+addr+endpoint+portno+to_string(port);
}

result Select::returnResult(){
    return R;
}

