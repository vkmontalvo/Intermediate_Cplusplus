//====================================================================================================
// Valerie Montalvo - Week 2 Homework
// Country Club Dues - switch statements, functions and loops.
//====================================================================================================

#include <iostream> 
#include <string> 
#include <iomanip>


using namespace std;


int getYears (); // function to input years of membership
void getName (string &); // function to input member name
void getMemType (char &); // function to input membership type
void display (float, string, string); // function to display results


//=======================================================
// Main Program
//=======================================================
int main()
{
	// initialize variables
	int opselect = 0; // menu selection
	int years = 0; // years of membership
	string name = ""; // member name
	char memType = ' '; // membership type
	float dues = 0.0; // member dues
	int ttlMem = 0; // total members processed during run
	float ttlFDues = 0.0; // total family membership dues processed
	float ttlIDues = 0.0; // total individual membership dues processed
	string memDesc = ""; // membership type description

	// program repeats until user exits
	do
	{
		system("cls"); // clears the screen

		// menu
		cout << "\t\t\t Country Club Dues \n\n";
		cout <<" \t 1. Calculate Dues \n"; 
		cout << "\t 2. Exit \n\n"; 
		cout << " Make a selection: ";
		cin >> opselect;

		// Menu Switch Statement
		switch (opselect)
		{

		// 1. Membership dues
		case 1: 
			{
				cin.ignore(1);
				getName (name);
				getMemType (memType);
				years=getYears();

				// Family membership, less than or equal to 6 years.
				if ( memType == 'F' && years <= 6)
				{
					dues = 1600.00;
					ttlFDues = ttlFDues + dues;
					ttlMem++;
					memDesc = "Family";
				}

				// Family membership, more than 6 years.
				else if ( memType == 'F' && years > 6)
				{
					dues = 1200.00;
					ttlFDues = ttlFDues + dues;
					ttlMem++;
					memDesc = "Family";
				}

				// Individual membership, less than of equal to 6 years.
				else if ( memType == 'I' && years <= 6 )
				{
					dues = 1100.00;
					ttlIDues = ttlIDues + dues;
					ttlMem++;
					memDesc = "Individual";
				}

				// Individual membership, more than 6 years.
				else if ( memType == 'I' && years > 6 )
				{
					dues = 800.00;
					ttlIDues = ttlIDues + dues;
					ttlMem++;
					memDesc = "Individual";
				}

				display (dues, name, memDesc);
				system("pause");
				break;
			}
	
		// 2. Display total summary and exit system.
		case 2: 
			{
				cout << "\n\t\t\t Summary Report \n\n";
				cout << left << setw(36) << "Total Members Processed" << setw(36) << fixed << setprecision(2) << ttlMem << endl;
				cout << left << setw(36) << "Total Family Membership Dues" << setw(36) << fixed << setprecision(2) << ttlFDues << endl;
				cout << left << setw(36) << "Total Individual Membership Dues" << setw(36) << fixed << setprecision(2) << ttlIDues << endl << endl;
				
				system("pause");
				return 0;
			}

		default:
			cout << "\t Invalid Selection \n";
	
		} // End Switch
	} while(1); // End do-while
} // End Main


//=======================================================
// Called Functions
//=======================================================

//== Years value returning function. ==//
int getYears()
{
	int years = 0;
	
	do
	{
		cout << "\t Years of Membership: ";
		cin >> years;

	} while (years < 0);
	
	return years;
} // End getYears


//======= Name void function. =======//
void getName (string &name)
{
	cout<< endl << "\t Enter Name (20 Characters): ";
	getline(cin, name);

	while (name.size() == 0 || name.size() > 20)
	{
		cout<<"Enter Name (20 Characters): ";
		getline(cin, name);
	}
} // End getName


//==== Membership void function. ====//
void getMemType (char &memType)
{
	cout << "\t Membership Type (F/I): ";
	cin >> memType;

	while (memType != 'F' && memType != 'I')
	{
		cout << "\t Membership Type (F/I): ";
		cin >> memType;
	}

} // End getMemType


//===== Display void function. =====//
void display (float dues, string name, string memDesc)
{
	cout << "\n\t" << name << " has a " << memDesc << " membership, and the dues are " << fixed << setprecision(2) << dues << "." << endl << endl;
} // End display
