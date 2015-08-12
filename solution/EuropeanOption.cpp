#include "EuropeanOption.h"
#include<cmath>
#include <boost/math/distributions/normal.hpp> // for normal_distribution
using boost::math::normal; // typedef provides default type is double.
#include<vector>
#include<string>
#include<sstream>

//implementing EuropeanOption class pricing functions
EuropeanOption& EuropeanOption::operator =(const EuropeanOption& o){
	//overloading assignment operator
	if (this == &o){
		//avoid assigning to self
		return *this;
	}

	Option::operator=(o);
	//assigning each member variable
	this->t = o.t;

	return *this;
}

double const EuropeanOption::Price(const double S) const{
	//price the current option
	double d1 = (log(S / this->K()) + (this->B() + pow(this->Sig(), 2) / 2)*t) / (this->Sig()*sqrt(t));
	double d2 = d1 - this->Sig()*sqrt(t);

	//declare a standard normal distribution object 
	normal sn;

	if (this->Type() == Call){
		//get call price using exact formula:
		return S*exp((this->B() - this->R())*t)*cdf(sn, d1) - this->K()*exp(-this->R()*t)*cdf(sn, d2);
	}
	else{
		//get put price using exact formula:
		return this->K()*exp(-this->R()*t)*cdf(sn, -d2) - S*exp((this->B() - this->R())*t)*cdf(sn, -d1);
	}
}

double const EuropeanOption::PriceByParity(const double S) const{
	//get corresponding put price by parity
	if (Type() == Call){
		return Price(S) + K()*exp(-R()*t) - S;
	}
	else{
		return Price(S) + S - K()*exp(-R()*t);
	}
}

std::vector<double> const EuropeanOption::BatchPrices(const std::vector<double>& ss) const{
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

std::vector<double> const EuropeanOption::BatchPrices(const std::vector<double>& expiries, const std::vector<double>& vol, const double S) const{
	//prices using expiries and vols
	//declare result vector
	std::vector<double> v_result;
	//double k = this->k;
	//double r = this->r;
	//double b = this->b;
	//OptionType type = this->type;
	for (unsigned int i = 0; i < expiries.size(); ++i){
		//looping over each possible T
		for (unsigned int j = 0; j < vol.size(); ++j){
			//looping over each possible sig
			EuropeanOption tmp(K(), expiries[i], R(), vol[j], B(), Type());
			//construct an option according to the specifics we have
			v_result.push_back(tmp.Price(S));
			//insert data into the vector
		}
	}
	return v_result;
}

std::string const EuropeanOption::ToString() const{
	std::stringstream ss;//get string stream object
	//loading data to stream
	ss <<"strike price: "<< K() <<", maturity: " << t<<", interest rate: " << R()<<", constant volatility: " << Sig()<<", cost of carry: " << B()<<", optiontype: "<<Type();
	return ss.str();
}

double const EuropeanOption::delta(const double S) const{
	//C vs S derivative
	double d1 = (log(S / K()) + (B() + pow(Sig(), 2) / 2)*t) / (Sig()*sqrt(t));
	//declare standard normal distr object
	normal sn;
	//get derivative
	if (Type() == Call){
		return exp((B() - R())*t)*cdf(sn, d1);
	}
	else{
		return exp((B() - R())*t)*(cdf(sn, d1) - 1);
	}
}

double const EuropeanOption::gamma(const double S) const{
	//C vs S second derivative
	double d1 = (log(S / K()) + (B() + pow(Sig(), 2) / 2)*t) / (Sig()*sqrt(t));
	//declare standard normal distr object
	normal sn;
	//get derivative
	return pdf(sn, d1)*exp((B() - R())*t) / (S*Sig()*sqrt(t));
}

double const EuropeanOption::vega(const double S) const{
	//C vs sigma derivative
	double d1 = (log(S / K()) + (B() + pow(Sig(), 2) / 2)*t) / (Sig()*sqrt(t));
	//declare standard normal distr object
	normal sn;
	//get derivative
	return S*sqrt(t)*exp((B() - R())*t)*pdf(sn, d1);
}

double const EuropeanOption::theta(const double S) const{
	//minus C vs T derivative
	double d1 = (log(S / K()) + (B() + pow(Sig(), 2) / 2)*t) / (Sig()*sqrt(t));
	double d2 = d1 - Sig()*sqrt(t);
	//declare standard normal distr object
	normal sn;
	//get derivative
	if (Type() == Call){
		return -S*Sig()*exp((B() - R())*t)*pdf(sn, d1) / (2 * sqrt(t)) - (B() - R())*S*exp((B() - R())*t)*cdf(sn, d1) - R()*K()*exp(-R()*t)*cdf(sn, d2);
	}
	else{
		return -S*Sig()*exp((B() - R())*t)*pdf(sn, d1) / (2 * sqrt(t)) + (B() - R())*S*exp((B() - R())*t)*cdf(sn, -d1) + R()*K()*exp(-R()*t)*cdf(sn, -d2);
	}
}

double const EuropeanOption::rho(const double S) const{
	double d1 = (log(S / K()) + (B() + pow(Sig(), 2) / 2)*t) / (Sig()*sqrt(t));
	double d2 = d1 - Sig()*sqrt(t);
	//declare standard normal distr object
	normal sn;
	//get result
	if (Type() == Call){
		return K()*t*exp(-R()*t)*cdf(sn, d2) / 100;
	}
	else{
		return -K()*t*exp(-R()*t)*cdf(sn, -d2) / 100;
	}
}

std::vector<double> const EuropeanOption::BatchDeltas(const std::vector<double>& ss) const{
	//declare a result vector
	std::vector<double> v;
	//looping over input array and get delta for each possible S
	for (unsigned int i = 0; i < ss.size(); ++i){
		v.push_back(delta(ss[i]));
	}
	return v;
}

std::vector<double> const EuropeanOption::BatchGammas(const std::vector<double>& ss) const{
	//declare a result vector
	std::vector<double> v;
	//looping over input array and get delta for each possible S
	for (unsigned int i = 0; i < ss.size(); ++i){
		v.push_back(gamma(ss[i]));
	}
	return v;
}

//calculate delta using divided difference method
double const EuropeanOption::delta_df(const double S, const double h) const{
	return (Price(S+h)-Price(S-h)) / (2*h);
}

//calculate gamma using divided difference method
double const EuropeanOption::gamma_df(const double S, const double h) const{
	return (Price(S+h)-2*Price(S)+Price(S-h)) / pow(h,2);
}

//delta against an array of S
std::vector<double> const EuropeanOption::BatchDeltas_df(const std::vector<double>& ss, const double h) const{
	//declare a result vector
	std::vector<double> v;
	//looping over input array and get delta for each possible S
	for (unsigned int i = 0; i < ss.size(); ++i){
		v.push_back(delta_df(ss[i],h));
	}
	return v;
}

//gamma against an array of S
std::vector<double> const EuropeanOption::BatchGammas_df(const std::vector<double>& ss, const double h) const{
	//declare a result vector
	std::vector<double> v;
	//looping over input array and get delta for each possible S
	for (unsigned int i = 0; i < ss.size(); ++i){
		v.push_back(gamma_df(ss[i],h));
	}
	return v;
}