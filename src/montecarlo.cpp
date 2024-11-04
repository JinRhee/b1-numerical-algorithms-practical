#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <iomanip>
#include <limits>
#include <chrono>

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
 * @brief Monte Carlo for timing purpose (no saving in vector)
 * 
 * @param iter_num 
 * @param r_vec 
 * @return double 
 */
double monte_carlo_timing(const int& iter_num) {
    double r_squared;   // Does using r or r^2 matter?
    int total_count = 0, inside_count = 0;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    
    for(int i = 0; i < iter_num; i++) {
        r_squared = std::pow(distribution(generator), 2) + std::pow(distribution(generator), 2);
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
    x_prev = x + err * 2;
    count = 0;
    //std::cout << "error:" << err << std::endl;
    while (fabs(x - x_prev) >= err) {
        temp = x;
        x = x_prev - static_cast<double>(tanf(x_prev));
        x_prev = temp;
        count++;
        //std::cout << std::setprecision(19) << x << ' ' << x_prev << ' ' << fabs(x - x_prev) << std::endl;
        if(fabs(x - x_prev) < err) {
            break;
        }
    }
    return static_cast<double>(x);
}

/**
 * @brief Newton-Raphson for timing purpose
 * 
 * @param x_0 
 * @param err 
 * @return double 
 */
double newton_raphson_timing(double x_0, double err) {
    double x, x_prev, temp;
    x = x_0;
    x_prev = x + err * 2;
    while (fabs(x - x_prev) >= err) {
        temp = x;
        x = x_prev - static_cast<double>(tanf(x_prev));
        x_prev = temp;
        if(fabs(x - x_prev) < err) {
            break;
        }
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
    double pi = 3.1415926535897932;
    double estimate;
    myfile << std::setprecision(std::numeric_limits<double>::max_digits10);

    // Monte Carlo
    myfile.open("./results/montecarlo.txt");
    myfile << "N,estimate,variance,error" << std::endl;

    for(int i = 0; i < 25; i++) {
        std::cout << i << std::endl;
        int N = static_cast<int>(std::round(std::pow(2, i)));
        estimate = monte_carlo(N, r_vec);
        myfile << N << ',' << estimate << ',' << get_variance(r_vec) << ',' << fabs((pi - estimate)) << std::endl;
    }
    myfile.close();
    
    // Newton Raphson
    int count;
    myfile.open("./results/newton_raphson.txt");
    myfile << "estimate,stop_error,count,error" << std::endl;
    for(int i = 0; i < 8; i++) {
        estimate = newton_raphson(2.0, std::pow(0.1, i), count);
        myfile << estimate << ',' << std::pow(0.1, i)<< ',' << count << ',' << fabs((pi - estimate)) << std::endl;
    }
    // Custom error value: 5.0e-08
    myfile << newton_raphson(2.0, 5.0e-08, count) << ',' << count << ',' << 5.0e-08 << std::endl;
    myfile << newton_raphson(2.0, 3.0e-08, count) << ',' << count << ',' << 5.0e-08 << std::endl;
    myfile.close();
    
    // Chudnovsky
    myfile.open("./results/chudnovsky.txt");
    myfile << "estimate,iter_num,error" << std::endl;
    for(double i = 0.0; i < 30.0; i++) {
        estimate = chudnovsky(i);
        myfile << estimate << ',' << i << ',' << fabs((pi - estimate)) << std::endl;
    }
    myfile.close();

    // Timing
    std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);
    auto t1 = std::chrono::high_resolution_clock::now();
    monte_carlo_timing(std::pow(2, 24));
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << ms_double.count() << "ms " << monte_carlo_timing(std::pow(2, 24)) << std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    newton_raphson_timing(2.0, 3.0e-08);
    auto t4 = std::chrono::high_resolution_clock::now();
    ms_double = t4 - t3;
    std::cout << ms_double.count() << "ms " << newton_raphson_timing(2.0, 3.0e-08) << std::endl;

    auto t5 = std::chrono::high_resolution_clock::now();
    chudnovsky(2.0);
    auto t6 = std::chrono::high_resolution_clock::now();
    ms_double = t6 - t5;
    std::cout << ms_double.count() << "ms " << chudnovsky(2.0) << std::endl;

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