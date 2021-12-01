import numpy as np
import matplotlib.pyplot as plt


def read_values(filename):
    xs, ys = [], []
    with open(filename, 'r') as f:
        for line in f:
            x, y = line.strip().split()
            xs.append(int(x)) 
            ys.append(float(y))
            xs.append(0)
            ys.append(0)
              
    return np.array(xs), np.array(ys)


# Insertion sort
ix, iy = read_values('isort.txt')
ip = np.polyfit(ix, iy, 2)

# Quicksort
qx, qy = read_values('qsort.txt')
qp = np.polyfit(qx, qy, 2)


#Drawing the plot
fig = plt.figure()
x = np.linspace(0, 100, 100)

plt.title('Sorting speed')
plt.xlabel('Array size')
plt.ylabel('Time (mcs)')
plt.grid()

plt.plot(x, np.polyval(ip, x), color='navy', label='Insertion sort')
plt.plot(x, np.polyval(qp, x), color='red', label='Quicksort')

plt.legend()
plt.show()
