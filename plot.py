import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('hist.txt')
bin = data[:, 0]
events = data[:, 1]
plt.hist(bin, bins=bin, weights=events, density=False, alpha=0.6)
plt.xlabel('bins')
plt.ylabel('Events')
plt.savefig('hist.png', dpi=400)
plt.close()

data_poisson = np.loadtxt('histpoi.txt')
bin_poisson = data_poisson[:, 0]
events_poisson = data_poisson[:, 1]
fit_poisson = data_poisson[:, 2]
plt.hist(bin_poisson, bins=bin_poisson, weights=events_poisson, density=False, alpha=0.6, label='Data')
plt.scatter((np.array(bin_poisson)+0.5), fit_poisson, label='mu = 3.11538', color='red')
plt.xlabel('bins')
plt.ylabel('Events')
plt.legend()
plt.savefig('histpoi.png', dpi=400)
plt.close()

