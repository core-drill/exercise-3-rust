#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

double poisson(double mu, int k) {
    return std::exp(-mu) * std::pow(mu, k) / std::tgamma(k + 1);
}

int main() {
    {
        std::ifstream fin("datensumme.txt");
        int n_i;
        double likelihood = 1.0;
        double mu = 3.11538;
        for(int i = 0 ; i < 234 ; ++i) {
            fin >> n_i;
            likelihood *= poisson(mu, n_i);
        }
        std::cout << "Likelihood: " << likelihood << std::endl;
        fin.close();
    }  

    {
        std::ifstream fin("datensumme.txt");
        int n_i;
        std::vector<double> likelihoods;
        std::vector<double> log_likelihoods;
        std::vector<double> delta_log_likelihoods;
        double mu_best = 3.11538;
        double best_likelihood = 1.0;
        double saturated_likelihood = 1.0;
        
        for(int i = 0 ; i < 234 ; ++i) {
            fin >> n_i;
            best_likelihood *= poisson(mu_best, n_i);
            saturated_likelihood *= poisson(n_i, n_i);
        }

        for(double mu = 0.0 ; mu <= 6.0 ; mu += 0.1) {
            double likelihood = 1.0;
            double log_likelihood = 0.0;
            fin.clear();
            fin.seekg(0, std::ios::beg);
            for(int i = 0 ; i < 234 ; ++i) {
                fin >> n_i;
                likelihood *= poisson(mu, n_i);
            }
            log_likelihood = -2 * std::log(likelihood);
            likelihoods.push_back(likelihood);
            log_likelihoods.push_back(log_likelihood);
            delta_log_likelihoods.push_back(log_likelihood - (-2 * std::log(best_likelihood)));
        }
        fin.close();
        std::ofstream fout("likelihood.txt");
        for(size_t i = 0 ; i < likelihoods.size() ; ++i) {
            fout << (i * 0.1) << " " << likelihoods[i] << std::endl;
        }
        fout.close();

        std::ofstream fout_log("nll.txt");
        for(size_t i = 0 ; i < log_likelihoods.size() ; ++i) {
            fout_log << (i * 0.1) << " " << log_likelihoods[i] << std::endl;
        }
        fout_log.close();

        std::ofstream fout_delta("deltanll.txt");
        for(size_t i = 0 ; i < delta_log_likelihoods.size() ; ++i) {
            fout_delta << (i * 0.1) << " " << delta_log_likelihoods[i] << std::endl;
        }
        fout_delta.close();

        // double lower_bound = 0.0;
        // double upper_bound = 0.0;
        // for(size_t i = 0 ; i < delta_log_likelihoods.size() ; ++i) {
        //     if(delta_log_likelihoods[i] <= 1.0 and delta_log_likelihoods[i-1] > 1.0) 
        //     {
        //         lower_bound = i * 0.1;
        //         break;
        //     }
        // }
        // for(size_t i = 0 ; i < delta_log_likelihoods.size() ; ++i) {
        //     if(delta_log_likelihoods[i] >= 1.0 and delta_log_likelihoods[i-1] < 1.0) 
        //     {
        //         upper_bound = i * 0.1;
        //         break;
        //     }
        // }
        
        // double delta_mu = (upper_bound - lower_bound) / 2.0;
        // std::cout << "Uncertainty from likelihood: +-" << delta_mu << std::endl;
        
        // double sum = 0.0;
        // double sum_sq = 0.0;
        // fin.clear();
        // fin.seekg(0, std::ios::beg);
        // for(int i = 0 ; i < 234 ; ++i) {
        //         fin >> n_i;
        //         sum += n_i;
        //         sum_sq += n_i * n_i;
        // }
        // double mean = sum / 234.0;
        // double variance = (sum_sq / 234.0) - (mean * mean);
        // double stddev = std::sqrt(variance / 234.0);
        // std::cout << "Uncertainty from standard deviation +-" << stddev << std::endl;

                
        // double saturated_likelihood = 1.0;
        // fin.clear();
        // fin.seekg(0, std::ios::beg);
        // for(int i = 0 ; i < 234 ; ++i) {
        //     fin >> n_i;
        //     saturated_likelihood *= poisson(n_i, n_i);
        // }
        double likelihood_ratio = best_likelihood / saturated_likelihood;
        std::cout << "best_likelihood: " << best_likelihood << std::endl;
        std::cout << "saturated_likelihood: " << saturated_likelihood << std::endl;
        std::cout << "- 2 * ln Likelihood ratio: " << -2*(std::log(best_likelihood) - std::log(saturated_likelihood)) << std::endl;
        std::cout << "- 2 * ln Likelihood ratio: " << -2*std::log(likelihood_ratio) << std::endl;

        int ndof = 234 - 1;
        std::cout << "Degrees of freedom: " << ndof << std::endl;
        double chi2_mean = ndof;
        double chi2_stddev = std::sqrt(2 * ndof);
        double z = (-2*std::log(likelihood_ratio) - chi2_mean) / chi2_stddev;
        std::cout << "Z-value: " << z << std::endl;


    }


    return 0;
}