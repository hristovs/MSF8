#include <iostream>
#include "queries.h"
#include "Select.h"
/* 
 *@function:averageDuration
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
    for(int i = 0; i <arraySize; ++i){
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
    if (count==0)
        return count;
    else
        return (double)(averageDuration/averageDenominator);
}



/* 
 *@function:averagePatients
 * @author: Jingren Li
 * @edited: Samuil Hristov
 * Returns float of average patients being admitted
 */

float Query::averagePatients(string username){
    string delimiter = ":";
    string tempString1 = " ";
    string columnName = "number_of_patients";
    string sqlQuery = "select number_of_patients from tevent where username='"+username+"' and number_of_patients is not null";
    /*string columnName2 = "completed_time";
    string sqlQuery2 = "select completed_time from tevent where completed_time<current_timestamp and username='"+username+"' order by completed_time asc limit 1";
    string sqlQuery3 = "select completed_time from tevent where completed_time<current_timestamp and username='"+username+"' order by completed_time desc limit 1";
    Select *startTime=new Select(sqlQuery2);
    startTime->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    startTime->queryDatabase();
    string *startDate = startTime->resultString();
    string start = startDate[0].substr(startDate[0].find(delimiter) + 1);
    Select *endTime=new Select(sqlQuery3);
    endTime->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    endTime->queryDatabase();
    string *endDate = endTime->resultString();
    string end = endDate[0].substr(endDate[0].find(delimiter) + 1);
    string sqlQuery4 = "select date_part('day','"+end+"'::timestamp-'"+start+"'::timestamp)";
    Select *diffTime=new Select(sqlQuery4);
    diffTime->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    diffTime->queryDatabase();
    string *diffDate = diffTime->resultString();
    float diff = stof(diffDate[0].substr(diffDate[0].find(delimiter) + 1));*/
    Select *averagePatientsSelect = new Select(sqlQuery);
    averagePatientsSelect->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    averagePatientsSelect->queryDatabase();
    float averagePatient= 0;
    float diffs = 0;
    int count=0;
    int arraySize = averagePatientsSelect->dataSize();
    string* resultStrings = averagePatientsSelect->resultString();
    // this int is there so i dont have to keep calling Select::dataSize();
    for(int i = 0; i <arraySize; ++i){
        tempString1 = resultStrings[i];
        if(!tempString1.empty()){
            if(tempString1.substr(0,tempString1.find(delimiter))==columnName){
                tempString1 = tempString1.substr(tempString1.find(delimiter) + 1);
                if(tempString1!="Empty"){
                    averagePatient+= stof(tempString1);
                    diffs++;
                    count++;
                }
            }
        }
    }
    if (count==0)
        return count;
    else{
        return averagePatient/diffs;
    }
}


/* 
 *@function:pscore
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
    string tempString2 = " ";
    float pscore1 = 0;
    float pscore2 = 0;
    float pscore3 = 0;
    float numberOfPatient =0;
    float arraySize = pscoreSelect->dataSize();
    string* resultStrings = pscoreSelect->resultString();
    for(int i = 0; i <arraySize; ++i){
        tempString2 = resultStrings[i];
        if(!tempString2.empty()){
            if(tempString2.substr(0,tempString2.find(delimiter))=="patient_severity_score_1"){
                tempString2 = tempString2.substr(tempString2.find(delimiter) + 1);
                if(tempString2!="Empty"&&tempString2!="nan"){
                    pscore1+= stof(tempString2)*1;
                }
            }
        }
    }
    for(int i = 0; i <arraySize; ++i){
        tempString2 = resultStrings[i];
        if(!tempString2.empty()){
            if(tempString2.substr(0,tempString2.find(delimiter))=="patient_severity_score_2"){
                tempString2 = tempString2.substr(tempString2.find(delimiter) + 1);
                if(tempString2!="Empty"&&tempString2!="nan"){
                    pscore2+= stof(tempString2)*2;
                }
            }
        }
    }
    for(int i = 0; i <arraySize; ++i){
        tempString2 = resultStrings[i];
        if(!tempString2.empty()){
            if(tempString2.substr(0,tempString2.find(delimiter))=="patient_severity_score_3"){
                tempString2 = tempString2.substr(tempString2.find(delimiter) + 1);
                if(tempString2!="Empty"&&tempString2!="nan"){
                    //cout<<"p3Score: "<<tempString<<endl;
                    pscore3+= stof(tempString2)*3;
                }
            }
        }
    }
    for(int i = 0; i <arraySize; ++i){
        tempString2 = resultStrings[i];
        if(!tempString2.empty()){
            if(tempString2.substr(0,tempString2.find(delimiter))=="total_number_of_patients_on_the_ward"){
                tempString2 = tempString2.substr(tempString2.find(delimiter) + 1);
                if(tempString2!="Empty"&&tempString2!="nan"){
                    //cout<<"p3Score: "<<tempString<<endl;
                    numberOfPatient+= stof(tempString2);
                }
            }
        }
    }
    float result =(pscore1+pscore2+pscore3)/numberOfPatient;
    return result;
}


/*
 * @function:numberOfShift
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
    string tempString3 = " ";
    string columnName = "enter_the_shift_you_are_working";
    int *result = new int[2];
    int countDay = 0;
    int countNight=0;
    float arraySize = numberOfShiftSelect->dataSize();
    string* resultStrings = numberOfShiftSelect->resultString();
    for(int i = 0; i <=arraySize; ++i){
        tempString3 = resultStrings[i];
        if(!tempString3.empty()){
            if(tempString3.substr(0,tempString3.find(delimiter))==columnName){
                tempString3 = tempString3.substr(tempString3.find(delimiter) + 1);
                if(tempString3!="Empty"){
                    if(tempString3=="am"||tempString3=="pm"||tempString3=="day"){
                        countDay++;
                    }
                    else if(tempString3=="night"){
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

/*int Query::numberOfNurse(){
    string sqlQuery = "select username from texp";
    Select *numberOfNurse = new Select(sqlQuery);
    numberOfNurse->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    numberOfNurse->queryDatabase();
    int arraySize = numberOfNurse->dataSize();
    return arraySize;
}*/

