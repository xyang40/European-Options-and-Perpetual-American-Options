#include "PerpetualAmericanOption.h"
#include<cmath>
#include<sstream>

//overloading assignment operator
PerpetualAmericanOption& PerpetualAmericanOption::operator =(const PerpetualAmericanOption& o){
	//avoid assigning to self
	if (this == &o){
		return *this;
	}
	//calling base class assignment operator
	Option::operator=(o);
	return *this;
}

//implementing perpetual american option functions
double const PerpetualAmericanOption::Price(const double S) const{
	if (this->Type() == Call){
		double y1 = 0.5 - this->B() / pow(this->Sig(), 2) + sqrt(pow(this->B()/pow(this->Sig(),2)-0.5,2)+2*this->R()/pow(this->Sig(),2));
		return (this->K() / (y1 - 1))*pow(((y1-1)/y1)*(S/this->K()),y1);
	}
	else{
		double y2 = 0.5 - this->B() / pow(this->Sig(), 2) - sqrt(pow(this->B() / pow(this->Sig(), 2) - 0.5, 2) + 2 * this->R() / pow(this->Sig(), 2));
		return (this->K() / (1 - y2)) *pow(((y2-1)/y2)*(S/this->K()),y2);
	}
}

std::string const PerpetualAmericanOption::ToString() const{
	std::stringstream ss;//get string stream object
	//loading data to stream
	ss << "strike price: " << this->K()  << ", interest rate: " << this->R() << ", constant volatility: " << this->Sig() << ", cost of carry: " << this->B() << ", optiontype: " << this->Type();
	return ss.str();
}

