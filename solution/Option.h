#include<vector>
#ifndef Option_H
#define Option_H

//an enum to specify the optiontype
enum OptionType { Call = 0, Put = 1 };

class Option{
private:
	//private members, excluding maturity
	double k;
	double sig;
	double r;
	double b;
	OptionType type;
public:
	Option(double k, double sig, double r, double b, OptionType ot) :k(k), sig(sig), r(r), b(b), type(ot){};//constructor with params
	Option(const Option& o) :k(o.k), sig(o.sig), r(o.r), b(o.b), type(o.type){};//copy constructor
	Option& operator =(const Option&);//overloading assignment operator

	virtual double const Price(const double S) const = 0;//pricing function
	std::vector<double> const BatchPrices(const std::vector<double>& ss) const;//pricing according to an array of S
	virtual std::string const ToString() const = 0;//overloading tostring function

	//the following getters and setters are inlined
	double K() const{//return strike price
		return this->k;
	}

	void K(const double k){//set strike price
		this->k = k;
	}

	double R() const{//return interet rate
		return this->r;
	}

	void R(const double d){//set interest rate
		this->r = d;
	}

	double Sig() const{//return vol
		return this->sig;
	}

	void Sig(const double d){//set vol
		this->sig = d;
	}

	double B() const{//return cost of carry
		return this->b;
	}

	void B(const double d){//set cost of carry
		this->b = d;
	}

	OptionType Type() const{//get option type
		return this->type;
	}

	void Type(const OptionType& ot){//set type
		this->type = ot;
	}
};

#endif