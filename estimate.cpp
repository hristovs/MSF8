#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"

using namespace pqxx;
using namespace std;

string evaluationEXP(string qualification, int taskDuration, double score, int numberOfPatient, int workTime ){
    int result=(qualification=="Master")*3+(qualification=="BA")*2+(qualification=="Assist")*3+(taskDuration<50)+(score>1.75)*2+(score>0)+(numberOfPatient>5)*2+(numberOfPatient>0)+(workTime>=16);
    string rank[3]={"high","medium","low"};
    string results;
    if(result>=0&&result<5)
        results=rank[2];
    else if(result>=5&&result<9)
        results=rank[1];
    else if(result>=9)
        results=rank[0];
    return results;
}

void outBreakTest(int numberOfNurse, int typeOfOutbreak,string nurseEXP[], double nurse[][5]){
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
                        if(nurse[i][4]>10){
                            count++;
                        }
                    }
                    else if (nurseEXP[i]=="medium") {
                        if(nurse[i][4]>10){
                            count1++;
                        }
                    }
                    else if (nurseEXP[i]=="low") {
                        if(nurse[i][4]>10){
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
    string qualifications[3]={"BA","Master","Assist"};
    double nurse[20][5]={{1,20,1,20,20},{2,40,0.6,10,10},{1,70,1.5,12,15},{0,90,1.8,17,24},{2,100,2,2,22},{1,45,2.75,4,12},{0,49,3,10,12},{1,78,2.4,9,21},{2,282,0.6,11,25},{1,297,1.7,13,6},{1,29,2.9,16,9},{1,60,1.4,12,22},{0,23,1.5,1,6},{1,22,1.9,1,7},{1,28,1.4,3,28},{1,60,2.5,5,18},{1,80,0.7,8,17},{2,10,0.8,2,29},{1,40,1.8,10,22},{1,90,1.98,9,21}};
    int numberOfNurse=20;
    string nurseExp[20];
    for(int i=0;i<numberOfNurse;i++){
        nurseExp[i]=evaluationEXP(qualifications[(int)nurse[i][0]], nurse[i][1], nurse[i][2], nurse[i][3],nurse[i][4]);
        cout<<"nurse"<<i<<" has "<<nurseExp[i]<<" experence."<<endl;
    }
    int outBreak[3] = {1,2,3};
    for (int i=0; i<3; i++) {
        outBreakTest(numberOfNurse, outBreak[i], nurseExp,nurse);
    }
}


