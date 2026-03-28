#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Base * generate(void) {
    int r = std::rand() % 100;
    std::cout << "r = " << r << std::endl;
    if (r < 33)
        return new A;
    else if (r >= 33 && r <= 66)
        return new B;
    else
        return new C;
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown classes" << std::endl;
}

void identify(Base& p) {
    try {
            (void)dynamic_cast<A&>(p);
            std::cout << "A" << std::endl;
            return ;
    }
    catch(const std::exception& e) {
        std::cerr << "TRY CAST A: " << e.what() << '\n';
    }
    try {
            (void)dynamic_cast<B&>(p);
            std::cout << "B" << std::endl;
            return ;
    }
    catch(const std::exception& e) {
        std::cerr << "TRY CAST B: " << e.what() << '\n';
    }
    try {
            (void)dynamic_cast<C&>(p);
            std::cout << "C" << std::endl;
            return ;
    }
    catch(const std::exception& e) {
        std::cerr << "TRY CAST C: " << e.what() << '\n';
    }
}

int main(void) {
    std::srand(time(0));

    Base *b = generate();

    identify(b);
    identify(*b);

    delete b;
    return 0;
}