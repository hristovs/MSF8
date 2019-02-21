#include <iostream>
#include <pqxx/pqxx>
#include "Select.h"
#include <cstring>
using namespace pqxx;
using namespace std;
Select::Select(string selectParams){
	selectString = selectParams;
//	notFinished = true;
}

string Select::resultingString(){

	return resultString;
}

void Select::queryDatabase(){
	try{
	string sql = selectString;
        cout<<sql<<endl;
	connection C(connectionString);
	if (C.is_open()) {
       	 cout << "Opened database successfully: " << C.dbname() << endl;
      } 
	else {
       	 cout << "Can't open database" << endl;
      }
  /* Create a non-transactional object. */
      nontransaction N(C);

      /* Execute SQL query */
      result R= N.exec(sql);
      resultString = "";
      for(result::const_iterator row = R.begin(); row!=R.end(); row++){
          for(int i=0;i<row.size();i++){
              cout<<row[i].as<string>()<<endl;
  	 	}
      }
	
      cout<<"Operation done successfully!" << endl;
      C.disconnect();
      }catch(const exception &e){
       	cerr<< e.what() << endl;
	}
//	notFinished = false;
}


void Select::setConnectionParameters(string dbname,string account, string password, string endpoint, int port){
	string template1 = "dbname=";
	string template2 = " user=";
	string template3 = " password=";
	string template4 = " hostaddr=";
	string template5 = " port=";
	connectionString =template1+dbname+template2+account+template3+password+template4+endpoint+template5+to_string(port);
}

