#include <iostream>
#include <string>

#ifndef INPUTVALIDITY
#define INPUTVALIDITY

using namespace std;

/*
* Purpose: Class for validating the input in Booking.h and Airline.cpp
* @param numRange: the range of integers that are acceptible
* @return integer: the integer of the user
*/
class InputValidity {
public:
	int checkIntInput(int& numRange) {
		int integer;
		bool isInputValid = false;

		do {
			try {
				if (!(cin >> integer)) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					throw invalid_argument("Invalid input: ");
				}
				if ((integer > numRange) || (integer <= 0)) {
					throw out_of_range("Invalid Input: ");
				}
				else if ((integer <= numRange) && (integer != 0)) {
					isInputValid = true;
				}
			}
			catch (invalid_argument& ex) {
				cout << ex.what();
				cout << "Please enter a numeric value appropiate to the choice selection\n";
			}
			catch (out_of_range ex) {
				cout << ex.what();
				cout << "Please enter a numeric value appropiate to the choice selection\n";
			}
		} while (!isInputValid);

		return integer;
	}
	string checkUserStr() {
		string userStr;
		bool isValid = false;
		do {
			try {
				getline(cin, userStr);

				if (!userStr.empty()) { //check if input is not empty
					isValid = true; // Set isValid to true if input is not empty
				}
				else {
					cout << "Please enter a non-empty string: ";
				}
			}
			catch (exception& ex) {
				cout << "Error: " << ex.what() << endl;
			}
		} while (!isValid);
		return userStr;
	}

	
};

#endif // !INPUTVALIDITY


