//===================================================
// Valerie Montalvo, Homework Week 9
// GPA Entry and Search
//===================================================

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const int NUMEL = 50; // max size of student ID array

void newEntry(); // function to input new student record
void prntRpt(); // function to print student records
int getID(); // function to input the student ID number
void getName(string &, string &); // function to input student name
void getGPA(float &); // function to input student GPA
void properName (string &); // function to convert names to proper case
void findStudent (); // function to find a student by ID
void bubbleSort (string [], int); // function to sort students into array
int binarySearch(int [], int, int); // function to search for a student
void prntStanding (float, string, string); // function to print the student academic standing
void displayTitle(); // function to display report titles
void display (int, string, string, float); // function to display student information

// start main program
int main()
{
	// variables
	int opselect = 0; // user menu input

	do
	{
		system("CLS"); // clears screen

		// user menu
		cout << "\t\t\t NEIT Registrar's Office" << endl;
		cout << "\t\t        Student Academic Records" << endl << endl;
		cout << "\t 1. Student GPA Entry" << endl;
		cout << "\t 2. Print Student Records" << endl;
		cout << "\t 3. Search Student Status" << endl;
		cout << "\t 4. Exit" << endl << endl;
		cout << " Make a Selection: ";
		cin >> opselect;

		switch (opselect) // menu switch statement
		{
		case 1: // student info entry
			{
				newEntry();
				break;
			}

		case 2: // print student records
			{
				prntRpt();
				break;
			}

		case 3: // search student
			{
				findStudent();
				break;
			}

		case 4: // user exit
			{
				cout << " Signing off..." << endl << endl;
				system("PAUSE");
				return 0;
			}

		default:
			{
				cout << " Invalid Selection." << endl;
				system("PAUSE");
				break;
			}
		} // end switch statement

	} while (1); // program repeats until user exits
} // end main

//==================== functions =======================//

void newEntry() // function to input new student data
{
	// variables
	int studID = 0; // student ID number
	string lastName = ""; // student last name
	string firstName = ""; // student first name
	float gpa = 0.0; // student GPA

	system("CLS");
	cin.ignore(1);
	cout << "\t\t\t NEIT Registrar's Office" << endl;
	cout << "\t\t            New Student Entry" << endl << endl;

	ofstream outFile;

	outFile.open("StudentGPA.txt",ios::app); // opens StudentGPA file and appends to the end
	if (outFile.is_open())
	{
		studID = getID(); // calls to function to input student ID
		cin.ignore(1);
		getName(firstName, lastName); // calls to function to input student name
		getGPA (gpa); // calls to function to input student GPA

		outFile << studID << '#' << lastName << '#' << firstName << '#' << gpa << '#' << endl; // writes user input to StudentGPA

		cout << " Saved successfully." << endl << endl;
		system("PAUSE");
	}

	else // if file is not opened, display error
	{
		cout << " Error: file not opened." << endl;
	}

	outFile.close(); // closes open file

} // end newEntry

void prntRpt() // function to print out student records
{
	// variables
	int studID = 0; // student ID number
	string lastName = ""; // student last name
	string firstName = ""; // student first name
	float gpa = 0.0; // student GPA

	system("CLS");
	cin.ignore(1);
	cout << "\t\t\t NEIT Registrar's Office" << endl;
	cout << "\t\t            Student Records" << endl << endl;

	ifstream inFile;
	displayTitle();

	inFile.open("StudentGPA.txt",ios::in); // opens and reads from StudentGPA file
	if (inFile.is_open())
	{
		inFile >> studID;

		while (!inFile.eof())
		{
			inFile.ignore(1);
			getline(inFile,lastName,'#');
			getline(inFile,firstName,'#');
			inFile >> fixed >> setprecision(2) >> gpa;
			inFile.ignore(2);
			display (studID, lastName, firstName, gpa);
			inFile >> studID; // loops the while
		}
	}

	else // display an arror if the file was not opened
	{
		cout << " Error: file not opened." << endl;
		system("PAUSE");
	}

	inFile.close(); // close the opened file
	system("PAUSE");

}

void display (int id, string last, string first, float gpa) // function to display student records
{
	cout << left << setw(4) << setfill(' ') << id << " " 
				 << setw(15) << last << " " 
				 << setw(15) << first << " " 
			     << setw(4) << fixed << setprecision(2) << gpa << endl;
}

void displayTitle() // function to display titles
{
	cout << left << setw(4) << setfill(' ') << "ID" << " " 
				 << setw(15) << "Last Name" << " " 
				 << setw(15) << "First Name" << " " 
				 << setw(4) << "GPA" << endl << endl;
} // end displayTitle

int getID() // function to input student ID 
{
	int id = 0; // student ID

	do
	{
		cout << endl << "\t Student ID Number: ";
		cin >> id;

	} while (id <= 100 || id >= 999); // repeats until user enters a number between 100 and 999

	return id;
} // end getID

