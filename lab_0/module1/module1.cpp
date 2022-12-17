#include "module1.h"

namespace Module1 {
    std::string getMyName() {
        std::string name = "John.";
        return name;
    }

    namespace Inner {
        std::string getMyName() {
            std::string name = "Vlad";
            return name;
        }
    }
}
