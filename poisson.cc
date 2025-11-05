#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
    return std::exp(-mu) * std::pow(mu, k) / std::tgamma(k + 1);
    return 0;
}

int main() {
    std::vector<int> data(11);

    std::ifstream fin("datensumme.txt");
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        data[n_i]++;
    }
    fin.close();
    for(int k = 0 ; k <= 10 ; ++k) {
        std::cout << k << " " << data[k] << " " << std::endl;
    }
    std::ofstream output_file_variance("hist.txt");
    if (!output_file_variance.is_open()) {
        std::cout << "cannot create hist.txt" << std::endl;
        return 1;
    }
    for(int k = 0 ; k <= 10 ; ++k) {
        output_file_variance << k << " " << data[k] << std::endl;
    }
    std::vector<int> possion_list(11);
    double mu = 3.11538;
    for(int k = 0 ; k <= 10 ; ++k) {
        possion_list[k] = static_cast<int>(poisson(mu, k) * 234);
    }
    std::ofstream output_file_poisson("histpoi.txt");
    if (!output_file_poisson.is_open()) {
        std::cout << "cannot create histpoi.txt" << std::endl;
        return 1;
    }
    for(int k = 0 ; k <= 10 ; ++k) {
        output_file_poisson << k << " " << data[k] << " " << possion_list[k] << std::endl;
    }

    return 0;
}