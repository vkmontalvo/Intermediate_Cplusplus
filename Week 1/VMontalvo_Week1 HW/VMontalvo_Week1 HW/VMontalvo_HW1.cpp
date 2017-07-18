//====================================================================================================================================
// Valerie Montalvo Week 1 Homework
//====================================================================================================================================

#include <iostream> 
#include <string> 
#include <iomanip> 
#include <algorithm>

using namespace std;

// Function to enter SSN
long getSocial();

// Function to enter address
string getAddress();

// Function to enter name
string getName();

// Function to display record
void display(long, string, string);

// Initialize main program
int main()
{
	// Variables
	string name = "";
	string address = "";
	long ssn = 0;
	char again = 'Y';

	// Program repeats until user exits
	while (again == 'Y' || again == 'y')
	{
		system("CLS");
		cout << "\t\t\t Demographic Entry" << endl;
		cout << endl << "\t Please enter:" << endl;
		name = getName();
		address = getAddress();
		ssn = getSocial();

		display(ssn, name, address);

		
		cout << endl << "\t Enter another person? (Y/N): ";
		cin >> again;
		cin.ignore(1);
	}

	system("pause");
	return 0;

}

// Function to enter name
string getName()
{
	string name1 = "";

	do
	{
		cout << endl << "\t\t Name: ";
		getline(cin, name1);

		if (name1.size() == 0 || name1.size() > 20)
		{
			cout << endl << "\t\t Name is required, and cannot be longer than 20 characters.";
		}
	} while (name1.size() == 0 || name1.size() > 20);

	return name1;
}

// Function to enter the address
string getAddress()
{
	string address1 = "";

	do
	{
		cout <<"\t\t Address: ";
		getline(cin, address1);

		if (address1.size() == 0 || address1.size() > 25)
		{
			cout << endl << "\t\t Address is required, and cannot be longer than 25 characters." << endl;
		}
	} while (address1.size() == 0 || address1.size() > 25);

	return address1;
}

//Function to enter ssn
long getSocial()
{
	long ssn1 = 0;

	do
	{
		cout <<"\t\t SSN: ";
		cin >> ssn1;

		if (ssn1 < 100000000 || ssn1 > 999999999)
		{
			cout << endl << "\t\t SSN must be between 100000000 and 999999999." << endl;
		}
	} while (ssn1 < 100000000 || ssn1 > 999999999);

	return ssn1;
}

//Function to display record
void display(long ssn, string name, string address)
{

	cout << endl << endl;
	cout << "\t NAME " << name << "\t ADDRESS" << address << "\t SSN " << ssn << endl;

}