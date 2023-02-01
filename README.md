# fast_eval
Fast evaluation of symbolic expressions in C++

# Installation
Install the conda environment, then run `./make`

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
