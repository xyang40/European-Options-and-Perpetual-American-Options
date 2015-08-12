#include "PerpetualAmericanOption.h"
#include<iostream>

//global function to create a mesh array of prices with step h
std::vector<double> const CreateMeshArray(double start, const int num, const double h){
	//start defines the first number;
	//num defines how many numbers we want
	//h is the step size
	std::vector<double> v;
	//therefore looping num times in total starting from start incrementing by h
	for (int i = 1; i <= num; ++i){
		//inserting into the vector
		v.push_back(start);
		start += h;
	}
	return v;
}

//test Perpetual American Option functions
int main(){
    //creating call and put options
	PerpetualAmericanOption option_call(100, 0.1, 0.1, 0.02, Call);
	PerpetualAmericanOption option_put(100, 0.1, 0.1, 0.02, Put);
	//test pricing function
	std::cout <<"Call price: "<< option_call.Price(110) << std::endl;
	std::cout << "Put price: " << option_put.Price(110) << std::endl;

	//testing batch pricing functions
	//create input function
	std::vector<double> const v_s = CreateMeshArray(10, 41, 1);
	std::vector<double> result_call = option_call.BatchPrices(v_s);
	std::vector<double> result_put = option_put.BatchPrices(v_s);
	//print out two vectors
	for (unsigned int i = 0; i < result_call.size(); ++i){
		std::cout <<"call price: "<< result_call[i] << std::endl;
	}
	for (unsigned int i = 0; i < result_put.size(); ++i){
		std::cout <<"put price: "<< result_put[i] << std::endl;
	}

	//customized input params:
	double K, S, sig, r, b;
	std::cout << "K: ";
	std::cin >> K;
	std::cout << "S: ";
	std::cin >> S;
	std::cout << "sig: ";
	std::cin >> sig;
	std::cout << "r: ";
	std::cin >> r;
	std::cout << "b: ";
	std::cin >> b;
	PerpetualAmericanOption call_test(K, sig, r, b, Call);
	PerpetualAmericanOption put_test(K, sig, r, b, Put);

	std::cout << call_test.Price(S) << std::endl;
	std::cout << put_test.Price(S) << std::endl;


	return 0;
}