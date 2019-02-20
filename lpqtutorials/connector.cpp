#include <iostream>
#include <string>
#include <cassert>

#include <pqxx/pqxx>

using namespace pqxx;
using namespace std;
int main(){
try{
	connection C("dbname=nurses user=nursesadmin password=password hostaddr=63.35.110.243 port=5432");

	if(C.is_open()){

		cout << "Database opened successfully: " << C.dbname() << endl;
	}
	else{
		cout<< "Can't open database" << endl;
		return 1;
	}
	C.disconnect();

} catch(const std::exception &e) {
			cerr << e.what() << endl;
			return 1;

			}

}
