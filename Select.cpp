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

     
int Select::dataSize(){
    int ArraySize = 0;
    for(result::const_iterator row = R.begin(); row!=R.end(); row++){
        rowSize++;
        for(int i=0;i<row.size();i++){
            ArraySize++;//get the column size from database.
        }
    }
    return ArraySize;
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
        R= N.exec(sql);
/*        cout << "Enter function: \n1 for unique column name.\n2 for store the data in a string.\n3 for size of the data.\n4 calculate average task duration.\n5 for average number of patients.\n6 for calculating the average severity score for a user.\n7 for number of shift one user took.\n8 for ending the program.\n "<<endl;
        cin.get(selectFunctionNumber);
        cin.ignore(80,'\n');
        while (selectFunctions(selectFunctionNumber)!=1){
            cout << "\nEnter function: \n1 for unique column name.\n2 for store the data in a string.\n3 for size of the data.\n4 calculate average task duration.\n5 for average number of patients.\n6 for calculating the average severity score for a user.\n7 for number of shift one user took.\n8 for ending the program. \n"<<endl;
            cin.get(selectFunctionNumber);
            cin.ignore(80,'\n');
        }*/
        C.disconnect();
    }catch(const exception &e){
        cerr<< e.what() << endl;
    }
}

void Select::uniqueData(){
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



string *Select::resultString(){
    string* results;
    //int columnSize=R.columns();//column size from database.
    int j=0;//counter for the column name.
    int arraySize = dataSize();
    results = new string[arraySize];//init new string array with column size.
    string inserts = ": ";//better visulization, comment them if we don't want to print the data.
    for(result::const_iterator row = R.begin()+1; row!=R.end(); row++){
        for(int i=0;i<row.size();i++){
            if(!row[i].is_null()){
                results[j]=R.column_name(i)+inserts+row[i].as<string>();//this is to store the data in one string
            }
            else
                results[j]=R.column_name(i)+inserts+"Empty";
            j++;
    }
    return results;
}
}

/*int Select::selectFunctions(int selectFunctionNumber){
    switch (selectFunctionNumber) {
        case 49:
            cout<<"Unique Data are: "<<endl;
            uniqueData();
            break;
        case 50:
            resultString();
            cout<<"The data has been stored in string!"<<endl;
            break;
        case 51:
            cout<<"\nsize of the data is "<<dataSize()<<"."<<endl;
            break;
        case 52:{
            int result = averageDuration();
            if(result==0)
                cout<<"There aren't any data related to duration."<<endl;
            else
                cout << "The average task takes: " << result << " sec to complete!" <<  endl;
            break;
        }
        case 53:{
            int result = averagePatients();
            if(result==0)
                cout<<"There aren't any data related to number of patients."<<endl;
            else
                cout << "The average number of patients are: " << result << "." <<  endl;
            break;
        }
        case 54:{
            float result = pscore();
            cout<<"The average patient_severity_score for user ga49 is "<<result<<"."<<endl;
            break;
        }
        case 55:{
            int *result=numberOfShift();
            cout<<"The number of day shift ga49 took is "<<result[0]<<"."<<endl;
            cout<<"The number of night shift ga49 took is "<<result[1]<<"."<<endl;
            break;
        }
        case 56:
            cout<<"\n";
            return 1;
            break;
        default:
            cout<<"This is not a valid input.\n";
            break;
    }
    return 0;
}*/


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
