// Ch3Data Structures COMP-2750 FA22
// This file creates a program to edit flights and flight manifests using a doubly linked list
//  Credits: big thanks to Jackson Zamorano

#include <iostream>
#include "DoublyLinkedList.cpp"
#include "Flight.h"

using namespace std;

void mainMenu(DLList<Flight>*);
void editReservation(DLList<Flight>*);
void printManifest(DLList<Flight>*, int);
void printManifestReverse(DLList<Flight>*, int);
void printAllManifests(DLList<Flight>*);
void insertPassenger(DLList<Flight>*, int);
void removePassenger(DLList<Flight>*, int);
void driver();

int main()
{
	DLList<Flight>* flights = new DLList<Flight>();
	mainMenu(flights);
	return 0;
}

void mainMenu(DLList<Flight>* flights)
{
	bool valid = true;
	while (valid)
	{
		char mainChoice;
		cout << "   ===== Main Menu =====\n";
		cout << "1) Press to make or change a reservation.\n";
		cout << "2) Press to print all manifests.\n";
		cout << "3) Press for driver.\n";
		cout << "0) Press to exit program.\n";

		cin >> mainChoice;

		switch (mainChoice)
		{
		case '1': editReservation(flights);
			break;
		case '2': printAllManifests(flights);
			break;
		case '3': driver();
			break;
		case '0':
			valid = false;
			break;
		default: cout << "Select a valid option.\n\n";
			break;
		}

		//cin.ignore(100000, '\n');
	}
}
void editReservation(DLList<Flight>* flights)
{
	int flightNum;
	cout << "Enter a flight number:\n";
	cin >> flightNum;

	Flight flight(flightNum);
	flights->insert(flight, [flight](const Flight& f) {return f.getNum() == flight.getNum(); }, 
		[flight](const Flight& f) {return flight.getNum() < f.getNum(); });

	bool repeat = true;
	do
	{
		char choice;
		cout << "   ===== Flight " << flightNum << " ===== \n";
		cout << "1) Insert a passenger onto flght " << flightNum << endl;
		cout << "2) Remove passenger from flight " << flightNum << endl;
		cout << "3) List passengers on flight " << flightNum << endl;
		cout << "4) List passengers on flight " << flightNum << "by reverse order " << endl;
		cout << "0) Exit flight " << flightNum << endl;

		cin >> choice;

		switch (choice)
		{
		case '1': insertPassenger(flights, flightNum);
			break;
		case '2': removePassenger(flights, flightNum);
			break;
		case '3': printManifest(flights, flightNum);
			break;
		case '4': printManifestReverse(flights, flightNum);
			break;
		case '0':
			repeat = false;
			break;
		default: cout << "Select a valid option.\n\n";
			break;
		}
	} while (repeat);


}
void printManifest(DLList<Flight>* flights, int num)
{
	cout << "Flight number: " << num << endl;

	auto manifest = flights->getNode([num](const Flight& f) { return num == f.getNum(); })->data.getManifest();
	DLLNode<string>* temp = manifest->getHead();

	while (temp != nullptr)
	{
		cout << "Name: " << temp->data;
		temp = temp->next;
		cout << endl;
	}
	cout << endl;
}
void printManifestReverse(DLList<Flight>* flights, int num)
{
	cout << "Flight number: " << num << endl;

	auto manifest = flights->getNode([num](const Flight& f) { return num == f.getNum(); })->data.getManifest();
	DLLNode<string>* temp = manifest->getTail();

	while (temp != nullptr)
	{
		cout << "Name: " << temp->data;
		temp = temp->prev;
		cout << endl;
	}
	cout << endl;
}
void printAllManifests(DLList<Flight>* flights)
{
	DLLNode<Flight>* temp = flights->getHead();

	while (temp != nullptr)
	{
		cout << "Flight number: " << temp->data.getNum() << endl;
		
		auto manifest = temp->data.getManifest();
		DLLNode<string>* temp2 = manifest->getHead();
		while (temp2 != nullptr)
		{
			cout << "Name: " << temp2->data;
			temp2 = temp2->next;
			cout << endl;
		}
		cout << endl;
		temp = temp->next;
	}
}
void insertPassenger(DLList<Flight>* flights, int num)
{
	string passenger;
	string trash;
	getline(cin, trash);

	cout << "Enter the name of the passenger (Last First).\n";
	getline(cin, passenger);

	//lamda for comparing strings to be used for insertion
	auto stringComp = [passenger](const string& s)
	{
		string comp1;
		string comp2;
		for (char c : passenger) { comp1 += toupper(c); }
		for (char c : s) { comp2 += toupper(c); }
		return comp1 < comp2;
	};

	auto manifest = flights->getNode([num](const Flight& f) { return num == f.getNum(); })->data.getManifest();
	manifest->insert(passenger, [passenger](const string& s) {return passenger == s; }, stringComp);

	cout << passenger << " was added to flight " << num << endl;
}
void removePassenger(DLList<Flight>* flights, int num)
{
	string passenger;
	string trash;
	getline(cin, trash);
	cout << "Enter the name of the passenger to be removed (Last First).\n";
	getline(cin, passenger);

	auto manifest = flights->getNode([num](const Flight& f) { return num == f.getNum(); })->data.getManifest();
	manifest->remove(passenger, [passenger](const string& s) {return passenger == s; });

	cout << passenger << " was removed from flight " << num << endl;
}
void driver()
{
	DLList<Flight>* flights = new DLList<Flight>();

	//lambda to quickly insert all driver values
	auto driverInsert = [flights](const string& passenger, const int& num) {
		auto stringComp = [passenger](const string& s)
		{
			string comp1;
			string comp2;
			for (char c : passenger) { comp1 += toupper(c); }
			for (char c : s) { comp2 += toupper(c); }
			return comp1 < comp2;
		};

		Flight flight(num);
		flights->insert(flight, [flight](const Flight& f) {return f.getNum() == flight.getNum(); },
			[flight](const Flight& f) {return flight.getNum() < f.getNum(); });

		auto manifest = flights->getNode([num](const Flight& f) { return num == f.getNum(); })->data.getManifest();
		manifest->insert(passenger, [passenger](const string& s) {return passenger == s; }, stringComp);

		cout << passenger << " was added to flight " << num << endl;
	};

	driverInsert("Hamilton Dale", 2430);
	driverInsert("Hamilton Leslie", 2430);
	driverInsert("Hamilton Jonathan", 2430);
	driverInsert("Hamilton Nicholas", 2430);
	driverInsert("Hamilton Annalisa", 2430);

	printManifest(flights, 2430);

	driverInsert("Absorka Thor", 2515);
	driverInsert("Snowwispe Nora", 2515);
	driverInsert("Loki the Mutt", 2515);

	printManifest(flights, 2515);

	auto removeManifest = flights->getNode([](const Flight& f) { return 2515 == f.getNum(); })->data.getManifest();
	removeManifest->remove("Loki the Mutt", [](const string& s) { return "Loki the Mutt" == s; });

	cout << "Loki the Mutt successfully saved from running in an Iditerod\n\n";

	driverInsert("Loki the Mutt", 2750);

	printManifest(flights, 2515);

	printManifest(flights, 2750);





}