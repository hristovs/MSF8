#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"
#include <cstring>
using namespace pqxx;
using namespace std;
int rowSize;
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
        R= N.exec(sql);
        cout << "Enter function: \n1 for unique column name.\n2 for store the data in a string.\n3 for size of the data.\n4 calculate average task duration.\n5 for average number of patients.\n6 for calculating the average severity score for a user.\n7 for number of shift one user took.\n8 for ending the program.\n "<<endl;
        cin.get(selectFunctionNumber);
        cin.ignore(80,'\n');
        while (selectFunctions(selectFunctionNumber)!=1){
            cout << "\nEnter function: \n1 for unique column name.\n2 for store the data in a string.\n3 for size of the data.\n4 calculate average task duration.\n5 for average number of patients.\n6 for calculating the average severity score for a user.\n7 for number of shift one user took.\n8 for ending the program. \n"<<endl;
            cin.get(selectFunctionNumber);
            cin.ignore(80,'\n');
        }
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
            //cout<<results[j]<<endl;
            j++;
        }
        //cout<<endl;
    }
    //for(int i=0;i<arraySize;i++)
    //  cout<<results[j]<<endl;
    return results;
}

int Select::selectFunctions(int selectFunctionNumber){
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
}

double Select::averageDuration(){
    string delimiter = ": ";
    string tempString = " ";
    string columnName = "duration";
    int averageDuration = 0;
    int averageDenominator = 0;
    int count=0;
    int arraySize = dataSize();
    string* resultStrings = resultString();
    // this int is there so i dont have to keep calling Select::dataSize();
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){ // this if statement is there because for some reason the result string has empty lines
            if(tempString.substr(0,tempString.find(delimiter))==columnName){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                averageDuration+= stoi(tempString);
                ++averageDenominator;
                count++;
            }
        }
    }
    //cout<<averageDuration<<endl;
    //cout<<averageDenominator<<endl;
    if (count==0)
        return count;
    else
        return (double)(averageDuration/averageDenominator);
}

float Select::averagePatients(){
    string delimiter = ": ";
    string tempString = " ";
    string columnName = "number_of_patients_being_admitted";
    int averagePatient= 0;
    int averageDenominator = 0;
    int count=0;
    int arraySize = dataSize();
    string* resultStrings = resultString();
    // this int is there so i dont have to keep calling Select::dataSize();
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!=" Empty"){
                    averagePatient+= stoi(tempString);
                    ++averageDenominator;
                    count++;
                }
            }
        }
    }
    //cout<<averagePatient<<endl;
    //cout<<averageDenominator<<endl;
    if (count==0)
        return count;
    else{
        //return (float)averagePatient/(float)averageDenominator;
        float avgPt = (float) averagePatient;
        float avgDnm = (float) averageDenominator;
        float diff = avgPt/avgDnm;
        return diff;
    }
}

float Select::pscore(){
    string delimiter = ": ";
    string tempString = " ";
    string columnName = "patient_severity_score_1";
    string columnName2 = "patient_severity_score_2";
    string columnName3 = "patient_severity_score_3";
    string columnName4 = "total_number_of_patients_on_the_ward";
    float pscore1 = 0;
    float pscore2 = 0;
    float pscore3 = 0;
    float numberOfPatient =0;
    float arraySize = dataSize();
    string* resultStrings = resultString();
    // this int is there so i dont have to keep calling Select::dataSize();
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!=" Empty"&&tempString!=" nan"){
                    pscore1+= stof(tempString)*1;
                }
            }
        }
    }
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName2){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!=" Empty"&&tempString!=" nan"){
                    pscore2+= stof(tempString)*2;
                }
            }
        }
    }
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName3){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!=" Empty"&&tempString!=" nan"){
                    //cout<<"p3Score: "<<tempString<<endl;
                    pscore3+= stof(tempString)*3;
                }
            }
        }
    }
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName4){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!=" Empty"&&tempString!=" nan"){
                    //cout<<"p3Score: "<<tempString<<endl;
                    numberOfPatient+= stof(tempString);
                }
            }
        }
    }
    float result =(pscore1+pscore2+pscore3)/numberOfPatient;
    //cout<<"result: "<<result<<endl;
    return result;
}

int *Select::numberOfShift(){
    string delimiter = ": ";
    string tempString = " ";
    string columnName = "enter_the_shift_you_are_working";
    int *result = new int[2];
    int countDay = 0;
    int countNight=0;
    float arraySize = dataSize();
    string* resultStrings = resultString();
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!=" Empty"){
                    if(tempString=="am"||tempString=="pm"||tempString==" day"){
                        countDay++;
                    }
                    else if(tempString==" night"){
                        countNight++;
                    }
                }
            }
        }
    }
    result[0]=countDay;
    result[1]=countNight;
    return result;
}

void Select::setConnectionParameters(string dbname,string account, string password, string endpoint, int port){
    string template1 = "dbname=";
    string template2 = " user=";
    string template3 = " password=";
    string template4 = " hostaddr=";
    string template5 = " port=";
    connectionString =template1+dbname+template2+account+template3+password+template4+endpoint+template5+to_string(port);
}

