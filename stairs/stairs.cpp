#include <iostream>
#include <fstream>

using namespace std;

ifstream ifile("stairs.inp");
ofstream ofile("stairs.out");

int main(){
  int M,F,N;
  ifile >> M >> F >> N;
  ofile << N/(M - 1) + 1 << endl;
  return 0;
}
