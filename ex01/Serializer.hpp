#pragma once
#include <iostream>
#include <stdint.h>

struct Data;

class Serializer {
    private:
        Serializer();
        Serializer(const Serializer& obj);
        Serializer& operator=(const Serializer& obj);
        ~Serializer();
    public:
        static uintptr_t serialize(Data *ptr);
        static Data* deserialize(uintptr_t raw);
};


