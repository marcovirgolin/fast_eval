#include "core.hpp"
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <time.h>

using namespace std;

int main(int argc, char** argv) {
  // Runs a speed test
  clock_t start, end;
  string expr = "*,6.67,/,*,x_0,x_1,*,x_2,x_2";
  auto expr_v = fe::strsplit(expr);
  int e;
  int n;
  for(int e = 3; e < 6; e++){
    for(int n = 3; n < 6; n++){
      // create a random training set
      auto X_train = MatrixXd::Random(pow(10,n),3);
      start = clock();
      for(int i = 0; i < pow(10,e); i++) {
        auto out = fe::eval(expr_v, X_train);
      }
      end = clock();
      double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
      cout << "e=10^"<<e<<", n=10^"<<n<<", runtime: "<<time_taken<<"s"<<endl;
    }
  }
  return 0;
}