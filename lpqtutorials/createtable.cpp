#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(){

	 string sql;
	
	try{
	connection C("dbname=testdatabase user=testadmin password=password hostaddr=63.34.244.203 port=5432");
	if(C.is_open()){
		cout << "Opened database successfully: " << C.dbname() << endl;
	}
	else{
		cout << "Can't open the goddamn database!!!!" << endl;
		return 1;
	}
	sql = "CREATE TABLE COMPANY(ID INT PRIMARY KEY 	NOT NULL, NAME TEXT NOT NULL, AGE INT NOT NULL, ADDRESS CHAR(50),SALARY REAL );";		 // sql statement

	work W(C); 					//create transactional object

	W.exec( sql );					//execute sql query
	W.commit();
	cout << "Table created successfully!" << endl;
	C.disconnect ();
	}
	catch( const std::exception &e){
		cerr << e.what() << std::endl;
	return 1;
	}
	return 0;
}
