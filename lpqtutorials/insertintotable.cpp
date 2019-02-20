#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(){
	char * sql;
	char * sql2;
	char * sql3;
	char * sql4;
	try {
		connection C("dbname=testdatabase user=testadmin password=password hostaddr=63.34.244.203 port=5432");

	if(C.is_open()){
	cout << "Opened database successfully: " << C.dbname() << endl;}
	else{
	cout << "Can't open database" << endl;
	return 1;
	}

	sql =(char *) "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES(1,'Paul', 32, 'California', 20000.00);"; 		
	sql2 = (char *)"INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES(2,'Allen', 25, 'Texas', 15000.00);";
        sql3 =(char *) "INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES(3, 'Teddy', 23, 'Norway', 20000.00);";
        sql4 =(char *)"INSERT INTO COMPANY(ID,NAME,AGE,ADDRESS,SALARY) VALUES(4, 'Mark', 25, 'Richmond', 65000.00);";

	work W(C);

	W.exec( sql );
	W.exec( sql2 );
	W.exec( sql3 );
	W.exec( sql4 );
	W.commit();
	cout << "Records created successfully!" << endl;
	C.disconnect();
	}catch(const std::exception &e) {
		cerr<<e.what() << endl;
		return 1;

	}

return 0;
}
