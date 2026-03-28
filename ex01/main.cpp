#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

int main() {
    Data data;
    data.val = 42;

    // Serialize the pointer
    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized value: " << raw << std::endl;

    // Deserialize back to pointer
    Data* ptr = Serializer::deserialize(raw);
    std::cout << "Deserialized value: " << ptr->val << std::endl;

    // Check if the pointer is the same
    if (ptr == &data)
        std::cout << "Pointer restored correctly!" << std::endl;
    else
        std::cout << "Pointer restoration failed!" << std::endl;

    return 0;
}
