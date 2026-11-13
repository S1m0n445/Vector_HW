#include <iostream>
#include "Vector_1.h"
#include "Vector_2.h"
#include <algorithm>


bool compare(double a, double b)
    {
        return a > b;
    }

int main(){
    std::cout << "=============== Vector_v1 tests ===============" << std::endl;
    Vector1 e;
    std::cout << e.size() << "\n";
    Vector1 a(3, 6.7);
    std::cout << a.size() << " " << &a.get(0) << "\n";
    std::cout << a.get(1) << "\n";
    Vector1 b(5);
    for (std::size_t i = 0; i < b.size(); ++i) {
        b.set(i, i);
    }
    std::cout << b.size() << " ";
    for (std::size_t i = 0; i < b.size(); ++i) {
        std::cout << b.get(i) << " ";
    }
    std::cout << "\n";
    std::cout << "===============================================" << std::endl;

    std::cout << "=============== Vector_v2 tests ===============" << std::endl;
    Vector2 c{1.0, 2.5, 3.5, 4.5};
    std::cout << "init_list " << c.size() << " ";
    for (std::size_t i = 0; i < c.size(); ++i) {
        std::cout << c[i] << " ";
    }
    std::cout << "\n";
    Vector2 d = c;
    d[0] = 100.0;
    std::cout << "copy " << c[0] << " " << d[0] << "\n";
    Vector2 e3;
    e3 = c;
    e3[1] = 200.0;
    std::cout << "assign " << c[1] << " " << e3[1] << "\n";
    e3 = e3;
    std::cout << "self_assign " << e3.size() << " " << e3[0] << "\n";
    Vector2 f = Vector2{10.0, 20.0, 30.0};
    std::cout << "move_ctor " << f.size() << " " << f[0] << "\n";
    Vector2 g;
    g = Vector2{40.0, 50.0, 60.0};
    std::cout << "move_assign " << g.size() << " " << g[0] << "\n";
    const Vector2& cref = c;
    std::cout << "const " << cref.at(0) << " " << cref[1] << "\n";
    Vector2 n{2.0, 5.6, 2.7, 1.0};
    std::sort(n.begin(), n.end());
    for (int i = 0; i < n.size(); ++i)
    {
        std::cout << n[i] << " ";
    }
    std::cout << "\n";
    std::sort(n.begin(), n.end(), [](double a, double b){return a > b;});
    for (int i = 0; i < n.size(); ++i)
    {
        std::cout << n[i] << " ";
    }
    std::cout << "\n";
    std::cout << "===============================================" << std::endl;

    return 0;
}