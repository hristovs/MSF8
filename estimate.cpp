#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"
#include "queries.h"
#include <fstream>
using namespace pqxx;
using namespace std;

string evaluationEXP(string qualification, int taskDuration, double score, int numberOfPatient, int sDuration, double sScore, int sNumberOfPatient){
    int result=(qualification=="diploma")*2+(qualification=="bsc")*3+(qualification=="Assist")*3+(taskDuration<sDuration)+(score>sScore)*2+(score>1)+(numberOfPatient>sNumberOfPatient)*2+(numberOfPatient>0);
    string rank[3]={"high","medium","low"};
    string results;
    if(result>=0&&result<5)
        results=rank[2];
    else if(result>=5&&result<8)
        results=rank[1];
    else if(result>=8)
        results=rank[0];
    return results;
}

void outBreakTest(int numberOfNurse, int typeOfOutbreak,string nurseEXP[], double nurse[][4]){
    int lowExp=0;
    int mediumExp=0;
    int highExp=0;
    for (int i=0; i<numberOfNurse; i++) {
        lowExp+=(nurseEXP[i]=="low");
        mediumExp+=(nurseEXP[i]=="medium");
        highExp+=(nurseEXP[i]=="high");
    }
    switch (typeOfOutbreak) {
        case 1:{
            if(numberOfNurse<20){//check if the nurse if enough for the outbreak.
                cout<<"we need more nurse"<<endl;
            }
            else if (highExp>=5) {//check if the required number of experienced nurse is enough.
                int count=0;
                int count1=0;
                int count2=0;
                for (int i=0; i<numberOfNurse; i++) {
                    if (nurseEXP[i]=="high") {
                        if(nurse[i][3]>10){
                            count++;
                        }
                    }
                    else if (nurseEXP[i]=="medium") {
                        if(nurse[i][3]>10){
                            count1++;
                        }
                    }
                    else if (nurseEXP[i]=="low") {
                        if(nurse[i][3]>10){
                            count2++;
                        }
                    }
                }
                if((count1+count2+count)>=15){//check if the number of patient per nurse is enough to handle the stress.
                    if(count2>10||count1>10){
                        if (mediumExp>=8) {
                            cout<<"we need "<<highExp<<" of experienced nurses and "<<mediumExp<<" of medium experienced nurses"<<endl;
                        }
                        else if(lowExp>=12){
                            cout<<"we need "<<highExp<<" of experienced nurses and "<<mediumExp<<" of medium experienced nurses and "<<(numberOfNurse-highExp-mediumExp)<<" of low experienced nurses"<<endl;
                        }
                    }
                    else{
                        cout<<"we need "<<highExp<<" of experienced nurses and "<<mediumExp<<" of medium experienced nurses"<<endl;
                    }
                }
                else
                    cout<<"we need "<<(15-count1-count2-count)<<" more nurse with number patient taken care of greater than "<<10<<endl;
            }
            else{
                cout<<"not enough experienced nurse"<<endl;
            }
            break;
        }
        case 2:{
            
            break;
        }
        case 3:{
            
            break;
        }
        default:
            break;
    }
}


int main(){
    int numberOfNurses=Query::numberOfNurse();
    string *nurseList = Query::nurseList();
    double nurses[numberOfNurses][4];
    for(int i=0;i<numberOfNurses;i++){
        nurses[i][0]=Query::qualification(nurseList[i]);
        //cout<<nurses[i][0]<<endl;
        nurses[i][1]=Query::averageDuration(nurseList[i]);
        //cout<<nurses[i][1]<<endl;
        nurses[i][2]=Query::pscore(nurseList[i]);
        //cout<<nurses[i][2]<<endl;
        nurses[i][3]=Query::averagePatients(nurseList[i]);
        //cout<<nurses[i][3]<<endl;
    }
    string qualifications[3]={"diploma","bsc","Assist"};
    //double nurse[20][5]={{1,20,1,20,20},{2,40,0.6,10,10},{1,70,1.5,12,15},{0,90,1.8,17,24},{2,100,2,2,22},{1,45,2.75,4,12},{0,49,3,10,12},{1,78,2.4,9,21},{2,282,0.6,11,25},{1,297,1.7,13,6},{1,29,2.9,16,9},{1,60,1.4,12,22},{0,23,1.5,1,6},{1,22,1.9,1,7},{1,28,1.4,3,28},{1,60,2.5,5,18},{1,80,0.7,8,17},{2,10,0.8,2,29},{1,40,1.8,10,22},{1,90,1.98,9,21}};
    string nurseExp[20];
    ofstream test;
    test.open("/Users/jingrenli/Library/Mobile Documents/com~apple~CloudDocs/nurse_allocation/test.text");
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
        cout<<"nurse"<<i<<" has "<<nurseExp[i]<<" experence."<<endl;
    }
 
    int outBreak[3] = {1,2,3};
    for (int i=0; i<3; i++) {
        outBreakTest(numberOfNurses, outBreak[i], nurseExp,nurses);
    }
    return 0;
}


