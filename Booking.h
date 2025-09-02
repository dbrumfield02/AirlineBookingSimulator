#ifndef AIRLINE
#define AIRLINE
#pragma warning(disable : 4996)
#include <ctime>
#include <string>
#include <iostream> 
#include <fstream> 
#include <vector>  
#include "InputValidity.h"
#include "Passenger.h"
using namespace std;

InputValidity checkInput;
int days = 15;

/* 
* Purpose: This class manages aspects of booking a flight
*/
class Booking {
private:
	string bookingID;
	tm departDate;
	string departTime;
	string origin, destination;
	string seat;
	//string seatSelection;
	Passenger passenger;

	//Vector for seat options. The seats are organized with rows as the letters (from A to H) and columns as the numbers (from 1 to 3).  
	vector<string> seatSelection = {
		"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
		"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
		"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3"
	};

	bool isValidSeat(const string& seat) const {
		for (const auto& s : seatSelection) {
			if (s == seat) {
				return true;
			}
		}
		return false;
	}

	void setBookingID(string bookingID) {
		this->bookingID = bookingID;
	}

public:
	//constructor
	Booking() = default;
	Booking(const string& origin, const string& destination, const tm& departDate)
		: origin(origin), destination(destination), departDate(departDate) {}
	
	//setters and getters
	string getBookingID() const {
		return bookingID;
	}
	void setPassenger(Passenger passenger) {
		this->passenger = passenger;
	}
	Passenger getPassenger() {
		return passenger;
	}
	void setOrigin(string origin) {
		this->origin = origin;
	}
	string getOrigin() const {
		return origin;
	}
	void setDestination(string destination) {
		this->destination = destination;
	}
	string getDestination() const {
		return destination;
	}
	void setDepartDate(const tm& date) {
		departDate = date;
	}
	tm getDepartDate() const {
		return departDate;
	}
	void setDepartTime(const string departTime) {
		this->departTime = departTime;
	}
	string getDepartTime() const{
		return departTime;
	}
	void setSeatSelection(const string seat) {
		this->seat = seat;
	}
	string getSeatSelection() const {
		return seat;
	}

	/*
	* Purpose: generate a unique Record Locator for bookingID
	* @param numLetters number of letters for loop as a condition 
	* @param numIntegers: however many numbers to include in bookingID
	* @return id: A string that will be for the bookingID
	*/
	string generateAlphaNumericID(int numLetters, int numIntegers) {
		srand(static_cast<unsigned>(time(0)));
		int randNum;
		string id = "";
		const int MAX = 26;
		char alphabet[MAX] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
							   'H', 'I', 'J', 'K', 'L', 'M', 'N',
							   'O', 'P', 'Q', 'R', 'S', 'T', 'U',
							   'V', 'W', 'X', 'Y', 'Z' };
		for (int i = 0; i < numLetters; i++) {
			id += static_cast<char>(alphabet[rand() % MAX]);
		}

