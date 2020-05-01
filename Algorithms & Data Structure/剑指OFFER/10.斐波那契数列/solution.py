import numpy as np

base = np.array([[0, 1], [1, 1]])

def fib(x):
    if(x > 0):
        f0, f1 = fib(x // 2)
        if(x % 2 == 1):
            return f0**2 + f1**2, f1*(f1 + 2*f0)
        return f0*(f0+2*(f1-f0)), f0**2+f1**2

    return 0, 1


print([fib(i)[0] for i in range(10)])