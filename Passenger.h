#ifndef PASSENGER
#define PASSENGER
using namespace std;

class Passenger {
private:
	string firstName;
	string lastName;
	string fullName;

public:
	Passenger() {}
	//setters (mutators)
	void setFirstName(string firstName) {
		this->firstName = firstName;
	}
	void setLastName(string lastName) {
		this->lastName = lastName;
	}
	//getter (accessor)
	string getFullName() const {
		return firstName + " " + lastName;
	}
	//toString function for displaying fullName as complete string
	void toString() const {
		cout << firstName << " " << lastName;
	}

};

#endif //	!PASSENGER