#ifndef FAST_EVAL
#define FAST_EVAL

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <iterator>
#include <Eigen/Core>
#include <Eigen/Dense>


using namespace std;
using namespace Eigen;

namespace fe {

  // This it the core of the library. 
  // Credit goes to Luca Manzoni (https://naturalcomputinglab.github.io/people/lmanzoni) 
  // for the idea of using this implementation and providing pseudo-code.

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

  pair<ArrayXd, int> eval(const vector<string> &stack, const MatrixXd &D, int idx=0) {
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


  // Credit: Nawaz https://stackoverflow.com/a/5607650
  struct tokens: std::ctype<char> 
  {
    tokens(): std::ctype<char>(get_table()) {}

    static std::ctype_base::mask const* get_table()
    {
      typedef std::ctype<char> cctype;
      static const cctype::mask *const_rc= cctype::classic_table();

      static cctype::mask rc[cctype::table_size];
      std::memcpy(rc, const_rc, cctype::table_size * sizeof(cctype::mask));

      rc[','] = std::ctype_base::space; 
      return &rc[0];
    }
  };

  vector<vector<string>> strsplit(const vector<string> & vs) {
    vector<vector<string>> vvs;
    for (auto s : vs) {
      std::stringstream ss(s);
      ss.imbue(std::locale(std::locale(), new tokens()));
      std::istream_iterator<std::string> begin(ss);
      std::istream_iterator<std::string> end;
      std::vector<std::string> vstrings(begin, end);
      vvs.push_back(vstrings);
    }
    return vvs;
  }

  vector<string> strsplit(const string &s) {
    vector<string> v = {s};
    return strsplit(v)[0];
  }

} 

#endif
