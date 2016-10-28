//Ruslan Pantaev

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <iomanip>

using namespace std;

ifstream fIN;
ofstream fOUT;
string answerIN = "";
char answer = {0};
//addDATA functions allows to me loop a program all day long without knowing the number of
//customers there would be. Loop is maintained at every user prompt for "y/n" reply to continue
void addDATA(){
	cout << "Would you like to add data for an additional Customer? (y/n) " ;
	while (true){
		getline(cin, answerIN);
		cin.clear();

		if (answerIN.length() == 1){
			answer = answerIN[0];
			if (answer == 'n'){
				break;
			}
			else if (answer == 'y'){
				break;
			}
			else {
				cout << "You must enter (y/n): ";
			}
		}
		else {
			cout << "You must enter (y/n): ";	
		}	
	}
}

int main()
{
	fOUT.open("companyData.txt");
	// Not necessary to check if file is open b/c this program will create a new one, 
	// but incl for good measure 
	if (!fOUT.is_open()){
		cout<< "File not found! " << "\n" 
		<< "Make sure file is in the same directory as the program! "
		<<endl;
		exit(EXIT_FAILURE);
	}

	string numIN = "";
	string custName = "";
	long double total[0];
	long double paid[0];
	long double balance[0];
	long double credit[0];
	long double ordersTotal;
	long double paidTotal;
	long double dueTotal;
	long double averageTotal;
	long double percentpaid;

	cout<< "Okay, let's begin!" <<endl;
	
	addDATA();

	for (int i = 0; answer == 'y'; ++i){
		//cin.ignore();
		cout<< "Please enter Customer Name: ";
		getline(cin, custName);
		//I wanted to use <cctype>> header to check isalpha() but decided not to
		if (custName.empty() || custName == " ")
			while (custName.empty() || custName == " ") {
				cout << "Please enter a name!: ";
				getline(cin, custName);
			}	
							
		while (true) {
			cout<< "Total of orders placed (USD): ";
			getline(cin, numIN);

			stringstream myStream(numIN);
			if (myStream >> total[i])
				break;
			cout << "Please enter a valid number! (USD): " <<endl;
		}
		
		while (true) {
			cout<< "Amount paid off (USD): ";
			getline(cin, numIN);

			stringstream myStream(numIN);
			if (myStream >> paid[i])
				break;
			cout << "Please enter a valid number! (USD): " <<endl;
		}	

		ordersTotal	+= total[i];
		paidTotal	+= paid[i];
		dueTotal	= ordersTotal - paidTotal;
		balance[i]	= total[i] - paid[i];
		averageTotal	= paidTotal / (i + 1);
		percentpaid	= (paidTotal * 100) / ordersTotal;

		if (total[i] > paid[i]) {

			fOUT << setprecision (2) << fixed << "Customer #" << i + 1 << " : " << custName << "\n" 
				<< "      Total : $" << total[i] << "\n" 
				<< "   Paid off : $" << paid[i] << "\n" 
				<< "    Balance : $" << balance[i] << "\n" <<endl;	
		}
		else {
			credit[i] = balance[i];
			fOUT << setprecision (2) << fixed << "Customer #" << i + 1 << " : " << custName << "\n" 
				<< "      Total : $" << total[i] << "\n" 
				<< "   Paid off : $" << paid[i] << "\n" 
				<< "     Credit : $" << credit[i] << "\n" <<endl;
		}
		//this IS A SUPER IMPORTANT BUG FIX. Until I reinitialized char answer every loop, I would 
		//randomly get crashes with Segmentation fault: 11
		char answer = {0};
		addDATA();
	}

	fOUT << setprecision (2) << fixed 
		<< "COMPANY TOTAL balance of orders PLACED (USD): $" << ordersTotal << "\n"
		<< "COMPANY TOTAL balance of orders paid (USD): $" << paidTotal << "\n"
		<< "COMPANY TOTAL balance DUE: $" << dueTotal << "\n"
		<< "COMPANY average of payments made by customers (USD): $" << averageTotal << "\n" 
		<< "COMPANY PERCENT of total balance paid: " << percentpaid << "%" <<endl;
	//User exits clean, but gets a friendly prompt 
	cout<< "Congratulations, your 'companyData.txt' file has been created! \n"
		<< "(It can be found in the same directory as this program)" <<endl;

	fOUT.close();
	//system("PAUSE");
	return 0;
}
