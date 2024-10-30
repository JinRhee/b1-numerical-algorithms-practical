#include <iostream>
#include <fstream>
#include <random>

/**
 * @brief Calculate pi by monte carlo with RV following uniform distribution
 * 
 * @param iter_num 
 * @return float 
 */
float get_pi(int iter_num = 100) {
    float x, y;
    int total_count = 0, inside_count = 0;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    for(int i = 0; i < iter_num; i++) {
        if (std::pow(distribution(generator), 2) + std::pow(distribution(generator), 2) <= 1.0) {
            inside_count++;
        }
        total_count++;
    }
    return static_cast<float>(inside_count / static_cast<float>(total_count) * 4);
}
int main() {
    std::ofstream myfile;
    myfile.open("../file.txt");
    for(int i = 0; i < 13; i++) {
        myfile << std::pow(5, i) << ',' << get_pi(std::pow(5, i)) << std::endl;
    }
    myfile.close();
    return 0;
}