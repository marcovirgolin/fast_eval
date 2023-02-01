#include "core.hpp"
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;

int main(int argc, char** argv) {
  MatrixXd dataset(3, 3);
  dataset << 1, 2, 3, 1, 2, 3, 1, 2, 3;
  cout << dataset << endl;
  auto res = fe::eval({"+", "+", "x_0", "2", "*", "neg", "x_2", "-4.3"}, dataset);
  cout << res.first << endl;
  return 0;
}