#include <iostream>
#include <fstream>
#include <random>
#include <vector>

/**
 * @brief Calculate pi by monte carlo with RV following uniform distribution
 * 
 * @param iter_num 
 * @return float 
 */
float get_pi(const int& iter_num, std::vector<double>& r_vec) {
    double r_squared;   // Does using r or r^2 matter?
    int total_count = 0, inside_count = 0;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    for(int i = 0; i < iter_num; i++) {
        r_squared = std::pow(distribution(generator), 2) + std::pow(distribution(generator), 2);
        r_vec.push_back(r_squared);
        if (r_squared <= 1.0) {
            inside_count++;
        }
        total_count++;
    }
    return static_cast<float>(inside_count / static_cast<float>(total_count) * 4);
}

float get_average(const std::vector<double>& vec) {
    if(vec.empty()) {
        return 0;
    }
    auto const count = static_cast<float>(vec.size());
    return std::reduce(vec.begin(), vec.end()) / count;
}

float get_variance(std::vector<double>& vec) {
    // Central Limit Theorem: For large N, error is asympototically Normally distributed
    int const count = vec.size();
    auto const avg = get_average(vec);
    float variance = 0.0;

    for (auto itr = vec.begin(); itr != vec.end(); itr++) {
        variance += std::pow((avg - *itr), 2);
    }
    variance = variance / (count - 1);
    return variance;
}



int main() {
    std::vector<double> r_vec;
    std::ofstream myfile;
    myfile.open("../file.txt");
    myfile << "N,estimate,variance" << std::endl;
    for(int i = 0; i < 25; i++) {
        myfile << std::pow(2, i) << ',' << get_pi(std::pow(2, i), r_vec) << ',' << get_variance(r_vec) << std::endl;
    }
    myfile.close();
    return 0;
}