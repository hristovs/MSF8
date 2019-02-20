#include <iostream>
#include <sqlite3.h>
int main()
{	int hourly_patients;
	int nurses_required;
	//A nurse can treat 50 patients per hour. This is obviously a placeholder.
	//It will be refined and this number is what our algorithm will determine once we have data.
	int hourly_nurse_throughput = 50; 
	
	//User enters patients intake per hour 
	std::cout << "Enter amount of patients per hour: ";
	std::cin >> hourly_patients;

	//User enters amount of nurses available
	int nurses_available;
	std::cout << "Enter amount of nurses available: ";
	std:: cin >> nurses_available;

	// We calculate required nurses as a fraction -> Hourly Intake / Hourly Treatment per nurse
	// nurses required truncates the DP, not ideal
	nurses_required = hourly_patients/hourly_nurse_throughput;
	

	//Here we use the implicit casting from bool to int and say 
	//if(remainder_on_division > 0.2) nurses_required++;
	//where remainder_on_division is the (workload/nurses_throughput - nurses_required)
	nurses_required = nurses_required + (((float)hourly_patients/(float)hourly_nurse_throughput)-(float)nurses_required > 0.2);
	




	//We check if we have enough nurses or more or less and we give information based on our results
	int nurses_surplus = nurses_available - nurses_required;
	if(nurses_surplus == 0)
	{
		std::cout << "SUCCESS\n"<< "You will have to assign all nurses here!\n";	
	}

	else if(nurses_surplus > 0)
	{
		std::cout << "SUCCESS\n" <<  "There is a " << nurses_surplus << " nurse surplus!\n";
	}

	else
	{
		std::cout << "ERROR\n" << "THERE AREN'T ENOUGH NURSES TO DEPLOY\n";
		std::cout << "YOU NEED " << nurses_required - nurses_available;
		if(nurses_required - nurses_available == 1)
		{
			std::cout << " MORE NURSE!\n"; 
		}
		else
		{
			std::cout << " MORE NURSES!\n";
		}
	}
}
