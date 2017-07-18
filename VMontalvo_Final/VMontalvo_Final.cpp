//====================================================================================================================================
// Valerie Montalvo - Final
//====================================================================================================================================

#include <iostream> 
#include <string> 
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;
//using std::cout;
//using std::string;
//using std::getline;
//using std::cin;
//using std::endl;
//using std::fixed;
//using std::left;
//using std::right;
//using std::rand;
//using std::setfill;
//using std::ifstream;
//using std::ofstream;
//using std::ios;
//using std::setw;
//using std::transform;

// structured Visa Array
struct VisaAccts
{
	string name;
	string address;
	string city;
	string state;
	int zip;
	int visa_num;
};

const int NUMEL=50; // max size of name array

void getName (string &); // function to input customer name
void getAddress (string &, string &, string &, int &); // function to input customer address
void display (string, string, string, string, int, int); // function to display member report
void displayTitle(); // function to display titles
void newVisa(); // function to enter customer information to apply for a new Visa
void prntRpt(); // function to print reports
int VisaNum(); // function to generate visa number
void propName (string &); // function to transform name to proper case
void findMem (); // function to find member name
int binarySearch(VisaAccts [], int, string); // function to search for member
void bubbleSort (VisaAccts [], int); // function to sort card member names into an array
void acceptDisplay (string, string, string, string, int, int); // function to display member report

