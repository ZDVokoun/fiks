import numpy as np
from scipy.optimize import linprog

def minimize_sum_linear_equations(A, b):
    # Define the objective function to minimize the sum of variables
    c = np.ones(A.shape[1])

    # Define the inequality constraints x >= 0
    bounds = [(0, None) for _ in range(A.shape[1])]


    # Solve the linear programming problem
    result = linprog(c=c, bounds=bounds, A_eq=A, b_eq=b)

    # Return the solution
    return result.x

for _ in range(1000):
    A = np.random.rand(2,100)
    b = np.random.rand(1,2)
    
    res = minimize_sum_linear_equations(A,b)
    summ = 0
    if res is not None:
        for n in res:
            if n != 0:
                summ += 1
    if summ > 2:
        print(res)