int Query::qualification(string username){
    string sqlQuery = "select qualification from texp where username='"+username+"'";
    Select *qualification = new Select(sqlQuery);
    qualification->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    qualification->queryDatabase();
    string delimiter = ":";
    string tempString4 = " ";
    string columnName = "qualification";
    int arraySize = qualification->dataSize();
    string* resultStrings = qualification->resultString();
    int result=5;
    for (int i=0; i<arraySize; i++) {
        tempString4 = resultStrings[i];
        if(tempString4.substr(0,tempString4.find(delimiter))==columnName){
            tempString4 = tempString4.substr(tempString4.find(delimiter) + 1);
            if(tempString4=="diploma_in_nursing_science_and_midwiferyorthopedic")
                result=0;
            else if(tempString4=="bsc_nursing"){
                result=1;
            }
            else{
                result=2;
            }
        }
    }
    return result;
}

/*
 *@function:nurseList()
 *@author:Jingren Li
 *@edited:Samuil Hristov
 *returns a tuple of array size and string array of nurse IDs 
 */
std::tuple<int, string *> Query::nurseList(){
    string delimiter = ":";
    int nursesToExclude = 1;

    string columnName = "username";
    string sqlQuery = "select username from texp";
    Select *username = new Select(sqlQuery);
    username->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    username->queryDatabase();
    int arraySize = username->dataSize();
    string *resultStrings=username->resultString();
    int sizeOfFilteredArray = arraySize - nursesToExclude;
    string *filteredResults = new string[sizeOfFilteredArray];
    int j = 0;
    for (int i=0; i<arraySize;i++) {
        if(resultStrings[i].substr(0,resultStrings[i].find(delimiter))==columnName){
            if( !(resultStrings[i].substr(resultStrings[i].find(delimiter) + 1)=="gi64")){
                filteredResults[j]=resultStrings[i].substr(resultStrings[i].find(delimiter) + 1);
                ++j;
        }
        }
    }
    return {sizeOfFilteredArray, filteredResults};
}






std::tuple<int, string *> Query::nurseList(string* nursesToExclude, int amountOfNursesToExclude){
    string delimiter = ":";
    int szExclude = amountOfNursesToExclude;

    string columnName = "username";
    string sqlQuery = "select username from texp";
    Select *username = new Select(sqlQuery);
    username->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    username->queryDatabase();
    int arraySize = username->dataSize();
    string *resultStrings=username->resultString();
    int sizeOfFilteredArray = arraySize - szExclude;
    string *filteredResults = new string[sizeOfFilteredArray];
    int j = 0;
    for (int i=0; i<arraySize;i++) {
        if(resultStrings[i].substr(0,resultStrings[i].find(delimiter))==columnName){
            if(!(isPresent(nursesToExclude,szExclude,resultStrings[i].substr(resultStrings[i].find(delimiter) + 1)))){
                filteredResults[j]=resultStrings[i].substr(resultStrings[i].find(delimiter) + 1);
                ++j;
        }
    }
    }
    return {sizeOfFilteredArray, filteredResults};
}










/*
 *@function:amountOfBreaks(username) 
 *@author:Samuil Hristov
 *returns integer - amount of breaks for a given username
 */


int Query::amountOfBreaks(string username){
    string sql = "select event_id from tevent where username='" + username + "' and event_type='taking_a_break'";
    Select *breaks = new Select(sql);
    breaks->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    breaks->queryDatabase();
    return breaks->dataSize();
}


/*
 *@function:breaksAsTimePercentage(username)
 *@author:Samuil Hristov
 *returns breaks of a user as a percentage of their total time spent doing actions in a month
 */


