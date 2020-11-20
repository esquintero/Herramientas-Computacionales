#include <iostream>
#include "mpi.h"
#include <cstdlib>
#include <cmath>
#include <vector>

const int N = 6000000; //total number of iterations
const double XMIN = 0.0, XMAX = 100;
const double DX = (XMAX - XMIN)/N;

void integral(int pid, int np, int Nlocal);
void fill(std::vector<double> & data, int N, int Nlocal, int pid, int np);
void print(std::vector<double> & data, int N, int Nlocal, int pid, int np);

int main(int argc, char **argv)
{
  int np = 0, pid = 0;
  MPI_Init(&argc, &argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &pid);
  MPI_Comm_size(MPI_COMM_WORLD, &np);

  const int Nlocal = N/np; //share of iterations per processor
  std::vector<double> data(Nlocal);

  fill(data, N, Nlocal, pid, np);
  integral(pid, np, Nlocal);
  print(data, N, Nlocal, pid, np);
 
  data.shrink_to_fit();

  MPI_Finalize();
  return 0;
}

void integral(int pid, int np, int Nlocal)
{
  int tag = 0;
  double result = 0.0; //result is the sum of all other sums
  for(int ii = 0; ii <= Nlocal; ++ii)
    {
      sum += std::pow(pid*Nlocal + ii*DX, 2)*DX;
    }
  if(0 == pid){ //if pid = 0, compute integral
    double local_sum; //local_sum are the final computations of each process
    for(int src = 1; src < np; ++src){
      MPI_Recv(&local_sum, 1, MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      result += local_sum;
    }
    std::cout << "The definite integral of x^2 from " << XMIN << " to " << XMAX << " is " << result << "\n"; 
  } else { //send to manager process
    int manager = 0; //procces that will gather and sum all other results
    MPI_Send(&local_sum, 1, MPI_DOUBLE, manager, tag, MPI_COMM_WORLD);
  }
}

void fill(std::vector<double> & data, int N, int Nlocal, int pid, int np)
{
  for(int ii = 0; ii < Nlocal; ++ii){
    data[ii] = 2*(pid*Nlocal + ii);
  }
}

void print(std::vector<double> & data, int N, int Nlocal, int pid, int np)
{
  int tag = 0;
  if (0 == pid){
    std::vector<double> aux(Nlocal);
    for(int src = 1; src < np; ++src){
      MPI_Recv(aux, aux.size(), MPI_DOUBLE, src, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      print_local(aux, N, Nlocal, src, np);
    }
    aux.shrink_to_fit();
  } else {
    int manager = 0; //procces that will gather and sum all other results
    MPI_Send(data, Nlocal, MPI_DOUBLE, manager, tag, MPI_COMM_WORLD);
  }
}

void printlocal(std::vector<double> & data, int N, int Nlocal, int pid, int np)
{
  if (0 == pid){
    std::cout<< "pid= " << pid << ")" << "\n";
    for (int ii = 0; ii < Nlocal; ++ii){
      std::cout << data[ii] << " ";
    }
    std<<cout << "\n";
  }
} 
