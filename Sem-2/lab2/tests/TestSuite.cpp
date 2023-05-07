//
// Created by Gregory Kogan on 06.05.2023.
//

#include "TestSuite.h"


namespace kogan {

    TestSuite::TestSuite(std::string name) {
        this->name = std::move(name);
    }

    size_t TestSuite::add_test(const Test &test) {
        tests.push_back(test);
        return tests.size();
    }

    bool TestSuite::run() {
        log_blue(name);
        std::cout << " test suite is running" << std::endl;

        bool all_tests_passed = true;
        for (const auto& test : tests) {
            if (!test.run())
                all_tests_passed = false;
        }

        if (all_tests_passed)
            log_green("All tests passed!\n\n");
        else
            log_red("Some tests failed\n\n");

        return all_tests_passed;
    }

} // kogan
