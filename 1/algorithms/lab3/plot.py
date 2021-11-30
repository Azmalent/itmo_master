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


# Quicksort
qx, qy = read_values('qsort.txt')
qp = np.polyfit(qx, qy, 2)


#Drawing the plot
fig = plt.figure()
x = np.linspace(0, 250, 5)

plt.title('Sorting speed')
plt.xlabel('Min elements for quicksort')
plt.ylabel('Time (mcs)')
plt.grid()

plt.plot(qx, qy, 'g.', x, np.polyval(qp, x), 'b-')

plt.show()
