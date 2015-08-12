#include<vector>
#include<string>
#include<iostream>
#include "Option.h"

#ifndef EUOption_H
#define EUOption_H

//declare the class for European option
class EuropeanOption: public Option{
private:
	double t;//maturity
public:
	EuropeanOption(double k, double t, double r, double s, double b, OptionType ot): Option(k,s,r,b,ot),t(t){};//constructor with full params
	EuropeanOption(const EuropeanOption& o): Option(o.K(), o.Sig(), o.R(), o.B(), o.Type()), t(t){};//copy constructor;
	EuropeanOption& operator=(const EuropeanOption&);//overloading assignment operator
	~EuropeanOption(){};//default destructor

	double T() const{//return maturity
		return this->t;
	}

	void T(const double t){//set maturity
		this->t = t;
	}

	double const Price(const double S) const;//price the current option
	double const PriceByParity(const double S) const;//get corresponding price by parity
	std::vector<double> const BatchPrices(const std::vector<double>& ss) const;//prices using an array of S
	std::vector<double> const BatchPrices(const std::vector<double>& expiries, const std::vector<double>& vol, const double S) const;//prices using expiries and vols

	std::string const ToString() const;//overloading tostring function

	//greek functions
	double const delta(const double S) const;
	double const gamma(const double S) const;
	double const vega(const double S) const;
	double const theta(const double S) const;
	double const rho(const double S) const;
	std::vector<double> const BatchDeltas(const std::vector<double>& ss) const;//calculate deltas against an array
	std::vector<double> const BatchGammas(const std::vector<double>& ss) const;//calculate gammas against an array

	//simulating delta and gamma using divided difference
	double const delta_df(const double S, const double h) const;
	double const gamma_df(const double S, const double h) const;
	std::vector<double> const BatchDeltas_df(const std::vector<double>& ss,const double h) const;//calculate deltas against an array
	std::vector<double> const BatchGammas_df(const std::vector<double>& ss,const double h) const;//calculate gammas against an array
};

#endif