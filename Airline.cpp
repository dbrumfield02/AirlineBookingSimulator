/*
* Name: Dylan Brumfield
* Date: 04/24/2024
* Course: CSC 250
*/
#include <ctime>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Passenger.h"
#include "RoundTrip.h"
#include "OneWayTrip.h"
#include "AirlineInfo.h"
#include "InputValidity.h"

//Number of days in advance that user can book a flight 
const int NUM_DAYS = 15;

//instance of InputValidity
InputValidity checkUserInput;

string filePath;

//Methods for menu options' functionaility (state its purpose as well as return and parameters if any) 
void bookTrip(Booking* booking, const vector<string>& placesVec, const vector<string>& departureTimes);
void modifyBooking(Booking* booking, const vector<string>& placesVec, const vector<string>& departureTimes);
void cancelBooking(Booking*& booking);
bool isDepartBeforeReturn(const tm& departDate, const tm& returnDate, const string& selectedDepartureTime, const string& selectedReturnTime);

int main() {
	Booking* booking = nullptr;
	AirlineInfo airlineInfo;
	vector<string> placesVec, departureTimes;
	bool isValid = true;
	int num = 6; 

	// Read departure times from file or initialize them manually
	departureTimes = { "08:00 AM", "10:00 AM", "12:00 PM", "3:00 PM", "6:00 PM" };

	// Read places from file
	bool isValidPath = false;
	cout << "NOTE: To ensure accurate processing of your booking, we require access to your booking data ('Airline.txt')\n";
	do {
		cout << "Enter your file path (examples):\n"
			<< "  Windows:  C:\\\\Users\\\\Name\\\\Documents\\\\Airline.txt\n"
			<< "  Windows:  C:/Users/Name/Documents/Airline.txt\n"
			<< "  Linux/Mac: /home/name/Documents/Airline.txt\n";
		cout << "File path: ";
		getline(cin, filePath);

		ifstream inFile(filePath);
		if (inFile.is_open()) {
			//string fileName = "C:\\Users\\Darli\\OneDrive\\Documents\\Airline.txt";
			booking = new Booking();
			placesVec = booking->fileToVector(filePath);
			inFile.close();
			isValidPath = true;
		}
		else {
			cout << "Unable to open file for places.\n" << endl;
		}
	} while (isValidPath == false);
	cout << endl;

	airlineInfo.systemInterface();

	do {
		airlineInfo.menu();
		cout << "Please select a menu option: ";
		int choice;
		choice = checkInput.checkIntInput(num);

		switch (choice) {
		case 1:
			bookTrip(booking, placesVec, departureTimes);
			break;
		case 2:
			modifyBooking(booking, placesVec, departureTimes);
			break;
		case 3:
			cancelBooking(booking);
			break;
		case 4:
			airlineInfo.TermsAndConditions();
			break;
		case 5:
			airlineInfo.CustomerServiceInfo();
			break;
		case 6:
			cout << "Thank you for using our services. See you again";
			delete booking;
			return 0;
		default:
			cout << "Invalid choice. Please try again" << endl;
			isValid = false;
		}
	} while (isValid == true);
	delete booking;
	return 0;
}