void getName (string &first, string &last) // function to enter student name
{
	do
	{
		cout << "\t First Name: ";
		getline(cin,first);
	} while (first.size() == 0); // repeats until user enters something

	properName (first); // calls to function to transform names to proper case

	do
	{
		cout <<"\t Last Name: ";
		getline(cin,last);
	} while (last.size() == 0); // repeats until user enters something

	properName (last); // calls to function to transform names to proper case
} // end getName

void properName (string &strData) // function to transform names to proper case
{
	int position = 0; // name character position

	transform(strData.begin(), strData.end(), strData.begin(), tolower); // transforms all characters to lowercase

	do
	{
		strData [position] = toupper(strData[position]); // transforms first letter to uppercase
		position = strData.find(" ", position)+1; // finds first space and goes to next character

	} while (position != 0);

} // end properName

void getGPA (float &gpa) // function to input student GPA
{
	do
	{
		cout << "\t Student GPA (0.0 - 4.0): ";
		cin >> gpa;

		if (gpa < 0.00 || gpa > 4.00) // prints an error if the GPA is not within range
		{
			cout << endl << "Invalid GPA." << endl;
		}
	} while (gpa < 0.00 || gpa > 4.00); // repeats until a correct GPA is entered
} // end getGPA

void findStudent () // function to search for a student
{
	int arrID[NUMEL]={0}; // int ID array
	float arrGPA[NUMEL]={0.0}; // float GPA array
	string arrName[NUMEL]={""}; // string first name array
	string arrLName [NUMEL] = {""}; // string last name array
	int studID = 0; // student ID number
	string lastName = ""; // student last name
	string firstName = ""; // student first name
	float gpa = 0.0; // student GPA
	int findID = 0; // search input to find student ID number
	int index = 0; // array index
	int location = 0; // index location of search results
	float standing = 0.0; // GPA from searched location
	string first = ""; // first name from searched location
	string last = ""; // last name from searched location

	system("CLS");
	cin.ignore(1);
	cout << "\t\t\t NEIT Registrar's Office" << endl;
	cout << "\t\t\t Search Student Records" << endl << endl;

	ifstream inFile;

	inFile.open("StudentGPA.txt",ios::in); // opens and reads from StudentGPA file
	if (inFile.is_open())
	{
		inFile >> studID;
		arrID[index]=studID; // sorts the student IDs into an array

		while (index < NUMEL && !inFile.eof())
		{
			inFile.ignore(1);
			getline(inFile,lastName,'#');
			arrLName[index]=lastName;
			getline(inFile,firstName,'#');
			arrName[index]=firstName; // sorts the student first names into an array
			inFile >> fixed >> setprecision(2) >> gpa;
			arrGPA[index]=gpa; // sorts the gpa into an array
			inFile.ignore(2);

			index++; // adds 1 to the array indexes

			inFile >> studID; // loops the while
			arrID[index]=studID; // sorts the student IDs into an array
		}
	}

	else // display an arror if the file was not opened
	{
		cout << " Error: file not opened." << endl;
		system("PAUSE");
	}

	inFile.close(); // close the opened file

	cout << "\t Search Student ID: ";
	cin >> findID;

	location = binarySearch(arrID, index, findID); // calls to the function to find the index location of the desired student ID

	if (location > -1) // if the ID was found
	{
		standing = arrGPA[location]; // finds the GPA from the same location
		first = arrName[location]; // finds the first name from the same location
		last = arrLName[location]; // finds the last name from the same location

		prntStanding (standing, first, last); // calls to the function to print out the student academic standing
	}

	else // if the student ID was not found
	{
		cout << endl << " The student ID was not located." << endl << endl;
	}

	cout << endl;
	system("PAUSE");
} // end findStudent

int binarySearch(int list[], int size, int key) // function to search the ID array and return the search location
{   
	int left = 0;
	int right = 0; 
	int midpt = 0;   
	right = size - 1;   
	while (left <= right)   
	{     
		midpt = (int) ((left + right) / 2);     
		if (key == list[midpt])     
		{       
			return midpt;     
		}     
		
		else if (key > list[midpt])       
			{ 
				left = midpt + 1;
			}
		
		else       
		{
			right = midpt - 1;   
		}
	}// end while   
	
	return -1; 

}// end binarySearch

void prntStanding (float studGPA, string first, string last) // function to print the academic standing of the student
{
	if (studGPA > 3.65)
	{
		cout << endl << " " << first << " " << last << " is on the Dean's List." << endl;
	}

	else if (studGPA >= 2.00 && studGPA <= 3.65)
	{
		cout << endl << " " << first << " " << last << " is an average student." << endl;
	}

	else 
	{
		cout << endl << " " << first << " " << last << " is on Academic Probation." << endl;
	}
} // end prntStanding



