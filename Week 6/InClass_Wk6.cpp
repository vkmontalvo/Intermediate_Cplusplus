//====================================================================================================================================
// Valerie Montalvo - In Class
// Week 1 - Developing Visa Card System. Enter SSN (9 digits), Name (20), Address (25).
// Week 2 - Visa Card Company Menu with switch statement and do-while.
// Week 3 - Read/write to a file using fstream - print report.
// Week 4 - Adding random Visa number and proper name case.
// Week 6 - Adding a proper name case function.
// Week 7 - Sorting names into an array.
// Week 8 - Adding binary search to find member.
// Week 9 - Adding structures
//====================================================================================================================================

#include <iostream> 
#include <string> 
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Visa_Acct_info
{
	long ssn;
	string name;
	string address;
	int visa_num;
};



const int NUMEL=50; // max size of name array


long getSSN (); // function to input social security number
void getName (string &); // function to input customer name
void getAddress (string &); // function to input customer address
void display (long, string, string, int); // function to display member report
void displayTitle(); // function to display titles
void newVisa(); // function to enter customer information to apply for a new Visa
void prntRpt(); // function to print reports
int VisaNum(); // function to generate visa number
void propName (string &); // function to transform name to proper case
void findMem (); // function to find member name
void bubbleSort (Visa_Acct_info[], int); // function to sort card member names into an array
int binarySearch(Visa_Acct_info[], int, string); // function to search for member

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
				findMem();
				break;
			}

		case 3: // print a report
			{
				prntRpt(); // calls to function to print report
				break;
			}

		case 4: // exit system
			{
				cout << "\n Signing Off... \n\n";
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
	
	propName (name); // calls to proper name case function

} // end name


// proper name trasform function
void propName (string &strData)
{
	int position = 0; // name character position

	transform(strData.begin(), strData.end(), strData.begin(), tolower); // transforms all characters to lowercase

	do
	{
		strData [position] = toupper(strData[position]); // transforms first letter to uppercase
		position = strData.find(" ", position)+1; // finds first space and goes to next character

	} while (position != 0);

} // end propName


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
	cout << "\n\t\tVisa Report\n\n";
	cout << left << setw(9) << setfill(' ') << "SSN" << " " 
				 << setw(20) << "Name" << " " 
				 << setw(25) << "Address" << " " 
				 << setw(5) << "Visa" << endl << endl;

} // end display titles

// display member summary void function
void display (long ssn, string name, string address, int vn)
{
	cout << left << setw(9) << setfill(' ') << ssn << " " 
				 << setw(20) << name << " " 
				 << setw(25) << address << " " 
				 << setw(5) << vn << endl;

} // end display summary

// apply for a visa void function
void newVisa()
{
	// inititialize variables
	long ssn = 0; // social security number
	string name = ""; // member name
	string address = ""; // member address
	int visa_num = 0; // visa number

	 ofstream outFile; // file complex variable

	 outFile.open("VISACARD.dat",ios::app); // open VISACARD file and append data to the end
	 if (outFile.is_open())  // checks if file is open
	 {
		ssn=getSSN(); // calls to social security entry function
		cin.ignore(1);
		getName (name); // calls to member name entry function
		getAddress (address); // calls to member address entry function
		visa_num=VisaNum(); // calls to visa number generator function
		cout << endl;
		display (ssn, name, address, visa_num); // calls to display member summary function
		system("pause");

		outFile << ssn << '#' << name << '#' << address << '#' << visa_num << '#' << endl; // writes user input to VISACARD

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
	int vn = 0; // visa number
	int x = 0; // array subscript


	ifstream inFile; // file i/o complex variable
	inFile.open("VISACARD.dat", ios::in); // opens VISACARD and reads from it

	if(inFile.is_open())
	{
		displayTitle(); // calls to display titles function
		inFile >> ssn;

		while(!inFile.eof()) // while not the end of the file
		{
			inFile.ignore(1); // ignores '#'
			getline(inFile, name, '#'); // reads name, ignores '#'
			getline(inFile, address, '#'); // reads address, ignores '#'
			inFile >> vn;
			inFile.ignore(2); // ignores '#' \n
			display (ssn, name, address, vn); // calls to display variables function
			inFile >> ssn; // loops while
		}

		cout << endl;	
	}

	else
	{
		cout << "\n File VISACARD not opened." << endl;
	}

	inFile.close();
	system("pause");

} // end prntRpt

// function to randomly generate visa number
int VisaNum()
{
	int vn = 0; // visa number
	
	srand(time(NULL)); // random number generator seed
	vn = 10000 + rand()%(99999 -10000 +1); // generates a random number between 10000 and 99999

	 
	return vn;
} // end VisaNum

// function to find card members
void findMem()
{
	Visa_Acct_info ArrRec[NUMEL]={0,"","",0};
	long ssn=0; // social security number
	string name=""; // card member name
	string address=""; // card member address
	int vn = 0; // visa number
	int index = 0; // name array index
	string findName = ""; // name search
	int location = 0; // index location of search results

	cin.ignore(1);

	ifstream inFile;

	inFile.open("VISACARD.dat",ios::in);

	if(inFile.is_open())
	{
		inFile >> ssn;

		while(index < NUMEL && !inFile.eof()) // repeats loop while the index is less than NUMEL and it is not the end of file
		{
			ArrRec[index].ssn=ssn;
			inFile.ignore(1);
			getline(inFile,name,'#');
			ArrRec[index].name=name;
			getline(inFile,address,'#');
			ArrRec[index].address=address;
			inFile >> vn;
			ArrRec[index].visa_num=vn;
			inFile.ignore(2);//'#'\n;

			index++;

			inFile >> ssn; // loops while
		}
	}

	else
	{
		cout << "\n File VISACARD not opened." << endl;
	}

	inFile.close();
	bubbleSort (ArrRec, index); // calls to function to sort names
	cout << endl << " Names Found:" << endl;

	for(int x=0;x<index;x++)
	{
		cout << " " << ArrRec[x].name<< endl;
	}
	cout << endl << " Member's Name to Search: ";
	getline(cin,findName);

	propName(findName);

	location = binarySearch(ArrRec, index, findName);   
	if (location > -1)     
		{
			cout << endl << " The member was found at index location "  << location << endl;
		}

	else     
		{
			cout << endl << " The member was not found in the array\n";
		}
	cout << endl;
	system("pause");

 } // end findMem

// function to sort names in the array
void bubbleSort(Visa_Acct_info AS[], int index)
{
	Visa_Acct_info temp = {0, "", "", 0};
	int i, j = 0;

    for ( i = 0; i < (index - 1); i++)
	{
		for(j = 1; j < index; j++)
		{
			if (AS[j].name < AS[j-1].name)
			{
				temp = AS[j];
				AS[j] = AS[j-1];
				AS[j-1] = temp;
			}
		}
	}

}//end bubbleSort

int binarySearch(Visa_Acct_info list[], int size, string key) 
{   
	int left = 0;
	int right = 0; 
	int midpt = 0;   
	right = size - 1;   
	while (left <= right)   
	{     
		midpt = (int) ((left + right) / 2);     
		if (key == list[midpt].name)     
		{       
			return midpt;     
		}     
		
		else if (key > list[midpt].name)       
			{ 
				left = midpt + 1;
			}
		
		else       
		{
			right = midpt - 1;   
		}
	}// end while   
	
	return -1; 

}// end function




