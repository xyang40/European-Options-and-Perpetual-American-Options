#include "Option.h"

//implementing Option class functions
Option& Option::operator =(const Option& o){
	//overloading assignment operator
	if (this == &o){
		//avoid assigning to self
		return *this;
	}

	//assigning each member variable
	this->k = o.k;
	this->r = o.r;
	this->sig = o.sig;
	this->b = o.b;
	this->type = o.type;

	return *this;
}

std::vector<double> const Option::BatchPrices(const std::vector<double>& ss) const{
	//prices using an array of S
	//ss is the vector of Ss
	//declare result vector
	std::vector<double> v_result;
	for (unsigned int i = 0; i < ss.size(); ++i){
		//looping over each possible S
		v_result.push_back(Price(ss[i]));
	}
	return v_result;
}

