#include <iostream>
#include <string>
#include <sqlite3.h>
#include <unistd.h>
using namespace std;

void assess(int patientIntake, int exp, int available){
	int hourlyPatients = patientIntake;
	int experience = exp;
	int nursesRequired;
	int availableNurses = available;
	//A nurse can treat 50 patients per hour. This is obviously a placeholder.
	//It will be refined and this number is what our algorithm will determine once we have data.
	int hourlyNurseThroughput = 10 * exp; 
	
	// We calculate required nurses as a fraction -> Hourly Intake / Hourly Treatment per nurse
	// nurses required truncates the DP, not ideal
	nursesRequired = hourlyPatients/hourlyNurseThroughput;
	

	//Here we use the implicit casting from bool to int and say 
	//if(remainder_on_division > 0.2) nurses_required++;
	//where remainder_on_division is the (workload/nurses_throughput - nurses_required)
	nursesRequired = nursesRequired + (((float)hourlyPatients/(float)hourlyNurseThroughput)-(float)nursesRequired > 0.2);
	




	//We check if we have enough nurses or more or less and we give information based on our results
	int nurseSurplus = availableNurses- nursesRequired;
	if(nurseSurplus == 0)
	{
		cout << "SUCCESS\n"<< "You will have to assign all nurses here!\n";	
	}

	else if(nurseSurplus > 0)
	{
		cout << "SUCCESS\n" <<  "There is a " << nurseSurplus << " nurse surplus!\n";
	}

	else
	{
		cout << "ERROR\n" << "THERE AREN'T ENOUGH NURSES TO DEPLOY\n";
		cout << "YOU NEED " << nursesRequired - availableNurses;
		if(nursesRequired - availableNurses == 1)
		{
			cout << " MORE NURSE!\n"; 
		}
		else
		{
			cout << " MORE NURSES!\n";
		}
	}
	cout << endl << endl;

}

int main()
{
	cout << "Welcome to the simulator..." << endl;
	cout << "Input 0 to exit at any time." << endl << endl;
	int sim;
	int exp;
	int availableNurses;
	while(true){
	cout << "Please choose between 4 crisis scenarios:"<<endl;
	cout << "1: Cholera Outbreak" << endl;
	cout << "2: Ebola Outbreak" << endl;
	cout << "3: Marburg Fever" << endl;
	cout << "4: Meningitis C" << endl; 
	cout << "Crisis: ";
	cin >> sim;
	if(sim == 0) return 0;

	cout << endl;
	cout << "Please choose degree of nurse experience:" << endl;
	cout << "1: Inexperienced Nurses" << endl;
	cout << "2: Mixed" << endl;
	cout << "3: Experienced" << endl;
	cout << "4: Very Experienced" << endl;
	cout << "Experience: ";
	cin >>  exp;
	if(exp == 0) return 0;

	cout << "Enter available nurses: ";
	cin >> availableNurses;	
	if(availableNurses == 0) return 0;
	
	sim = sim*150;
	cout << endl << endl;
	
	cout << "Please wait while we crunch some numbers..." << endl;
	cout << "In the meantime, please consider donating at https://secure.msf.ie/" << endl;
	cout << endl << endl;

	unsigned int microseconds = 5000000;
	usleep(microseconds);
        assess(sim,exp,availableNurses);
	}

}
