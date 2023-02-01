import sys, os

sys.path.insert(0, os.path.join(
  os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'pyfe'))

import _pyfe

def eval(expressions, dataset, verbose=False):
  """Evaluate expressions on dataset.
  Parameters
  ----------
  expressions : list of str
    Expressions to evaluate expressed as strings in prefix order, arguments should be comma-separted.
    E.g., '+,*,x_0,2.3,-1.2' represents 2.3*x_0 + (-1.2)
  dataset : numpy.ndarray
    Numpy dataset to evaluate expressions on.
    Rows are observations and columns are features.
  verbose : bool
    If True, print progress.
  Returns
  -------
  results : list of np.ndarray
    Results of evaluations for the expressions on the dataset.
  """
  results = _pyfe.eval(expressions, dataset, verbose)
  return results