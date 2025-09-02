#ifndef AIRLINEINFO
#define AIRLINEINFO 

using namespace std;

/* For printing various messages to screen
*/
class AirlineInfo {
public:
	/* 
	* Purpose: display inital greeting to screen
	*/
	void systemInterface() {
		cout << "===========>>>>>>> Airline Name <<<<<<<===========\n\n";
		cout << "Greetings! Kindly choose an option from the menu below to proceed with your flight reservation.\n";
	}

	/*
	* Purpose: display nice message to screen before user exits the system
	*/
	void printGoodbyeMessage() {
		cout << "Thank you for choosing our services. Goodbye!\n";
	}

	/*
	* Purpose: display menu options to screen
	*/
	void menu() {
		cout << "~~~~~~~ Menu ~~~~~~~\n";
		cout << "1. Book a Flight\n";	//allow user to book flight and print ticket
		cout << "2. Edit Booking\n";	//allow user to edit book flight details 
		cout << "3. Cancel Booking\n";	//output a string telling user to contact customer service for further assistence
		cout << "4. View Terms & Conditions\n";
		cout << "5. Contact Customer Service\n";
		cout << "6. Exit\n";			//leave terminal
	}

	/*
	* Purpose: display customer service informaion to user 
	*/
	void CustomerServiceInfo() {
		cout << "For assistance, please contact our customer service team:\n";
		cout << "Phone: 1-800--555--4567\n";
		cout << "Email: customerservice@airlinebooking.com\n";
		cout << "Live Chat: Visit our website and click on the live chat option\n";
	}

	/*
	* Purpose: display terms and conditions to screen
	*/
	void TermsAndConditions() {
		cout << "* Cancellation Policy: \n[NOTE: Each cancellation request will be investigated by our customer service team for validity]" << endl;
		cout << "  1. Full refunds or credits are available for cancellations within 24 hours of purchase, if the flight departure is at least 7 days away." << endl;
		cout << "  2. Refunds or credits may be provided for cancellations due to emergencies, such as medical emergencies, family emergencies, natural disasters, or government advisories." << endl;
		cout << "  3. Customers can appeal a denied cancellation by providing additional documentation." << endl;
		cout << "  4. Non-refundable fares may qualify for credits if canceled within the grace period." << endl;
		cout << "* Refund Eligibility:" << endl;
		cout << "  1. Refunds in the form of credits are available for cancellations within 24 hours of purchase." << endl;
		cout << "  2. Refunds are primarily issued as credits for future bookings." << endl;
		cout << "  3. Customers may appeal for refunds in special circumstances." << endl;
		cout << "* Cancellation Fees:" << endl;
		cout << "  1. No cancellation fees within 24 hours of purchase." << endl;
		cout << "  2. Cancellation fees may apply outside the grace period." << endl;
		cout << "  3. Fees may be waived for cancellations due to emergencies." << endl;
	}

};
#endif // !AIRLINEINFO