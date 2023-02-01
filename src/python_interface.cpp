#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <iostream>
#include "core.hpp"

namespace py = pybind11;  

using namespace std;


py::list eval(py::list expressions, Eigen::Ref<const Eigen::MatrixXd> &dataset, bool verbose=false) { 
  // transform to vector of strings
  if (verbose) 
    cout << "Reading in expressions:" << endl;
  vector<string> exprs; exprs.reserve(expressions.size());
  for (py::handle obj : expressions) {  // iterators!
    string expr = obj.attr("__str__")().cast<std::string>();
    if (verbose) 
      cout << "\tRead in: " << expr << endl;
    exprs.push_back(expr);
  }
  // transform to vectors of tokens (i.e. vecotr of vectors of strings)
  if (verbose) 
    cout << "Splitting expressions into tokens:" << endl;
  auto exprs_split = split::strsplit(exprs);
  
  // evaluate expressions
  if (verbose) 
    cout << "Evaluating expressions:" << endl;

  py::list res;
  for(auto & expr : exprs_split) {
    res.append(fe::eval(expr, dataset).first);
  }
  if (verbose) 
    cout << "Done." << endl;
  return res;
}

int read_data(Eigen::Ref<const Eigen::MatrixXd> &d) {
  cout << d << endl;
  return 1;
}


PYBIND11_MODULE(_pyfe, m) {
  m.doc() = "pybind11-based interface for fast_eval"; // optional module docstring
  m.def("eval", &eval, "Evaluates a list of expressions on the given dataset");
  m.def("read_data", &read_data, "Reads in a dataset");
}
