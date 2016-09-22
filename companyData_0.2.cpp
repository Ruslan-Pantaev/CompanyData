// Ruslan Pantaev

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

ofstream fout;
string answerIn = "";
char answer = {0};

void addData();

int main()
{
	fout.open("Handy_Hardware_Company_DATA.txt");
	//Not sure if necessary to check if file is open b/c this program will create a new one, regardless
	if (!fout.is_open()){
		cout<< "File not found! " << "\n" 
		<< "Make sure file is in the same directory as the program! "
		<<endl;
		exit(1);
	}

	string numIn = "";
	string custName = "";
	double total = 0;
	double paid = 0;
	double balance = 0;
	double credit = 0;
	double ordersTotal = 0;
	double paidTotal = 0;
	double dueTotal = 0;
	double averageTotal = 0;
	double percentPaid = 0;
	double size = 0;
	int width = 20;

	//setting up the table headings for file output
	fout << left << setw(width) << "Customer Name" << right << setw(width) << "Total ($)" 
				<< right << setw(width) << "Paid off ($)" << right << setw(width) << "balance ($)" << "\n" << endl;

	cout<< "Okay, let's begin!" <<endl;

	addData();

	//using while loop to check user input from addData function
	
	while (answer == 'y'){
		//cin.ignore();
		size += 1; //used to keep track of # of customers to calculate company average
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
			getline(cin, numIn);
			stringstream myStream(numIn);
			if (myStream >> total)
				break;
			cout << "Please enter a valid number! (USD): " <<endl;
		}
		
		while (true) {
			cout<< "Amount paid off (USD): ";
			getline(cin, numIn);
			stringstream myStream(numIn);
			if (myStream >> paid)
				break;
			cout << "Please enter a valid number! (USD): " <<endl;
		}	
		
		balance			= total - paid;
		ordersTotal		+= total;
		paidTotal		+= paid;
		dueTotal		= ordersTotal - paidTotal;
		averageTotal	= paidTotal / size;
		percentPaid		= (paidTotal * 100) / ordersTotal;

		if (total > paid) {
			fout << setprecision (2) << fixed 
				<< left << setw(width) << custName << right << setw(width) << total 
				<< right <<setw(width) << paid << right << setw(width) << balance << endl;
		}
		else {
			credit = abs(balance);
			fout << setprecision (2) << fixed 
				<< left << setw(width) << custName << right << setw(width) << total 
				<< right <<setw(width) << paid << right << setw(width) << "credit: " << credit << endl;
			
		}
		//this IS AN IMPORTANT BUG FIX. Until I reinitialized char answer every loop, I would 
		//randomly get crashes with Segmentation fault: 11
		char answer = {0};
		//calls user prompt "y/n" function again at end of this for loop
		addData();
	}
	//once user breaks out of loop with 'n', the following is additionally printed 
	fout << "\n" << "\n" << "                       - Company Data Summary -" << "\n" << endl;
	fout << left << setw(width - 6) << "Total ($)" << left << setw(width - 6) << "Paid ($)" 
				<< left <<setw(width) << "Balance Due ($)" << left << setw(width) << "Average Paid ($)"
				<< left << setw(width) << "Percent Paid" << endl;

	fout << setprecision (2) << fixed 
		<< left << setw(width - 6) << ordersTotal << left << setw(width - 6) << paidTotal 
		<< left <<setw(width) << dueTotal << left << setw(width) << averageTotal
		<< left << setw(0) << percentPaid << "%" << endl;

	//User exits clean, but gets a friendly prompt 
	cout<< "Congratulations, your 'Handy_Hardware_Company_DATA.txt' file has been created! \n"
		<< "(It can be found in the same directory as this program)" <<endl;
	fout.close();
	//system("PAUSE");
	return 0;
}

void addData(){
	cout << "Would you like to add data for an additional Customer? (y/n) " ;
	while (true){
		getline(cin, answerIn
			);
		cin.clear();

		if (answerIn
			.length() == 1){
			answer = answerIn
		[0];
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

/* Output Example
for 2 customers:

Customer Name                  Total ($)        Paid off ($)         balance ($)

George Takei                       26.75                5.00               21.75
Spock                             349.19                0.31              348.88


                       - Company Data Summary -

Total ($)     Paid ($)      Balance Due ($)     Average Paid ($)    Percent Paid        
375.94        5.31          370.63              2.65                1.41%
____________________________________________________________________________________

*/