double Query::breaksAsTimePercentage(string username){
    string allDurationSQL = "select duration from tevent where username='" + username + "'";
    Select *allDuration = new Select(allDurationSQL);
    allDuration->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    allDuration->queryDatabase();
    string *resultString = allDuration->resultString();
    int size = allDuration->dataSize();
    double totalDuration = 0.0;
    for(int i = 0; i < size; ++i){
        if(resultString[i].substr(0,resultString[i].find(":"))=="duration"){
        if(!resultString[i].substr(resultString[i].find(":") + 1).empty()){
        totalDuration+= stod(resultString[i].substr(resultString[i].find(":") + 1));
    }
    }
    }
  

    string breakDurationSQL = "select duration from tevent where username='" + username + "' and event_type='taking_a_break'";
    Select *breakDuration = new Select(breakDurationSQL);
    breakDuration->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    breakDuration->queryDatabase();
    string *breakString = breakDuration->resultString();
    int breaks = breakDuration->dataSize();
    double totalBreakDuration = 0.0;
    for(int i = 0; i < breaks; ++i){
        if(breakString[i].substr(0,breakString[i].find(":"))=="duration"){
        if(!breakString[i].substr(breakString[i].find(":") + 1).empty()){
        totalBreakDuration+=stod(breakString[i].substr(breakString[i].find(":") + 1));
    }

    }
    }
    return (totalBreakDuration/totalDuration)*100;

}

/*
 *@function:uniqueEvents
 *@author:Samuil Hristov
 *returns a tuple of array size and string array of unique events in tevent
 */

std::tuple<int, string*>  Query::uniqueEvents(){
    string sql = "select event_type from tevent";
    Select *events = new Select(sql);
    events->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    events->queryDatabase();
    int size = events->dataSize();
    string *results = events->resultString();
    string *uniqueResults;
    int j = 0;
    uniqueResults = new string[events->dataSize()];
    for(int i = 0; i < size; ++i){
        if(results[i].substr(0,results[i].find(":"))=="event_type" && !(results[i].substr(results[i].find(":")+1).empty())){
        if(!isPresent(uniqueResults,j,results[i].substr(results[i].find(":")+1))){
           
            uniqueResults[j] = results[i].substr(results[i].find(":")+1);
            ++j;
        }
    }
    }

    return {j, uniqueResults};
}

/*
 *@function:isPresent(array,size,token)
 *@author:Samuil Hristov
 *check if token is present in an array of a given size
 */

 bool Query::isPresent(string *array, int size, string checkPresent){
    if(size == 0) return false;
    for(int i = 0; i < size; ++i){
        if(array[i].substr(array[i].find(":")+1) == checkPresent) return true;
    }
    return false;
 }





/*
 *@function:baselinePercentage()
 *@author:Samuil Hristov
 *returns tuple of array size and string array
 */


 double Query::baselinePercentage(string username){
string arrayOfBaselineTasks[]={"admission","discharge","drug_round","vital_sign_round","patient_documentation","meeting_patients_basic_needs",\
"handover","surveillance","taking_a_break","indirect_patient_care","pharmacy_tasks"};
    int baselineTaskAmount = 11;
    string sql = "select duration from tevent where (username='" + username + "')";

    for(int i = 0; i < baselineTaskAmount; ++i){
        if(i == 0){
            sql+=" AND (event_type='" + arrayOfBaselineTasks[i] + "'";
        } 
        else{
            sql+=" OR event_type='" + arrayOfBaselineTasks[i] + "'";
        }
    }
    sql+=")";
    cout << sql << endl;
    Select *baseline = new Select(sql);
    baseline->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    baseline->queryDatabase();
    string *resultString = baseline->resultString();
    int size = baseline->dataSize();
    double baselineDuration = 0.0;
    double wholeDuration = durationOfAllTasks(username);

      for(int i = 0; i < size; ++i){
      if(resultString[i].substr(0,resultString[i].find(":"))=="duration" && !(resultString[i].substr(resultString[i].find(":")+1).empty())){
            baselineDuration += stod(resultString[i].substr(resultString[i].find(":")+1));

        }
    }

    return (baselineDuration/wholeDuration) * 100;
 }

double Query::durationOfAllTasks(string username){
    string sql = "select duration from tevent where username='" + username + "'";
    Select *duration = new Select(sql);
    duration->setConnectionParameters("nurses", "nursesadmin", "password","63.32.216.167", 5432);
    duration->queryDatabase();
    string *resultString = duration->resultString();
    int size = duration->dataSize();
    double allTasks = 0.0;
    for(int i = 0; i < size; ++i){
      if(resultString[i].substr(0,resultString[i].find(":"))=="duration" && !(resultString[i].substr(resultString[i].find(":")+1).empty())){
            allTasks += stod(resultString[i].substr(resultString[i].find(":")+1));
        }
    }
    return allTasks;
}