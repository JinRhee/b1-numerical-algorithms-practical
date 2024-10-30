#include <iostream>

/**
 * @brief Calculate pi by monte carlo
 * 
 * @param iter_num 
 * @return float 
 */
float get_pi(int iter_num = 100) {
    float x, y;
    int total_count = 0, inside_count = 0;
    std::srand(std::time(nullptr));     // Set rng seed
    for(int i = 0; i < iter_num; i++) {
        float x = static_cast<float>(rand()/static_cast<float>(RAND_MAX));
        float y = static_cast<float>(rand()/static_cast<float>(RAND_MAX));
        if (std::pow(x, 2) + std::pow(y, 2) <= 1.0) inside_count++;
        total_count++;
    }
    return static_cast<float>(inside_count / static_cast<float>(total_count) * 4);
}
int main() {
    float pi = get_pi(100);
    std::cout << "Pi estimate: " << pi << std::endl;
    return 0;
}