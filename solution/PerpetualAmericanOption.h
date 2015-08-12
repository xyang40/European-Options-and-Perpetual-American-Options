#include<vector>
#include "Option.h"
#ifndef PAO_H
#define PAO_H

//declare the perpetual american option class
class PerpetualAmericanOption:public Option{
public:
	PerpetualAmericanOption(double k, double sig, double r, double b, OptionType ot): Option(k,sig,r,b,ot){};//constructor with params
	PerpetualAmericanOption(const PerpetualAmericanOption& o): Option(o){};//copy constructor
	PerpetualAmericanOption& operator =(const PerpetualAmericanOption&);//overloading assignment operator
	~PerpetualAmericanOption(){};//default destructor

	//overriding two pure virtual functions in Option 
	double const Price(const double S) const;//pricing function
	std::string const ToString() const;//overloading tostring function
};

#endif