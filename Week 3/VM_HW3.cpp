//===============================================================================================
// Valerie Montalvo - Homework 3
// Airline Flight Data File - Read/Write with file I/O stream
//===============================================================================================

#include <iostream> 
#include <string> 
#include <iomanip>
#include <fstream>
#include <ctype.h>

using namespace std;

void getCode (char &); // function to input flight code
void display (int, string, string, int, char); // function to display flight data
void displayTitle (); // function to display flight data titles
void prntRpt (); // function to print all file flight data to screen
void newData (); // function to enter new flight data

// MAIN PROGRAM
int main()
{
	// initialize variables
	int opselect = 0; // user menu selection

	do // program repeats until user exits
	{
		system ("cls"); // clears the screen

		// user menu
		cout << "\t\t\t Tech Air Dispatch \n\n";
		cout << "\t\t 1. Enter Flight Data \n";
		cout << "\t\t 2. Print Report \n";
		cout << "\t\t 3. Exit \n\n";
		cout << "\t Make a selection: ";
		cin >> opselect;

		switch (opselect) // menu switch statement
		{
		case 1: // enter new flight data
			{
				newData (); // calls to funtion to enter data
				break;
			}

		case 2: // display all stored data
			{
				prntRpt(); // calls to function to print report
				break;
			}

		case 3: // exit system
			{
				cout << "\n Signing Off... \n\n";
				system ("pause");
				return 0;
			}

		default:

				cout << "\n Invalid Selection \n";
		} // end switch statement
	
	} while (1); // end infinite do-while

} // END MAIN

// =============================== CALLED FUNCTIONS ====================================

// INPUT FLIGHT CODE FUNCTION
void getCode ( char & code)
{
	do
	{
		cout << "\t Flight Code (O/D/C): ";
		cin >> code;

		code = toupper(code);

	} while ( code!='O' && code!='D' && code!='C' );

} // END GETCODE

// DISPLAY FLIGHT DATA FUNCTION
void display (int flightNum, string origin, string dest, int pass, char code)
{
	cout << left << setw(15) << setfill(' ') << flightNum << " " << setw(15) << origin << " " << setw(15) << dest << " " << setw(15) << pass << " " << setw(15) << code << endl;

} // END DISPLAY

// DISPLAY FLIGHT DATA TITLES FUNCTION
void displayTitle()
{
	cout << "\n\t\t Flight Data Report \n\n";
	cout << left<< setw(15) << setfill(' ') << "Flight No." << " " << setw(15) << "Origin" << " " << setw(15) << "Destination"<< " " << setw(15) << "Passengers" << " " << setw(15) << "Code"<< endl << endl;


} // END DISPLAYTITLE


// PRINT FLIGHT REPORT FUNCTION
void prntRpt()
{
	// initialize variables
	int flightNum = 0; // flight number
	string origin = ""; // flight origin
	string dest = ""; // flight destination
	char code = ' '; // flight code
	int pass = 0; // number of passengers

	ifstream inFile; // file to be read
	inFile.open ("airline_data.dat", ios::in); // opens flight_data and begins reading

	if (inFile.is_open())
	{
		displayTitle(); // displays data titles
		inFile >> flightNum; 

		while (!inFile.eof()) // repeats while there is data still in the file
		{
			inFile.ignore(1); 
			getline(inFile, origin, '#'); 
			getline(inFile, dest, '#'); 
			inFile >> pass;
			inFile.ignore(1);
			inFile >> code;
			inFile.ignore(2);

			display (flightNum, origin, dest, pass, code); // displays read flight data under the titles
			

			inFile >> flightNum;
		}
		cout << endl;
		system ("pause");

	}

	else
	{
		cout << "\n\t File airline_data.dat not opened." << endl;
		system ("pause");
	}

} // END PRNTRPT


// NEW FLIGHT DATA ENTRY FUNCTION
void newData()
{
	// initialize variables
	int flightNum = 0; // flight number
	string origin = ""; // flight origin
	string dest = ""; // flight destination
	char code = ' '; // flight code
	int pass = 0; // number of passengers

	ofstream outFile; // write to file

	outFile.open ("airline_data.dat", ios::app); // open airline_data file and append

	if (outFile.is_open()) // checks to see if the file is open
	{
		cout << "\n\t Flight Number: ";
		cin >> flightNum;
		
		cin.ignore(1);
		cout << "\t City of Origin: ";
		getline (cin, origin);

		cout << "\t Destination City: ";
		getline (cin, dest);

		cout << "\t Number of Passengers: ";
		cin >> pass;

		getCode(code); // calls to flight code input function
		cout << endl;

		display (flightNum, origin, dest, pass, code); // displays flight data
		system ("pause");

		outFile << flightNum << '#' << origin << '#' << dest << '#' << pass << '#' << code << '#' << endl; // writes user input to flight_data
	}

	else // if the file is not open, display error
	{
		cout << "\n\t File airline_data.dat not opened." << endl;
		system ("pause");
	}

	outFile.close(); // close opened file

} // END NEWDATA