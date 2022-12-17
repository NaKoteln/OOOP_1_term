#include "module1/module1.h"
#include "module2/module2.h"
#include "module3/module3.h"
#include <iostream>

std::string getMyName() {
    std::string name = "main";
    return name;
}

int main(int argc, char **argv) {
    std::cout << "Hello world!" << "\n";

    std::cout << Module1::getMyName() << "\n";
    std::cout << Module2::getMyName() << "\n";

    using namespace Module1;
    std::cout << ::getMyName() << "\n"; // (A)
    std::cout << Module2::getMyName() << "\n";

    using namespace Module2; // (B)
    std::cout << Module2::getMyName() << "\n"; // COMPILATION ERROR (C)
    std::cout << Module1::Inner::getMyName() << "\n";

    using Module2::getMyName;
    std::cout << getMyName() << "\n"; // (D)

    using namespace std;
    cout << Module3::getMyName() << "\n";
}
