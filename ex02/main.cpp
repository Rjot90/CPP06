#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <stdlib.h>
#include <fstream>
#include <iostream>

Base * generate(void) {
    std::ifstream urandom("/dev/urandom");
    if (!urandom)
        return NULL;

    unsigned int num = 0;

    if (!urandom.read(reinterpret_cast<char *>(&num), sizeof(num)))
        return NULL;
    int res = num % 3;

    std::cout << "result = " << res << std::endl;
    if (res == 0)
        return new A;
    else if (res == 1)
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
        std::cerr << "TRY CAST A: " << e.what() << std::endl;
    }
    try {
            (void)dynamic_cast<B&>(p);
            std::cout << "B" << std::endl;
            return ;
    }
    catch(const std::exception& e) {
        std::cerr << "TRY CAST B: " << e.what() << std::endl;
    }
    try {
            (void)dynamic_cast<C&>(p);
            std::cout << "C" << std::endl;
            return ;
    }
    catch(const std::exception& e) {
        std::cerr << "TRY CAST C: " << e.what() << std::endl;
    }
}

int main(void) {
    Base *b = generate();

    std::cout << std::endl;
    identify(b);
    std::cout << std::endl;
    identify(*b);
    std::cout << std::endl;

    delete b;
    return 0;
}