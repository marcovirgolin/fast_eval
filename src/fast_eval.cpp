#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

map<string, pair<function<ArrayXd(const vector<ArrayXd> &)>, int>> ops = {
  {"+", {[](const vector<ArrayXd> &args){return args[0] + args[1];}, 2}},
  {"-", {[](const vector<ArrayXd> &args){return args[0] - args[1];}, 2}},
  {"*", {[](const vector<ArrayXd> &args){return args[0].cwiseProduct(args[1]);}, 2}},
  {"/", {[](const vector<ArrayXd> &args){return args[0].cwiseQuotient(args[1]);}, 2}},
  {"neg", {[](const vector<ArrayXd> &args){return -args[0];}, 1}},
  {"sqrt", {[](const vector<ArrayXd> &args){return args[0].sqrt();}, 1}},
  {"log", {[](const vector<ArrayXd> &args){return args[0].log();}, 1}},
  {"exp", {[](const vector<ArrayXd> &args){return args[0].exp();}, 1}},
  {"abs", {[](const vector<ArrayXd> &args){return args[0].abs();}, 1}},
  {"sin", {[](const vector<ArrayXd> &args){return args[0].sin();}, 1}},
  {"cos", {[](const vector<ArrayXd> &args){return args[0].cos();}, 1}},
  {"tan", {[](const vector<ArrayXd> &args){return args[0].tan();}, 1}},
  {"asin", {[](const vector<ArrayXd> &args){return args[0].asin();}, 1}},
  {"acos", {[](const vector<ArrayXd> &args){return args[0].acos();}, 1}},
  {"atan", {[](const vector<ArrayXd> &args){return args[0].atan();}, 1}},
};

pair<ArrayXd, int> eval(const vector<string> &stack, const MatrixXd & D, int idx) {
  cout << idx << endl;
  cout << stack[idx] << endl;
  if (ops.count(stack[idx])) {
    auto op = ops[stack[idx]];
    vector<ArrayXd> args; args.reserve(2);
    for (int i = 0; i < op.second; i++) {
      auto res = eval(stack, D, idx + 1);
      args.push_back(res.first);
      idx = res.second;
    }
    return {op.first(args), idx};
  } else if (stack[idx][0] == 'x') {
    int feat_idx = stoi(stack[idx].substr(2));
    return {D.col(feat_idx), idx};
  } else {
    return {ArrayXd::Constant(D.rows(), stod(stack[idx])), idx};
  }
}

int main() {
  MatrixXd dataset(3, 3);
  dataset << 1, 2, 3, 1, 2, 3, 1, 2, 3;
  cout << dataset << endl;
  auto res = eval({"+", "+", "x_0", "2", "*", "neg", "x_2", "-4.3"}, dataset, 0);
  cout << res.first << endl;
  return 0;
}