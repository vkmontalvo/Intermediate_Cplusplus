//====================================================================================================================================
// Valerie Montalvo - Homework, Week 4
// Final grades input, save to a file and display records, with accumulators.
//====================================================================================================================================

#include <iostream> 
#include <string> 
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

void inGrades(string, int, char); // function to input student grades
int getGrades(); // function to calculate letter grade
string getName(); // function to input name
void prntRpt(); // function to print student grades report
void display (string, char); // function to display student report
void displayTitle(); // function to display titles


int main()
{
	// initizialize variables
	int opselect = 0; // user menu selection
	int ttlStudent = 0; // total students entered
	int ttlScore = 0; // total score from all students entered
	int ttlA = 0; // total number of A's
	int ttlB = 0; // total number of B's
	int ttlC = 0; // total number of C's
	int ttlD = 0; // total number of D's
	int ttlF = 0; // total number of F's
	float avg = 0.0; // average score for all students entered
	string name = ""; // student name
	int score = 0; // student test score
	char grade = ' '; // student letter grade
	
	do // program repeats until user exits
	{
		system("cls"); // clears the screen
		
		// user menu
		cout << "\t\t\t Student Test Grades \n\n";
		cout <<" \t 1. Enter Grades \n";
		cout << "\t 2. Report Grades \n";
		cout << "\t 3. Exit \n\n";
		cout << " Make a selection: ";
		cin >> opselect;

		switch (opselect) // menu switch statement
		{
		case 1: // enter grades
			{
				ttlStudent++; // adds to total number of students
				cin.ignore(1);
				name = getName(); // calls to function to input student name
				score = getGrades(); // calls to function to input student test score
				ttlScore = ttlScore + score; // adds the scores together
				avg = ttlScore / ttlStudent; // averages all scores

				// letter grade if statements
				if (score >= 90 && score <= 100)
				{
					grade = 'A';
					ttlA++;
				}

				else if (score >= 80 && score <= 89)
				{
					grade = 'B';
					ttlB++;
				}

				else if (score >= 70 && score <= 79)
				{
					grade = 'C';
					ttlC++;
				}

				else if (score >= 60 && score <= 69)
				{
					grade = 'D';
					ttlD++;
				}
				
				else if (score < 60)
				{
					grade = 'F';
					ttlF++;
				}

				inGrades(name, score, grade); // calls to function to input student test information to a file
				break;
			}

		case 2: // print a report
			{
				prntRpt(); // calls to function to print report
				break;
			}

		case 3: // display usage and exit system
			{
				cout << endl << left << setw(30) << setfill(' ') << "Total students processed" << " " 
				             << setw(5) << ttlStudent << endl 
							 << setw(30) << setfill(' ') << "Total students receiving an A" << " "
							 << setw(5) << ttlA << endl
							 << setw(30) << setfill(' ') << "Total students receiving a B" << " "
							 << setw(5) << ttlB << endl
							 << setw(30) << setfill(' ') << "Total students receiving a C" << " "
							 << setw(5) << ttlC << endl
							 << setw(30) << setfill(' ') << "Total students receiving a D" << " "
							 << setw(5) << ttlD << endl
							 << setw(30) << setfill(' ') << "Total students receiving a F" << " "
							 << setw(5) << ttlF << endl
							 << setw(30) << setfill(' ') << "Average score for this class" << " "
							 << setw(5) << avg << endl << endl;

				system("pause");
				return 0;
			}

		default:
			{
				cout << " Invalid Selection \n";
			    break;
			}
	
		} // end switch
	} while(1); // end infinite do-while
} // end main program

// function to input and format student name
string getName()
{
	int position = 0; // name character position
	string name = "";

	do
	{
		cout<<"Enter Name (20 Characters): ";
		getline(cin, name);

	} while (name.size() == 0 || name.size() > 20); // repeats user entry while invalid

	transform(name.begin(), name.end(), name.begin(), tolower); // transforms all characters to lowercase
	name [0] = toupper(name[0]); // transforms first letter to uppercase
	position = name.find(" ", 0)+1; // finds first space and goes to next character
	name [position] = toupper(name [position]); // transforms second part of two part name to uppercase

	return name;

} // end getName


// function to input grade information into a file
void inGrades(string name, int score, char grade)
{
	ofstream outFile; // complex file i/o variable

	outFile.open("GRADES.dat", ios::app); // opens GRADES and appends to it
		if (outFile.is_open())
		{
			cout << endl;
			display (name, grade); // calls to display function

			system ("PAUSE");

			outFile << name << '#' << score << '#' << endl; // writes variables into the file
		}

		else
		{
		 cout << "\n\t File GRADES not opened." << endl;
	    }

		outFile.close(); // closes the file
} // end inGrades


// display titles void function
void displayTitle()
{
	cout << "\n\t\t CLASS GRADE REPORT \n\n";
	cout << left << setw(20) << setfill(' ') << "Name" << " " 
				 << setw(5) << "Grade" << endl << endl;

} // end displayTitle


// function to display student report
void display (string name, char grade)
{
	cout << left << setw(20) << setfill(' ') << name << " "
				 << setw(5) << grade;
} // end display


// function to enter student test scores
int getGrades ()
{
	// initialize variables
	int score = 0;

		do
		{
			cout << "Enter Test Score (0-100): ";
			cin >> score;
		} while ( score > 100);

		return score;
} // end getGrades


// function to read from a file and print a report
void prntRpt()
{
	// inititialize variables
	string name = ""; // student name
	int score = 0; // student test score
	char grade = ' ';

	ifstream inFile; // file i/o complex variable
	inFile.open("GRADES.dat", ios::in); // opens GRADES and reads from it

	if(inFile.is_open())
	{
		displayTitle();
		getline(inFile, name, '#');

		while(!inFile.eof()) // while not the end of the file
		{
			inFile >> score;

			// letter grade conversion if statements
				if (score >= 90 && score <= 100)
				{
					grade = 'A';
				}

				else if (score >= 80 && score <= 89)
				{
					grade = 'B';
					
				}

				else if (score >= 70 && score <= 79)
				{
					grade = 'C';
					
				}

				else if (score >= 60 && score <= 69)
				{
					grade = 'D';
					
				}
				
				else if (score < 60)
				{
					grade = 'F';
					
				}

			inFile.ignore(1); // ignores '#' \n
			display (name, grade); // calls to display variables function
			getline(inFile, name, '#'); // loops while
		}

		cout << endl << endl;
		system("pause");
	}

	else
	{
		cout << "\n File GRADES not opened." << endl;
	}

} // end prntRpt