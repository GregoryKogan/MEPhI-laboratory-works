//
// Created by Gregory Kogan on 06.05.2023.
//

#ifndef SEQUENCE_LIB_TEST_HPP
#define SEQUENCE_LIB_TEST_HPP

#include <iostream>
#include <string>

#include "../IO/colored_logs.hpp"

namespace kogan {

class Test {
    std::string name;
    void (*testFunction)();

   public:
    Test(std::string name, void (*testFunction)());
    [[nodiscard]] bool run() const;
};

}  // namespace kogan

#endif  // SEQUENCE_LIB_TEST_HPP