/*
* Purpose: Allow user to book a trip by prompting them to select various things that simulate an actual airline flight booking program
* @param booking A pointer to the Booking object used for the trip.
* @param placesVec A vector containing the available places for travel.
* @param departureTimes A vector containing the available departure times.
*/
void bookTrip(Booking* booking, const vector<string>& placesVec, const vector<string>& departureTimes) {
	Passenger passenger;
	string firstName, lastName, origin, destination, seatID, bookingID, ticketName, strChoice;
	tm departDate, returnDate;
	int tripType, tripRange = 2, numRange = 15;
	vector<string> placesVecSorted = booking->insertionSort(placesVec);
	bool isValidLocation = false;
	bool isValidReturnDate = false;
	cout << "\nBOOKING\n";

	//Create a one-way or round trip booking depending on user inputs
	cout << "What type of trip would you like to book? (Enter 1 for RoundTrip, and 2 for One-Way): ";
	tripType = checkInput.checkIntInput(tripRange);
	if (tripType == 1) {
		booking = new RoundTrip();
	}
	else if (tripType == 2) {
		booking = new OneWayTrip();
	}
	else {
		cout << "Invalid choice";
		exit(1);
	}

	//Get User's name
	cout << "Enter your full name: ";
	cin >> firstName >> lastName;
	passenger.setFirstName(firstName);
	passenger.setLastName(lastName);
	cout << "Passenger's full name: " << passenger.getFullName() << endl;

	cout << "\nEnter Origin formatted as (City, State Abbreviation): ";
	cin.ignore();
	getline(cin, origin);
	while (!booking->binarySearch(placesVecSorted, origin)) {
		cout << "\nLocation not found!\n Please enter a valid Origin (check for spelling): ";
		getline(cin, origin);
	}
	//booking->binarySearch(placesVecSorted, origin);
	booking->setOrigin(origin);

	cout << "\nEnter Destination formatted as City, State Abbreviation: ";
	getline(cin, destination);
	while (!booking->binarySearch(placesVecSorted, destination)) {
		cout << "\nLocation not found!\n Please enter a valid destination (check for spelling): ";
		getline(cin, destination);
	}
	booking->setDestination(destination);

	cout << "\nSelect a date for departure: \n";
	departDate = booking->selectDate(NUM_DAYS);
	booking->setDepartDate(departDate);
	cout << "You selected to depart on: " << departDate.tm_mday << "/" << (departDate.tm_mon + 1) << "/" << (departDate.tm_year + 1900) << endl;

	string selectedDepartureTime = booking->selectDepartureTime(departureTimes);
	cout << "\nSelected Departure Time: \n" << selectedDepartureTime << endl;
	booking->setDepartTime(selectedDepartureTime);

	//seat selection 
	seatID = booking->selectSeat();
	booking->setSeatSelection(seatID);

	//This if statement block is only entered, if user chose round trip instead of one-way
	if (tripType == 1) {
		do {
			cout << "\nSelect a date for return: \n";
			returnDate = booking->selectDate(NUM_DAYS);
			static_cast<RoundTrip*>(booking)->setReturnDate(returnDate);
			cout << "You selected to return on: " << returnDate.tm_mday << "/" << (returnDate.tm_mon + 1) << "/" << (returnDate.tm_year + 1900) << std::endl;
			string selectedReturnTime = booking->selectDepartureTime(departureTimes);
			cout << "\nSelect a time for return: " << selectedReturnTime;
			static_cast<RoundTrip*>(booking)->setReturnTime(selectedReturnTime);
			isValidReturnDate = isDepartBeforeReturn(departDate, returnDate, selectedDepartureTime, selectedReturnTime);
			if (!isValidReturnDate) {
				cout << "\n\n*ERROR: Please select a return date and time that is after the departure date and time.*\n" << endl;
			}
		} while (!isValidReturnDate);
		//seat for return
		string seatID2 = booking->selectSeat();
		static_cast<RoundTrip*>(booking)->setReturnSeat(seatID2);
		static_cast<RoundTrip*>(booking)->setReturnOrigin(destination);
		static_cast<RoundTrip*>(booking)->setReturnDestination(origin);
	}
	bookingID = booking->generateAlphaNumericID(3, 5);
	cout << "\nBooking ID: " << bookingID << endl;
	booking->confirmBooking();

	cout << "Would you like to print your ticket (enter 'Y' for yes, and 'N' for no)? ";
	cin >> strChoice;

	/*FIX AS SOON AS POSSIBLE*/
	if (strChoice == "Y") {
		//ticketName = "C:\\Users\\Darli\\OneDrive\\Documents\\BoardingTicket.txt";
		//booking->printTicket(passenger, booking->getOrigin(), departDate, booking->getDestination(), returnDate, bookingID, ticketName);
	
		cout << "Enter your file path to save the ticket (e.g., C:\\Users\\YourUsername\\Documents\\): ";
		string userFilePath;
		cin >> userFilePath;
		string ticketFileName = userFilePath + "BoardingTicket.txt";
		booking->printTicket(passenger, booking->getOrigin(), departDate, booking->getDestination(), returnDate, bookingID, ticketFileName);

		cout << "Ticket Printed! For any issues experienced in this process, please contact customer service\n ";
	}
}

