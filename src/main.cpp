#include <iostream>
#include <cstdlib>
#include <chrono>

#include "graphics.h"
#include "environment.h"

using namespace std::chrono;

int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.precision(5);
    std::cout << std::fixed;

    if (argc != 2) {
        std::cout << "Expected exactly one argument: <path to config>" << std::endl;
        return -1;
    }
    environment_t env(argv[1]);

    if (!graphics::initialize(800, 600, env)) {
        return -1;
    }
    std::cout << "Graphics was successfully initialized" << std::endl;

    int64_t timestamp_lst = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    while (!graphics::should_finish()) {
        int64_t timestamp_cur = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        
        env.update((timestamp_cur - timestamp_lst) / 1000.0f);
        timestamp_lst = timestamp_cur;

        graphics::render();
    }

    graphics::destroy();

    std::cout << "Application was successfully finished" << std::endl;

    return 0;
}
