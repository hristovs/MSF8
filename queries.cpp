#include <iostream>
#include "queries.h"
#include "Select.h"




/* @function:averageDuration
 * @author: Samuil Hristov
 * @edited: Jingren Li, Samuil Hristov
 * Returns double of averageDuration for all tasks
 */

double Query::averageDuration(string username){
    string sqlQuery = "select duration from tevent where username='"+username+"'";
    Select *averageDurationSelect = new Select(sqlQuery);
    averageDurationSelect->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    averageDurationSelect->queryDatabase();
    string delimiter = ":";
    string tempString = " ";
    string columnName = "duration";
    int averageDuration = 0;
    int averageDenominator = 0;
    int count=0;
    int arraySize = averageDurationSelect->dataSize();
    string* resultStrings = averageDurationSelect->resultString();
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
    //delete averageDurationSelect;
    if (count==0)
        return count;
    else
        return (double)(averageDuration/averageDenominator);
}




/* @function:averagePatients
 * @author: Jingren Li
 * @edited: Samuil Hristov
 * Returns float of average patients being admitted
 */

float Query::averagePatients(string username){
    string sqlQuery = "select number_of_patients_being_admitted from tevent where username='"+username+"'";
    Select *averagePatientsSelect = new Select(sqlQuery);
    averagePatientsSelect->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    averagePatientsSelect->queryDatabase();
    string delimiter = ":";
    string tempString = " ";
    string columnName = "number_of_patients_being_admitted";
    int averagePatient= 0;
    int averageDenominator = 0;
    int count=0;
    int arraySize = averagePatientsSelect->dataSize();
    string* resultStrings = averagePatientsSelect->resultString();
    // this int is there so i dont have to keep calling Select::dataSize();
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!="Empty"){
                    averagePatient+= stoi(tempString);
                    ++averageDenominator;
                    count++;
                }
            }
        }
    }
    //cout<<averagePatient<<endl;
    //cout<<averageDenominator<<endl;
    //delete averagePatientsSelect;
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





/* @function:pscore
 * @author: Jingren Li
 * @edited: Samuil Hristov
 * Returns float of average patient severity
 */

float Query::pscore(string username){
    string sqlQuery = "select patient_severity_score_1,patient_severity_score_2,patient_severity_score_3,total_number_of_patients_on_the_ward from tevent where username='"+username+"'";
    Select *pscoreSelect = new Select(sqlQuery);
    pscoreSelect->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    pscoreSelect->queryDatabase();
    string delimiter = ":";
    string tempString = " ";
    string columnName = "patient_severity_score_1";
    string columnName2 = "patient_severity_score_2";
    string columnName3 = "patient_severity_score_3";
    string columnName4 = "total_number_of_patients_on_the_ward";
    float pscore1 = 0;
    float pscore2 = 0;
    float pscore3 = 0;
    float numberOfPatient =0;
    float arraySize = pscoreSelect->dataSize();
    string* resultStrings = pscoreSelect->resultString();
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!="Empty"&&tempString!="nan"){
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
                if(tempString!="Empty"&&tempString!="nan"){
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
                if(tempString!="Empty"&&tempString!="nan"){
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
                if(tempString!="Empty"&&tempString!="nan"){
                    //cout<<"p3Score: "<<tempString<<endl;
                    numberOfPatient+= stof(tempString);
                }
            }
        }
    }
    float result =(pscore1+pscore2+pscore3)/numberOfPatient;
    //delete pscoreSelect;
    //cout<<"result: "<<result<<endl;
    return result;
}




/* @function:numberOfShift
 * @author: Jingren Li
 * @edited: Samuil Hristov
 * Returns array of size 2 - gives day and night shift amounts
 */

int *Query::numberOfShift(){
    string sqlQuery = "select enter_the_shift_you_are_working from tacuity";
    Select *numberOfShiftSelect = new Select(sqlQuery);
    numberOfShiftSelect->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    numberOfShiftSelect->queryDatabase();
    string delimiter = ":";
    string tempString = " ";
    string columnName = "enter_the_shift_you_are_working";
    int *result = new int[2];
    int countDay = 0;
    int countNight=0;
    float arraySize = numberOfShiftSelect->dataSize();
    string* resultStrings = numberOfShiftSelect->resultString();
    for(int i = 0; i <=arraySize; ++i){
        tempString = resultStrings[i];
        if(!tempString.empty()){
            if(tempString.substr(0,tempString.find(delimiter))==columnName){
                tempString = tempString.substr(tempString.find(delimiter) + 1);
                if(tempString!="Empty"){
                    if(tempString=="am"||tempString=="pm"||tempString=="day"){
                        countDay++;
                    }
                    else if(tempString=="night"){
                        countNight++;
                    }
                }
            }
        }
    }
    result[0]=countDay;
    result[1]=countNight;
    delete numberOfShiftSelect;
    return result;
}

int Query::numberOfNurse(){
    string sqlQuery = "select username from texp";
    Select *numberOfNurse = new Select(sqlQuery);
    numberOfNurse->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    numberOfNurse->queryDatabase();
    string delimiter = ":";
    string tempString = " ";
    string columnName = "username";
    int arraySize = numberOfNurse->dataSize();
    return arraySize;
}

int Query::qualification(string username){
    string sqlQuery = "select qualification from texp where username='"+username+"'";
    Select *qualification = new Select(sqlQuery);
    qualification->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    qualification->queryDatabase();
    string delimiter = ":";
    string tempString = " ";
    string columnName = "qualification";
    int arraySize = qualification->dataSize();
    string* resultStrings = qualification->resultString();
    int result=5;
    for (int i=0; i<arraySize; i++) {
        tempString = resultStrings[i];
        string tempString2=tempString.substr(0,tempString.find(delimiter));
        if(tempString.substr(0,tempString.find(delimiter))==columnName){
            tempString = tempString.substr(tempString.find(delimiter) + 1);
            if(tempString=="diploma_in_nursing_science_and_midwiferyorthopedic")
                result=0;
            else if(tempString=="bsc_nursing"){
                result=1;
            }
            else{
                result=2;
            }
        }
    }
    return result;
}

string *Query::nurseList(){
    string delimiter = ":";
    string tempString = " ";
    string columnName = "username";
    string sqlQuery = "select username from texp";
    Select *username = new Select(sqlQuery);
    username->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    username->queryDatabase();
    int arraySize = username->dataSize();
    string *resultStrings=username->resultString();
    for (int i=0; i<arraySize;i++) {
        tempString = resultStrings[i];
        if(tempString.substr(0,tempString.find(delimiter))==columnName){
            resultStrings[i]=tempString.substr(tempString.find(delimiter) + 1);
        }
    }
    return resultStrings;
}
