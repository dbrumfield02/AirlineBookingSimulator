#ifndef ROUNDTRIP
#define ROUNDTRIP
#include "Booking.h"
#include <ctime>

class RoundTrip : public Booking {
private:
	//return date
	tm returnDate = {};
	string returnTime, returnOrigin, returnDestination, returnSeat;

public:
	void setReturnDate(const tm& returnDate) {
		this->returnDate = returnDate;
	}
	tm getReturnDate() const {
		return returnDate;
	}

	void setReturnTime(const string returnTime) {
		this->returnTime = returnTime;
	}
	string getReturnTime() const {
		return returnTime;
	}

	void setReturnOrigin(const string returnOrigin) {
		this->returnOrigin = returnOrigin;
	}
	string getReturnOrigin() const {
		return returnOrigin;
	}

	void setReturnDestination(const string returnDestination) {
		this->returnDestination = returnDestination;
	}
	string getReturnDestination() const {
		return returnDestination;
	}

	void setReturnSeat(const string returnSeat) {
		this->returnSeat = returnSeat;
	}
	string getReturnSeat() const {
		return returnSeat;
	}

	void printTicket(const Passenger& passenger, const string& origin, const tm& departDate, const string& destination, const tm& returnDate, const string& bookingID, const string& ticketName) const override {
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
		ticketFile << "| Outbound Flight: \n";
		ticketFile << "| Origin: " << origin << endl;
		ticketFile << "| Destination: " << destination << endl;
		ticketFile << "| Departure Date: " << put_time(&departDate, "%d/%m/%Y") << endl;
		ticketFile << "| Departure Time: " << getDepartTime() << endl;
		ticketFile << "| \n";
		ticketFile << "| Return Flight: \n";
		ticketFile << "| Origin: " << getReturnOrigin() << endl;
		ticketFile << "| Destination: " << getReturnDestination() << endl;
		ticketFile << "| Return Date: " << put_time(&returnDate, "%d/%m/%Y") << endl;
		ticketFile << "| Departure Time: " << getReturnTime() << endl;
		ticketFile << "| \n";
		ticketFile << "| Seat: " << getSeatSelection() << " (Outbound), " << getReturnSeat() << " (Return)\n";
		ticketFile << "| \n";
		ticketFile << "| Flight Status: Confirmed\n";
		ticketFile << "=======================================================================\n";
		// Write other booking details as needed

		ticketFile.close();
	}
};

#endif // !ROUNDTRIP