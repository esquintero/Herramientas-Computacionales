#include <iostream>
#include <cmath>

//double func_legendre();
const double DX = 0.01;
const double XMIN = -1.0;
const double XMAX = 1.0;
const int N = 5;

int main(void)
{
	std::cout.precision(15); std::cout.setf(std::ios::scientific);

	for(double ii = XMIN; ii <= XMAX; ii += DX){

		double NUM = std::legendre(N, ii);
		std::cout<< ii << "\t"<<NUM << "\n";
	}

	return 0;
}
