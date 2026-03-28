#include "ScalarConverter.hpp"

int main(int ac, char **av) {
    if (ac < 2) {
        std::cout << "Error: needs a argument" << std::endl; return 0;
    }
    if (!av[1]) {
        std::cout << "Error: needs a argument" << std::endl; return 0;
    }
    if (av[2]) {
        std::cout << "Error: too much argument" << std::endl; return 0;
    }
    ScalarConverter sc;
    sc.converter(av[1]);
    return 0;
}