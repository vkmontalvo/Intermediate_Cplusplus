//====================================================================================================================================
// Valerie Montalvo - In Class
// Week 1 - Developing Visa Card System. Enter SSN (9 digits), Name (20), Address (25).
// Week 2 - Visa Card Company Menu with switch statement and do-while.
//====================================================================================================================================

#include <iostream> 
#include <string> 
#include <iomanip>


using namespace std;

//  Function to enter SSN.
long getSSN ();
// Function to enter name.
void getName (string &);
// Fuction to enter address.
void getAddress (string &);
// Function to display results.
void display (long, string, string);
// Function to call to other functions.
void newVisa();

// Start main program
int main()
{
	// Variables
	int opselect = 0;

	do
	{
		system("cls");
		//Menu
		cout << "\t\t\t Visa Card Company \n\n";
		cout <<" \t 1. Apply Visa Card \n";
		cout << "\t 2. Find a Member \n";
		cout << "\t 3. Print Report \n";
		cout << "\t 4. Exit \n\n";
		cout << " Make a selection: ";
		cin >> opselect;

		// Menu Switch Statement
		switch (opselect)
		{

		// 1. Apply for a Visa
		case 1: 
			{
				newVisa();
				break;
			}
	
		// 2. Find Member
		case 2: 
			{
				break;
			}

		// 3. Print Report
		case 3:
			{
				break;
			}

		// 4. Exit system
		case 4:
			{
				cout << " Signing Off \n";
				system("pause");
				return 0;
			}

		default:
			cout << " Invalid Selection \n";
	
		} // End Switch
	} while(1); // End do-while
} // End Main

// SSN value returning function.
long getSSN()
{
	long ssn=0;
	
	do
	{
		cout << "\nEnter SSN (9 digits): ";
		cin >> ssn;

	} while (ssn < 100000000 || ssn > 999999999);
	
	return ssn;
}

// Name void function.
void getName (string &name)
{
	cout<<"Enter Name (20 Characters): ";
	getline(cin, name);

	while (name.size() == 0 || name.size() > 20)
	{
		cout<<"Enter Name (20 Characters): ";
		getline(cin, name);
	}
}

// Address void function.
void getAddress (string &address)
{
	cout<<"Enter Address (25 Characters): ";
	getline(cin, address);

	while (address.size() == 0 || address.size() > 25)
	{
		cout<<"Enter Address (25 Characters): ";
		getline(cin, address);
	}

}

// Display void function.
void display (long ssn, string name, string address)
{
	cout<<"\n\t\tVisa Report\n\n";
	cout<<left<<setw(9)<<setfill(' ')<<"SSN"<<" "<<setw(20)<<"Name"<<" "<<setw(25)<<"Address"<<endl;
	cout << left << setw(9) << setfill(' ') << ssn << " " <<setw(20) << name << " " <<setw(25) << address << endl << endl;
	system("pause");
}

// Visa call function.
void newVisa()
{
	long ssn = 0;
	string name = "";
	string address = "";
				
	ssn=getSSN();
	cin.ignore(1);
	getName (name);
	getAddress (address);
	display (ssn, name, address);
}