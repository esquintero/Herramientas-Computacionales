#include <random>
#include <iostream>

const int NBINS = 20;
const double XMIN = 0.0, XMAX = 1.0;
const int N = 10000;
const int SEED = 1;
const double DXHISTO = (XMAX-XMIN)/NBINS;

int main(void)
{
	double histo[NBINS]={0.0};

	std::random_device rd;
        std::mt19937 gen(SEED); //generador
        std::uniform_real_distribution<double> dis(XMIN, XMAX);

	for(int n = 0; n < N; ++n) {
		double r = dis(gen);
		int bin = int((r - XMIN)/DXHISTO);
		histo[bin] += 1;
        }

	for(int ii = 0; ii <= NBINS; ++ii){
		std::cout<< XMIN + ii*DXHISTO << "\t" << histo[ii] << "\n";
	}

	return 0;
}
