#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <iomanip>
#include <limits>

/**
 * @brief Calculate pi by monte carlo with RV following uniform distribution
 * 
 * @param iter_num 
 * @param r_vec 
 * @return double 
 */
double monte_carlo(const int& iter_num, std::vector<double>& r_vec) {
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
    return static_cast<double>(inside_count / static_cast<double>(total_count) * 4);
}

/**
 * @brief Get the average from vector
 * 
 * @param vec 
 * @return double 
 */
double get_average(const std::vector<double>& vec) {
    if(vec.empty()) {
        return 0;
    }
    auto const count = static_cast<double>(vec.size());
    return std::reduce(vec.begin(), vec.end()) / count;
}

/**
 * @brief Get the variance from vector
 * 
 * @param vec 
 * @return double 
 */
double get_variance(std::vector<double>& vec) {
    // Central Limit Theorem: For large N, error is asymptotically Normally distributed
    int const count = vec.size();
    auto const avg = get_average(vec);
    double variance = 0.0;

    for (auto itr = vec.begin(); itr != vec.end(); itr++) {
        variance += std::pow((avg - *itr), 2);
    }
    variance = variance / (count - 1);
    return variance;
}

/**
 * @brief Return result from Newton-Raphson method on sin function
 * 
 * @param x_0 
 * @param err 
 * @return double 
 */
double newton_raphson(double x_0, double err, int& count) {
    double x, x_prev, temp;
    x = x_0;
    x_prev = x + err;
    count = 0;
    //std::cout << std::setprecision(19) << x << std::endl;
    while (abs(x - x_prev) >= err) {
        temp = x;
        x = x_prev - static_cast<double>(tan(x_prev));
        x_prev = temp;
        count++;
        //std::cout << std::setprecision(19) << x << ' ' << x_prev << ' ' << std::endl;
    }
    return static_cast<double>(x);
}

/**
 * @brief Return factorial
 * 
 * @param num 
 * @return double 
 */
double fac(double num) {
    double result = 1.0;
    for (double i=2.0; i<num; i++)
       result *= i;
    return result;
}

/**
 * @brief Return PI estimate using Chudnovsky algorithm
 * 
 * @param digit 
 * @return double 
 */
double chudnovsky(double digit) {
    double approx = 0;
    for (double k = 0; k < digit; k++) {
        approx += (pow(-1.0,k) * fac(6.0 * k) * (13591409.0 + (545140134.0 * k))) 
            / (fac(3.0 * k) * pow(fac(k), 3.0) * pow(640320.0, 3.0 * k + 3.0/2.0));

    }
    approx *= 12.0;
    approx = 1/approx;
    return approx;
}


int main() {
    std::vector<double> r_vec;
    std::ofstream myfile;
    myfile.open("../results/montecarlo.txt");
    myfile << "N,estimate,variance" << std::endl;
    myfile << std::setprecision(std::numeric_limits<double>::max_digits10);
    
    for(int i = 0; i < 25; i++) {
        myfile << std::pow(2, i) << ',' << monte_carlo(std::pow(2, i), r_vec) << ',' << get_variance(r_vec) << std::endl;
    }
    myfile.close();

    int count;
    myfile.open("../results/newton_raphson.txt");
    myfile << "estimate,stop_error,count" << std::endl;
    for(int i = 0; i < 7; i++) {
        myfile << newton_raphson(2.0, std::pow(0.1, i), count) << ',' << count << ',' << std::pow(0.1, i) << std::endl;
    }
    myfile.close();
    
    myfile.open("../results/chudnovsky.txt");
    myfile << "estimate,iter_num" << std::endl;
    for(double i = 0.0; i < 10.0; i++) {
        myfile << chudnovsky(10.0*i) << ',' << 10.0*i << std::endl;
    }
    myfile.close();

    /*
    std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);
    std::cout << newton_raphson(2.0, count) << std::endl;
    std::cout << chudnovsky(10.0) << std::endl;
    std::cout << std::endl;
    std::cout << std::setprecision(50);
    std::cout << newton_raphson(2.0) << std::endl;
    std::cout << chudnovsky(10.0) << std::endl;
    
    double pi = 3.1415926535897932;
    */
    return 0;
}