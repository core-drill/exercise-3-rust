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

data_likelihood = np.loadtxt('likelihood.txt')
mu = data_likelihood[:, 0]
likelihood = data_likelihood[:, 1]
plt.plot(mu, likelihood)
plt.xlabel(r'($\mu$)')
plt.ylabel(r'$\mathcal{L}$ ($\mu$)')
plt.savefig('likelihood.png', dpi=400)
plt.close()

data_loglikelihood = np.loadtxt('nll.txt')
mu_log = data_loglikelihood[:, 0]
log_likelihood = data_loglikelihood[:, 1]
plt.plot(mu_log, log_likelihood)
plt.xlabel(r'($\mu$)')
plt.ylabel(r'- 2 * log $\mathcal{L}$ ($\mu$)')
plt.savefig('loglikelihoods.png', dpi=400)
plt.close()

data_deltaNLL = np.loadtxt('deltanll.txt')
mu_delta = data_deltaNLL[:, 0]
delta_nll = data_deltaNLL[:, 1]
plt.plot(mu_delta, delta_nll)
plt.xlabel(r'($\mu$)')
plt.ylabel(r'- 2 * log $\mathcal{L}$ ($\mu$')
plt.savefig('delta_nll.png', dpi=400)