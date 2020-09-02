#include<iostream>
#include<cstdlib>
int main(int argc, char **argv)
{
	std::cout.precision(15);
	std::cout.setf(std::ios::scientific);
	double under = 1.0;
	double over = 1.0;
	int N = std::atoi(argv[1]);
	for(int ii = 0; ii <= N; ii++){
		under = under / 2.0;
		over = over * 2.0;
		std::cout<< ii << " "<< under << " " << over << "\n";
	}
	return 0;
}
