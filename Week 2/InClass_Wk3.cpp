//====================================================================================================================================
// Valerie Montalvo - In Class
// Week 1 - Developing Visa Card System. Enter SSN (9 digits), Name (20), Address (25).
// Week 2 - Visa Card Company Menu with switch statement and do-while.
// Week 3 - Read/write to a file using fstream - print report.
//====================================================================================================================================

#include <iostream> 
#include <string> 
#include <iomanip>
#include <fstream>

using namespace std;


long getSSN (); // function to input social security number
void getName (string &); // function to input customer name
void getAddress (string &); // function to input customer address
void display (long, string, string); // function to display member report
void displayTitle(); // function to display titles
void newVisa(); // function to enter customer information to apply for a new Visa
void prntRpt(); // function to print reports

// start main program
int main()
{
	// initizialize variables
	int opselect = 0; // user menu selection

	
	do // program repeats until user exits
	{
		system("cls"); // clears the screen
		
		// user menu
		cout << "\t\t\t Visa Card Company \n\n";
		cout <<" \t 1. Apply Visa Card \n";
		cout << "\t 2. Find a Member \n";
		cout << "\t 3. Print Report \n";
		cout << "\t 4. Exit \n\n";
		cout << " Make a selection: ";
		cin >> opselect;

		switch (opselect) // menu switch statement
		{
		case 1: // apply for a new visa
			{
				newVisa(); // calls to function to apply for a visa
				break;
			}
	
		case 2: // find a member
			{
				break;
			}

		case 3: // print a report
			{
				prntRpt(); // calls to function to print report
				break;
			}

		case 4: // exit system
			{
				cout << " Signing Off \n";
				system("pause");
				return 0;
			}

		default:
			cout << " Invalid Selection \n";
	
		} // end switch
	} while(1); // end infinite do-while
} // end main program


//==================== called functions =======================//

// social security number value returning function
long getSSN()
{
	// initialize variables
	long ssn=0; // social security number
	
	do // repeats user entry while invalid
	{
		cout << "\nEnter SSN (9 digits): ";
		cin >> ssn;

	} while (ssn < 100000000 || ssn > 999999999);
	
	return ssn;
} // end ssn


// name entry void function, pass by reference
void getName (string &name)
{
	cout<<"Enter Name (20 Characters): ";
	getline(cin, name);

	while (name.size() == 0 || name.size() > 20) // repeats user entry while invalid
	{
		cout<<"Enter Name (20 Characters): ";
		getline(cin, name);
	}
} // end name

// address entry void function, pass by reference
void getAddress (string &address)
{
	cout<<"Enter Address (25 Characters): ";
	getline(cin, address);

	while (address.size() == 0 || address.size() > 25) // repeats user entry while invalid
	{
		cout<<"Enter Address (25 Characters): ";
		getline(cin, address);
	}

} // end address entry

// display titles void function
void displayTitle()
{
	cout<<"\n\t\tVisa Report\n\n";
	cout<<left<<setw(9)<<setfill(' ')<<"SSN"<<" "<<setw(20)<<"Name"<<" "<<setw(25)<<"Address"<<endl;

} // end display titles

// display member summary void function
void display (long ssn, string name, string address)
{
	cout << left << setw(9) << setfill(' ') << ssn << " " <<setw(20) << name << " " <<setw(25) << address << endl << endl;
	system("pause");

} // end display summary

// apply for a visa void function
void newVisa()
{
	// inititialize variables
	long ssn = 0; // social security number
	string name = ""; // member name
	string address = ""; // member address

	 ofstream outFile; // file complex variable

	 outFile.open("VISACARD.dat",ios::app); // open VISACARD file and append data to the end
	 if (outFile.is_open())  // checks if file is open
	 {
		ssn=getSSN(); // calls to social security entry function
		cin.ignore(1); // ignores \n
		getName (name); // calls to member name entry function
		getAddress (address); // calls to member address entry function
		display (ssn, name, address); // calls to display member summary function

		outFile << ssn << '#' << name << '#' << address << '#' << endl; // writes user input to VISACARD
	 }

	 else // if file is not open, display error
	 {
		 cout << "\n\t File VISACARD not opened." << endl;
	 }
	 
	 outFile.close(); // close opened file

} // end new visa

// function to read from a file and print a report
void prntRpt()
{
	// inititialize variables
	long ssn = 0; // social security number
	string name = ""; // member name
	string address = ""; // member address

	ifstream inFile; // file i/o complex variable
	inFile.open("VISACARD.dat", ios::in); // opens VISACARD and reads from it

	if(inFile.is_open())
	{
		displayTitle();
		inFile >> ssn;

		while(!inFile.eof()) // while not the end of the file
		{
			inFile.ignore(1); // ignores '#'
			getline(inFile, name, '#'); // reads name, ignores '#'
			getlint(inFile, address, '#'); // reads address, ignores '#'
			inFile.ignore(1); // ignores '\n'
			display (ssn, name, address); // calls to display variables function
			inFile >> ssn; // loops while
		}
} // end prntRpt