// start main program
int main()
{
	// initizialize variables
	int opselect = 0; // user menu selection

	
	do // program repeats until user exits
	{
		system("cls"); // clears the screen
		
		// user menu
		cout << "\t\t\t Visa Card System \n\n";
		cout <<" \t\t 1. Apply Visa Card \n";
		cout << "\t\t 2. Find a Member \n";
		cout << "\t\t 3. Print Report \n";
		cout << "\t\t 4. Exit \n\n";
		cout << "\t Make a selection: ";
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

// name entry void function, pass by reference
void getName (string &name)
{
	cout<<"\t Name (20 Characters): ";
	getline(cin, name);

	while (name.size() == 0 || name.size() > 20) // repeats user entry while invalid
	{
		cout<<"\t Name (20 Characters): ";
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
void getAddress (string &address, string &city, string &state, int &zip)
{
	cout<<"\t Street Address (25 Characters): ";
	getline(cin, address);

	while (address.size() == 0 || address.size() > 25) // repeats user entry while invalid
	{
		cout<<"\t Street Address (25 Characters): ";
		getline(cin, address);
	}

	propName(address);

	do
	{
		cout << "\t City: ";
		getline(cin, city);

	} while (city.size()==0 || city.size() > 16);

	propName(city);

	do
	{
		cout << "\t State (RI, MA or CT): ";
		getline(cin, state);

		transform(state.begin(), state.end(), state.begin(), toupper);

	} while (state != "RI" && state != "MA" && state != "CT");

	do
	{
		cout << "\t Zip Code: ";
		cin >> zip;

	} while (zip < 01000 || zip > 99900);

	

} // end address entry

// display titles void function
void displayTitle()
{
	system("CLS");
	cout << "\t\t\t Visa Card System" << endl;
	cout << "\t\t\t Membership Report" << endl << endl;
	cout << left << setw(20) << setfill(' ') << "Name" << " " 
				 << setw(25) << "Address" << " " 
				 << setw(16) << "City" << " "
				 << setw(2) << "ST" << " "
				 << setw(5) << "Zip" << " "
				 << setw(6) << "Visa #" << endl << endl;

} // end display titles

// display member summary void function
void display (string name, string address, string city, string state, int zip, int vn)
{
	cout << left << setw(20) << setfill(' ') << name << " " 
				 << setw(25) << address << " " 
				 << setw(16) << city << " "
				 << setw(2) << state << " "
		<< right << setw(5) << setfill('0') << zip << " "
		<< left << setw(6) << setfill(' ') << vn << endl;

} // end display summary

void acceptDisplay (string name, string address, string city, string state, int zip, int visa_num)
{
	cout << left << setw(15) << setfill(' ') << "\t Name:" << " " << setw(25) << name << endl 
				 << setw(15) << "\t Address:"  << " " << setw(25) << address << endl 
				 << setw(15) << "\t City:" << " " << setw(25) << city << endl 
				 << setw(15) << "\t State:" << " " << setw(25) << state << endl
				 << setw(15) << "\t Zip:" << " " << right << setw(5) << setfill('0') << zip << endl << endl;
}

// apply for a visa void function
void newVisa()
{
	// inititialize variables
	string name = ""; // member name
	string address = ""; // member street address
	string city = ""; // member city
	string state = ""; // member state
	char accept = ' '; // accept member info
	int zip = 0; // member zip code
	int visa_num = 0; // visa number

	
	ofstream outFile; // file complex variable

	outFile.open("VisaInfo.txt",ios::app); // open VISACARD file and append data to the end
	if (outFile.is_open())  // checks if file is open
	 {
		do
		{
			system("CLS");
			cout << "\t\t\t Visa Card System \n";
			cout << "\t\t     New Account Information \n\n";
			cin.ignore(1);
			getName (name); // calls to member name entry function
			getAddress (address, city, state, zip); // calls to member address entry function
			visa_num=VisaNum(); // calls to visa number generator function
			cout << endl;
			system("CLS");
			cout << "\t\t\t Visa Card System \n";
			cout << "\t\t     New Account Information \n\n";
			cout << " Information Entered: \n\n";
			acceptDisplay (name, address, city, state, zip, visa_num); // calls to display member summary function

			cout << " Verify Information (Y/N): ";
			cin >> accept;

			cout << endl;

		} while (accept != 'Y' && accept !='y');

		outFile << name << '#' << address << '#' << city << '#' << state << '#' << zip << '#' << visa_num << '#' << endl; // writes user input to VISACARD
		cout << " Member data saved successfully." << endl << endl;

		system("pause");

	 }

	 else // if file is not open, display error
	 {
		 system("CLS");
		 cout << "\t\t\t Visa Card System \n";
		 cout << "\t\t     New Account Information \n\n";
		 cout << "\n\t File not opened." << endl;
	 }
	 
	 outFile.close(); // close opened file

} // end new visa

// function to read from a file and print a report
void prntRpt()
{
	// inititialize variables
	string name = ""; // member name
	string address = ""; // member address
	string city = ""; // member city
	string state = ""; // member state
	int zip = 0; // member zip code
	int vn = 0; // visa number


	ifstream inFile; // file i/o complex variable
	inFile.open("VisaInfo.txt", ios::in); // opens VISACARD and reads from it

	if(inFile.is_open())
	{
		displayTitle(); // calls to display titles function
		getline(inFile, name, '#'); // reads name, ignores '#'

		while(!inFile.eof()) // while not the end of the file
		{
			getline(inFile, address, '#'); // reads address, ignores '#'
			getline(inFile, city, '#'); // reads city, ignores '#'
			getline(inFile, state, '#'); // reads state, ignores '#'
			inFile >> zip;
			inFile.ignore(1); // ignores '#'
			inFile >> vn;
			inFile.ignore(2); // ignores '#' \n
			display (name, address, city, state, zip, vn); // calls to display variables function
			getline(inFile, name, '#'); // reads name, ignores '#'
		}

		cout << endl;	
	}

	else
	{
		cout << "\n File not opened." << endl;
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

	VisaAccts arrInfo[NUMEL]={"", "", "", "", 0, 0}; // structured visa array
	string name=""; // card member name
	string address=""; // card member address
	string city = ""; // member city
	string state = ""; // member state
	int zip = 0; // member zip code
	int vn = 0; // visa number
	int index = 0; //array index
	string findName = ""; // search member name
	int location = 0; // index location of search
	string foundName = ""; // found member name
	string foundAddress = ""; // found member address
	string foundCity = ""; // found member city
	string foundState = ""; // found member state
	int foundZip = 0; // found member zip
	int foundVisa = 0; // found member visa number

	system("CLS");
	cin.ignore(1);
	cout << "\t\t\t Visa Card System \n";
	cout << "\t\t     Find an Existing Member \n\n";
	
	ifstream inFile;
	inFile.open("VisaInfo.txt",ios::in);

	if(inFile.is_open())
	{
		getline(inFile,name,'#');
	

		while(index < NUMEL || !inFile.eof()) // repeats loop while the index is less than NUMEL and it is not the end of file
		{
			
			arrInfo[index].name = name; // enters names into an array
			getline(inFile,address,'#'); // reads address from file
			arrInfo[index].address=address; // inputs address into array
			getline(inFile,city,'#'); // reads city from file
			arrInfo[index].city=city; // inputs city into array
			getline(inFile,state,'#'); // reads state from file
			arrInfo[index].state=state; // inputs state into array
			inFile >> zip; // reads zip code from file
			arrInfo[index].zip=zip; // inputs zip code into array
			inFile.ignore(1);
			inFile >> vn; // reads visa number from file
			arrInfo[index].visa_num=vn; // inputs visa number into array
			inFile.ignore(2);//'#'\n;

			index++;
			getline(inFile,name,'#'); // loops while
		}
	}

	else
	{
		cout << "\n File not opened." << endl;
	}

	inFile.close(); // closes file
	bubbleSort (arrInfo, index); // calls to function to sort names
	cout << endl << "Enter member name to locate:" << endl << endl;
	cout << "Name (20 Characters): ";
	getline(cin,findName);

	propName(findName); // calls to function to transform into proper case
	location = binarySearch(arrInfo, index, findName); // calls to function to find location of search input in array

	if (location > -1) // if found    
		{
			foundName = arrInfo[location].name; // finds name at location in array
			foundAddress = arrInfo[location].address; // finds address at location in array
			foundCity = arrInfo[location].city; // finds city at location in array
			foundState = arrInfo[location].state; // finds state at location in array
			foundZip = arrInfo[location].zip; // finds zip at location in array
			foundVisa = arrInfo[location].visa_num; // finds visa number at location in array

			system("CLS");
			cout << "\t\t\t Visa Card System \n";
			cout << "\t\t     Find an Existing Member \n\n";
			cout << " Report on Existing Member:" << endl;

			acceptDisplay(foundName, foundAddress, foundCity, foundState, foundZip, foundVisa);

		}

	else     
		{
			cout << endl << " The member was not found in the array\n";
		}
	
	cout << endl;
	system("pause");

 } // end findMem

// function to sort array by name
void bubbleSort(VisaAccts AS[], int index)
{
	VisaAccts temp = {"","","","",0,0};
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

// function to search for location in array
int binarySearch(VisaAccts list[], int size, string key) 
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

}// end binarySearch






