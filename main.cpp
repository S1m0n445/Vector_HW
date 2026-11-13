#include <iostream>
#include "Vector.h"

int main(){
    std::cout << "=============== Vector_v1 tests ===============" << std::endl;
    Vector e;
    std::cout << e.size() << "\n";
    Vector a(3, 6.7);
    std::cout << a.size() << " " << &a[0]<< "\n";
    std::cout << a[1] << " " << a.at(1) << "\n";
    std::cout << a[10] << " " << a.at(10) << "\n";

    std::cout << "===============================================" << std::endl;

    std::cout << "=============== Vector_v2 tests ===============" << std::endl;

    
    std::cout << "===============================================" << std::endl;

    return 0;
}