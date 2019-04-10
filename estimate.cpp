#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"
#include "queries.h"
#include <fstream>
using namespace pqxx;
using namespace std;
int numberOfNurses;
int evaluationEXP(string qualification, int taskDuration, double score, int numberOfPatient, int sDuration, double sScore, int sNumberOfPatient){
    int evaluation=(qualification=="diploma")*2+(qualification=="bsc")*3+(qualification=="Assist")*3+(taskDuration<sDuration)+(score>sScore)*2+(score>1)+(numberOfPatient>sNumberOfPatient)*2+(numberOfPatient>0);
    return evaluation;
}

void simulationTest(int numberOfNurse,string nurseEXP[], double nurse[][4], int nurseExp[], int averagePatient, int peakPatient, int simScore){
    int lowExp=0;
    int mediumExp=0;
    int highExp=0;
    int nurseScore=0;
    int highScore=0;
    int mediumScore=0;
    int lowScore=0;
    double patientNumber=0;
    for (int i=0;i<numberOfNurse;i++) {
        for (int j=0; j<4; j++) {
            j=3;
            patientNumber+=nurse[i][3];
        }
    }
    for (int i=0; i<numberOfNurse; i++) {
        lowExp+=(nurseEXP[i]=="low");
        mediumExp+=(nurseEXP[i]=="medium");
        highExp+=(nurseEXP[i]=="high");
        nurseScore+=nurseExp[i];
        if(nurseExp[i]>=0&&nurseExp[i]<5)
            lowScore+=nurseExp[i];
        else if(nurseExp[i]>=5&&nurseExp[i]<8)
            mediumScore+=nurseExp[i];
        else if(nurseExp[i]>=8)
            highScore+=nurseExp[i];
    }
    if(nurseScore<simScore){//check if the nurses are enough for the outbreak.
        cout<<"we need more nurse"<<endl;
    }
    else if (nurseScore>simScore) {//check if the required number of experienced nurse is enough to handle outbreak.
        int count=0;
        int count1=0;
        int count2=0;
        for (int i=0; i<numberOfNurse; i++) {
            if (nurseEXP[i]=="high") {
                if(nurse[i][3]>(averagePatient/numberOfNurse)){
                    count++;
                }
            }
            else if (nurseEXP[i]=="medium") {
                if(nurse[i][3]>(averagePatient/numberOfNurse)){
                    count1++;
                }
            }
            else if (nurseEXP[i]=="low") {
                if(nurse[i][3]>(averagePatient/numberOfNurse)){
                    count2++;
                }
            }
        }
        if((count1+count2+count)>=numberOfNurse*0.75){//check if the number of patient per nurse is enough to handle the stress.
            if(count2+count1>=(numberOfNurse-count2)*0.8){
                if (patientNumber>peakPatient) {
                    if ((simScore-mediumScore-lowScore)/8<0) {
                        cout<<"You will need "<<lowExp<<" less experienced nurses, "<<mediumExp<<" more experienced nurses. There will be "<<numberOfNurse-lowExp-mediumExp<<" extra highly experienced nurses to handle any emergency."<<endl;
                    }
                    else{
                        cout<<"You will need "<<lowExp<<" less experienced nurses, "<<mediumExp<<" more experienced nurses and "<<(simScore-mediumScore-lowScore)/8<<" of highly experienced nurses. There will be "<<numberOfNurse-lowExp-mediumExp-(simScore-mediumScore-lowScore)/8<<" extra highly experienced nurses to handle any emergency."<<endl;
                    }
                }
                else{
                    cout<<"You will need additional staff to take care of "<<(peakPatient-patientNumber)<<" per day to handle the peak patient intake. Off-peak situations do not require extra staff."<<endl;
                }
            }
            else{
                cout<<"You will need "<<lowExp<<" less experienced nurses, "<<mediumExp<<" more experienced nurses. There will be "<<numberOfNurse-lowExp-mediumExp<<" extra highly experienced nurses to handle any emergency."<<endl;
            }
                
        }
        else{
            cout<<"Daily patient intake is too large. You need to take care of an extra "<<averagePatient*numberOfNurse-patientNumber<<" patients to handle this scenario."<<endl;
        }
    }
    else{
        cout<<"There are just enough nurses to handle the day-to-day running but not enough if there are an extraordinary amount of emergencies."<<endl;
    }
}


int main(){
    auto tpl = Query::nurseList();
    numberOfNurses=std::get<0>(tpl);
    string *nurseList =std::get<1>(tpl);
    double nurses[numberOfNurses][4];
    for(int i=0;i<numberOfNurses;i++){
        nurses[i][0]=Query::qualification(nurseList[i]);
        cout<<nurses[i][0]<<endl;
        nurses[i][1]=Query::averageDuration(nurseList[i]);
        cout<<nurses[i][1]<<endl;
        nurses[i][2]=Query::pscore(nurseList[i]);
        cout<<nurses[i][2]<<endl;
        nurses[i][3]=Query::averagePatients(nurseList[i]);
        cout<<nurses[i][3]<<endl;
        cout<<endl;
    }
    string qualifications[3]={"diploma","bsc","Assist"};
    //double nurse[20][5]={{1,20,1,20,20},{2,40,0.6,10,10},{1,70,1.5,12,15},{0,90,1.8,17,24},{2,100,2,2,22},{1,45,2.75,4,12},{0,49,3,10,12},{1,78,2.4,9,21},{2,282,0.6,11,25},{1,297,1.7,13,6},{1,29,2.9,16,9},{1,60,1.4,12,22},{0,23,1.5,1,6},{1,22,1.9,1,7},{1,28,1.4,3,28},{1,60,2.5,5,18},{1,80,0.7,8,17},{2,10,0.8,2,29},{1,40,1.8,10,22},{1,90,1.98,9,21}};
    int nurseExp[numberOfNurses];
    ofstream test;
    test.open("test.txt");
    for(int i=0;i<numberOfNurses;i++){//creat text file for graph.
        test<<nurses[i][1]<<" "<<nurses[i][2]<<" "<<nurses[i][3]<<"\n";
    }
    int sD=0;
    double sS=0;
    int sN=0;
    for (int i=0; i<numberOfNurses; i++) {
        sD+=nurses[i][1];
        sS+=nurses[i][2];
        sN+=nurses[i][3];
    }
    sD/=numberOfNurses;
    sS/=numberOfNurses;
    sN/=numberOfNurses;
    for(int i=0;i<numberOfNurses;i++){
        nurseExp[i]=evaluationEXP(qualifications[(int)nurses[i][0]], nurses[i][1], nurses[i][2], nurses[i][3],sD,sS,sN);
    }
    string rank[3]={"high","medium","low"};
    string results[numberOfNurses];
    for (int i=0; i<numberOfNurses; i++) {
        if(nurseExp[i]>=0&&nurseExp[i]<5)
            results[i]=rank[2];
        else if(nurseExp[i]>=5&&nurseExp[i]<8)
            results[i]=rank[1];
        else if(nurseExp[i]>=8)
            results[i]=rank[0];
    }
    int simScore,averagePatient,peakPatient;
    cout<<"Please enter the similuation score(severity) for the scenario: ";
    cin>>simScore;
    cout<<"Please enter the average daily patient intake in this scenario: ";
    cin>>averagePatient;
    cout<<"Please enter the projected peak number of patients in this secnario: ";
    cin>>peakPatient;
    simulationTest(numberOfNurses,results,nurses,nurseExp,averagePatient,peakPatient,simScore);
    return 0;
}