/*
* Purpose: allow user to modify aspects pf booking \such as departure date, return date, origin, or destination
* @param booking: Pointer to the booking object to be modified.
* @param placesVec: Vector containing locations for binary search.
* @param departureTimes: Vector containing departure times for menu display.
*/
void modifyBooking(Booking* booking, const vector<string>& placesVec, const vector<string>& departureTimes) {
	int choice, menuRange = 5;
	tm newDepartDate,newReturnDate;
	string newOrigin, newDestination;

	cout << "What aspect of your booking would you like to modify?" << endl;
	cout << "1. Departure date" << endl;
	cout << "2. Return date" << endl;
	cout << "3. Origin" << endl;
	cout << "4. Destination" << endl;
	cout << "5. Cancel" << endl;
	cout << "Enter your choice: ";
	choice = checkInput.checkIntInput(menuRange);

	switch (choice) {
	case 1:
		// Modify departure date
		newDepartDate = booking->selectDate(NUM_DAYS);
		booking->setDepartDate(newDepartDate);
		cout << "Departure date modified." << endl;
		break;
	case 2:
		// Modify return date (if applicable)
		if (dynamic_cast<RoundTrip*>(booking) != nullptr) {
			newReturnDate = booking->selectDate(NUM_DAYS);
			static_cast<RoundTrip*>(booking)->setReturnDate(newReturnDate);
			cout << "Return date modified." << endl;
		}
		else {
			cout << "Return date is not applicable for this booking type." << endl;
		}
		break;
	case 3:
		// Modify origin
		cout << "Enter new origin (City, State): ";
		cin.ignore();
		getline(cin, newOrigin);
		booking->binarySearch(placesVec, newOrigin);
		booking->setOrigin(newOrigin);
		cout << "Origin modified.\n" << endl;
		break;
	case 4:
		// Modify destination
		cout << "Enter new destination (City, State): ";
		cin.ignore();
		//newDestination = checkUserInput.checkUserStr();
		getline(cin, newDestination);
		booking->binarySearch(placesVec, newDestination);
		booking->setDestination(newDestination);
		cout << "Destination modified.\n" << endl;
		break;
	case 5:
		// Cancel modification
		cout << "Modification cancelled.\n" << endl;
		break;
	default:
		cout << "Invalid choice. Please try again." << endl;
	}
}

/*
* Purpose: Delete the user's booking
* @param booking: A dereferenced pointer for the user's booking, which can be deleted
*/
void cancelBooking(Booking*& booking) {
	string strChoice;
	cout << "Are you sure you want to cancel this booking?\n";
	cout << "Before proceeding with your cancellation, please review our terms and conditions.\nType 'Y' to confirm that you've read our policies and still wish to cancel, or 'N' to exit without cancelling.\n";
	do {
		false;
		cin >> strChoice;
		if (strChoice == "Y" || strChoice == "y") {
			if (booking != nullptr) {
				cout << "Cancellation complete.\n Thank you for choosing Airline Name, we wish to see you again soon!\n";
				delete booking;
				true;
			}
		}
		else if (strChoice == "N" || strChoice == "n") {
			cout << "Cancellation cancelled!\n";
		}
		else {
			cout << "Please respond with 'yes' or 'no'.\n";
		}
	} while (false);
}

/*
* Purpose: ensure departDate is before returnDate
* @param departDate: The departure date.
* @param returnDate: The return date.
* @param selectedDepartureTime: The selected departure time.
* @param selectedReturnTime: The selected return time.
* @return true if the departure date is before the return date, false otherwise.
*/
bool isDepartBeforeReturn(const tm& departDate, const tm& returnDate, const string& selectedDepartureTime, const string& selectedReturnTime) {
	if (returnDate.tm_year < departDate.tm_year) {
		return false;
	}
	else if (returnDate.tm_year == departDate.tm_year) {
		if (returnDate.tm_mon < departDate.tm_mon) {
			return false;
		}
		else if (returnDate.tm_mon == departDate.tm_mon) {
			if (returnDate.tm_mday < departDate.tm_mday) {
				return false;
			}
		}
	}
	// If the dates are not equal, or return date is after depart date,
	// check the times if they are on the same day
	if (returnDate.tm_year == departDate.tm_year &&
		returnDate.tm_mon == departDate.tm_mon &&
		returnDate.tm_mday == departDate.tm_mday) {
		// Dates are the same, compare times
		if (selectedReturnTime <= selectedDepartureTime) {
			cout << "Return time must be later than departure time." << endl;
			return false;
		}
	}
	return true;
}
