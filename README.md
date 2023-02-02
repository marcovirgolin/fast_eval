# pyfe
Fast evaluation of symbolic expressions in C++ with a Python interface.
The core algorithm is by [mnzluca](https://github.com/mnzluca).

# Installation
Install the conda environment, then compile and install with `make`:
```
conda env create -f environment.yml
conda activate pyfe
make
```

# Usage
Expressions need to be in prefix notation, with comma-separated terms.
The dataset must be a `np.ndarray`.
Here's an example:
```python
import numpy as np
from pyfe import fast

np.random.seed(42)
dataset = np.random.rand(5, 2)

expressions = ["+,-,x_1,x_0,2", "+,*,x_0,2.3,-1.2"]

result = fast.eval(expressions, dataset)
print(result)
```