		for (int i = 0; i < numIntegers; i++) {
			randNum = rand() % numIntegers;
			id += to_string(static_cast<int>(randNum));
		}
		return id;
	}

	/*
	* Purpose: Store the locations from file to a vector 
	* @param filename: A string for the name of the file
	* @return vec: A vector that will hold the content of the file
	*/
	vector<string> fileToVector(const string& filename) {
		vector <string> vect;
		ifstream file(filename);

		if (file.is_open()) {
			string location;
			while (getline(file, location)) {
				vect.push_back(location);
			}
			file.close();
		}
		else {
			cout << "Unable to open the following file: " << filename << endl;
		}
		return vect;
	}

	/*
	* Purpose: Sort vector of string variables for location
	* @param vec: A vector that will be sorted 
	* @return vec: A vector that should contain a sorted version of the original vector
	*/
	vector<string> insertionSort(vector <string> vec) {
		string temp;
		int size = vec.size();
		string key;
		int i;
		int j;

		for (i = 1; i < size; i++) {
			key = vec[i];
			j = i - 1;

			while ((j >= 0) && (vec[j] > key)) {
				vec[static_cast<vector<string, allocator<string>>::size_type>(j) + 1] = vec[j];
				j = j - 1;
			}
			vec[static_cast<vector<string, allocator<string>>::size_type>(j) + 1] = key;
		}
		return vec;
	}

	/*
	* Purpose: Perform binary search on vector of string variables for location
	* @param vec: A reference vector of string data type used for conducting a binary search
	* @param key: A string that will be searched throughout the vector for in the binary seach
	* @return A true or false value that will let user know if the key was found or not
	*/
	bool binarySearch(const vector<string>& vec, string key) {
		int low = 0;
		int high = vec.size() - 1;

		while (low <= high) {
			int mid = low + (high - low) / 2;

			cout << "Comparing: " << vec[mid] << " with " << key << endl;

			if (vec[mid] == key) {
				cout << "Location found\n";
				return true;
			}
			else if (vec[mid] < key) {
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
		}

		return false;
	}

	//Prompt user to select a date
	/*
	* Purpose: Generate dates after the current day in a vector and allow the user to select one from the options
	* @param numDays: An int variable that represents the number of days after the current date that the user can select up to 
	  (should be relatively small for resource purposes)
	* @return The element within a tm vector of dates which the user chooses from
	*/
	static tm selectDate(int numDays) {
		// Get current time
		time_t currentTime = time(nullptr);

		// Convert current time to tm structure
		tm* currentDate = localtime(&currentTime);

		// Create a vector to store dates
		vector<tm> dates;

		// Populate dates starting from tomorrow
		for (int i = 0; i < numDays; ++i) {
			// Reset the day of the month to the current day
			tm nextDate = *currentDate;
			nextDate.tm_mday += i + 1;
			mktime(&nextDate);

			// Store date
			dates.push_back(nextDate);

			// Print date
			cout << i + 1 << ". " << nextDate.tm_mday << "/" << (nextDate.tm_mon + 1) << "/" << (nextDate.tm_year + 1900) << endl;
		}

		// Prompt user to choose date, and validate their input
		cout << "Choose a date (1-" << numDays << "): ";
		int choice = checkInput.checkIntInput(days);
		choice--; // Adjust for 0-based indexing
	
		// Return selected date
		return dates[choice];
	}
	
	/*
	* Purpose: method for printing ticket to a file
	* @param passenger: The passenger that the ticket is being printed for. Used for printing passenger name
	* @param origin: origin of the flight.
	* @param departDate: depart date of the flight.
	* @param destination: The destination of the flight.
	* @param bookingID: The booking ID for the ticket.
	* @param ticketName: The name of the file to which the ticket will be printed.
	*/
	virtual void printTicket(const Passenger& passenger, const string& origin, const tm& departDate, const string& destination, const tm& returnDate, const string& bookingID, const string& ticketName) const {
		// Open a new text file

		ofstream ticketFile(ticketName);

		if (!ticketFile.is_open()) {
			cout << "Error: Unable to open the file." << endl;
			return;
		}

		// Write booking information to the file
		ticketFile << "=======================================================================" << endl;
		ticketFile << "|                            AIRLINE TICKET                           |" << endl;
		ticketFile << "=======================================================================" << endl;
		ticketFile << "| Passenger Name: " << passenger.getFullName() << endl;
		ticketFile << "| Ticket Number: " << bookingID << endl;
		ticketFile << "| \n";
		ticketFile << "| Outbound Flight: " << endl;
		ticketFile << "| Origin: " << origin << endl;
		ticketFile << "| Destination: " << destination << endl;
		ticketFile << "| Departure Date: " << put_time(&departDate, "%d/%m/%Y") << endl;
		ticketFile << "| Departure Time: " << departTime << endl;
		ticketFile << "| \n";
		ticketFile << "| Seat: " << seat <<" (Outbound)" << endl;
		ticketFile << "| \n";
		ticketFile << "| Flight Status: Confirmed" << endl;
		ticketFile << "=======================================================================" << endl;

		ticketFile.close();
	}


	/*
	* Purpose: Let user choose departure time
	* @param departureTimes
	* @return departureTimes[choice]
	*/
	string selectDepartureTime(const vector<string>& departureTimes) {
		// Display available departure times
		cout << "Available Departure Times:" << endl;
		for (size_t i = 0; i < departureTimes.size(); ++i) {
			cout << i + 1 << ". " << departureTimes[i] << endl;
		}
		int timeRange = 5;
		// Randomly select a departure time (check if input is valid)
		size_t choice;
		cout << "Choose a departure time (1-" << departureTimes.size() << "): ";
		choice = checkInput.checkIntInput(timeRange);
		choice--;

		return departureTimes[choice];
	}

	/*
	* Purpose: Allow the user to select a seat from options
	* @return A string variable that represents the selected seat
	*/
	string selectSeat() {
		string seat;
		cout << "Available seats:" << endl;
		for (const auto& s : seatSelection) {
			cout << s << " ";
		}
		cout << endl;
		cout << "Enter seat selection (ex. A1): ";

		cin >> seat;
		if (!isValidSeat(seat)) {
			cout << "Invalid seat selection. Please try again." << endl;
			return selectSeat(); // Recursive call until valid seat is selected
		}
		//return seat
		return seat;
	}

	/*
	* Purpose: search for the seat that the user wants by using recurrsion. 
	* @param A constant (unchangable) refrenced string 
	* @param size of the vector
	* @return A bool value (true or false) depending on whether seat is found
	*/
	bool searchSeat(const string& targetSeat, size_t index = 0) {
		if (index >= seatSelection.size()) {
			return false; // base case for seat not found
		}
		if (seatSelection[index] == targetSeat) {
			return true; // base case for seat found
		}
		// Do recursive call to search next seat
		return searchSeat(targetSeat, index + 1); 
	}

	/*
	* Purpose: Display "Booking Confirmed!" to the screen to let user know that the proccess was completed
	*/
	void confirmBooking() const {
		cout << "Booking Confirmed!" << endl;
	}
};
#endif // !AIRLINE