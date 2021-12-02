import numpy as np
import matplotlib.pyplot as plt
import os

def read_distribution(filename):
    values = {}
    total = 0
    result_sum = 0
    with open(filename, 'r') as f:
        for line in f:
            x = int(line)
            if not x in values:
                values[x] = 0
            values[x] += 1
            total += 1
            result_sum += x
              
    return {x: n / total for x, n in values.items()}, result_sum / total


directory = 'dist'

for filename in os.listdir(directory):
    if os.path.splitext(filename)[1] == '.txt':
        path = os.path.join(directory, filename)
        
        dist, avg = read_distribution(path)
        xs = np.fromiter(dist.keys(), dtype=int)
        ys = np.fromiter(dist.values(), dtype=float)
        
        plt.bar(xs, ys, color='navy')
        plt.xlabel('Value')
        plt.ylabel('Probability')
        
        plot_name = os.path.splitext(filename)[0]
        plt.title(plot_name + ' (avg: %.2f)' % avg)
        
        out_path = os.path.join(directory, plot_name + '.png')
        
        if os.path.isfile(out_path):
            os.remove(out_path)
            
        plt.savefig(out_path)
        plt.clf()