#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"
#include <cstring>
using namespace pqxx;
using namespace std;
Select::Select(string selectParams){
    selectString = selectParams;
}

void Select::queryDatabase(){
    char selectFunctionNumber;
    try{
        string sql = selectString;
        connection C(connectionString);
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() <<"\n"<< endl;
        }
        else {
            cout << "Can't open database" << endl;
        }
        /* Create a non-transactional object. */
        nontransaction N(C);
        
        /* Execute SQL query */
        result R= N.exec(sql);
        cout << "Enter function: \n1 for unique column name.\n2 for store the data in a string.\n3 for size of the data.\n4 for ending the program.\n"<<endl;
        cin.get(selectFunctionNumber);
        cin.ignore(80,'\n');
        while (selectFunctions(R,selectFunctionNumber)!=1){
            cout << "\nEnter function: \n1 for unique column name.\n2 for store the data in a string.\n3 for size of the data.\n4 for ending the program.\n"<<endl;
            cin.get(selectFunctionNumber);
            cin.ignore(80,'\n');
        }
        C.disconnect();
    }catch(const exception &e){
        cerr<< e.what() << endl;
    }
}

void Select::uniqueData(result R){
    int flag=0;
    string inserts = ": ";
    for(result::const_iterator row = R.begin()+1; row!=R.end(); row++){
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

int Select::dataSize(result R){
    int ArraySize = 0;
    for(result::const_iterator row = R.begin(); row!=R.end(); row++){
        for(int i=0;i<row.size();i++){
            ArraySize++;//get the column size from database.
        }
    }
    return ArraySize;
}

string *Select::resultString(result R){
    string* results;
    int columnSize=R.columns();//column size from database.
    int j=0;//counter for the column name.
    int arraySize = dataSize(R);
    results = new string[arraySize];//init new string array with column size.
    string inserts = ": ";//better visulization, comment them if we don't want to print the data.
    for(result::const_iterator row = R.begin()+1; row!=R.end(); row++){
        for(int i=0;i<row.size();i++){
            if(!row[i].is_null())
                results[j]=R.column_name(i)+inserts+row[i].as<string>();//this is to store the data in one string
            else
                results[j]="Empty";
            j++;
        }
    }
    for(int i=0;i<arraySize;i++){
        if (i%columnSize==0||i==arraySize) {
            cout<<results[i]<<endl<<endl;
        }
        else{
            cout<<results[i]<<endl;
        }
    }
    cout<<"The data has been stored in string!"<<endl;
    return results;
}

int Select::selectFunctions(result R,int selectFunctionNumber){
    switch (selectFunctionNumber) {
        case 49:
            cout<<"Unique Data are: "<<endl;
            uniqueData(R);
            break;
        case 50:
            resultString(R);
            break;
        case 51:
            cout<<"\nsize of the data is "<<dataSize(R)<<"."<<endl;
            break;
        case 52:
            cout<<"\n";
            return 1;
            break;
        default:
            cout<<"This is not a valid input.\n";
            break;
    }
    return 0;
}
void Select::setConnectionParameters(string dbname,string account, string password, string endpoint, int port){
    string template1 = "dbname=";
    string template2 = " user=";
    string template3 = " password=";
    string template4 = " hostaddr=";
    string template5 = " port=";
    connectionString =template1+dbname+template2+account+template3+password+template4+endpoint+template5+to_string(port);
}

