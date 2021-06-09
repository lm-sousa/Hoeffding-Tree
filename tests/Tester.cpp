#include "Tester.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <tuple>

Tester::Test::Test(std::string name,
                   std::function<std::pair<bool, std::string>()> tfn)
    : name(name), tfn(tfn) {}

bool Tester::Test::runTest(bool logSuccess, bool verbose) {
    std::tie(this->successfull, this->executionLog) = (this->tfn)();

    if (!this->successfull) {
        std::cout << setColour(ERROR) << "FAILED" << resetColour()
                  << " --> Test '" << this->name << "'" << std::endl;
        std::cout << "\t" << this->executionLog << std::endl;
    } else if (logSuccess) {
        std::cout << setColour(SUCCESS) << "Passed" << resetColour()
                  << " --> Test '" << this->name << "'" << std::endl;
        if (verbose) {
            std::cout << "\t" << this->executionLog << std::endl;
        }
    }

    return this->successfull;
}

Tester::~Tester() {
    for (auto test : this->_tests) {
        delete test;
    }
}

void Tester::addTest(std::string name,
                     std::function<std::pair<bool, std::string>()> tfn) {
    Tester::Test *t = new Tester::Test(name, tfn);
    this->_tests.push_back(&*t);
    _testN++;
}

uint Tester::runTestSuite(bool logSuccess, bool verbose) {
    for (auto t = this->_tests.begin(); t != this->_tests.end(); t++) {
        Test &currentTest = **t;
        this->_successCount += currentTest.runTest(logSuccess, verbose);
    }

    uint errorCount = this->_testN - this->_successCount;

    std::cout << std::endl;
    std::cout << "############################################################"
              << std::endl;
    std::cout << "Test Results:" << std::endl;

    if (errorCount) {
        std::cout << setColour(WARNING) << "\t" << errorCount << " error(s) "
                  << resetColour() << "detected." << std::endl;
    } else {
        std::cout << setColour(SUCCESS) << "\tAll tests were sucessfull."
                  << resetColour() << std::endl;
    }

    std::cout << "############################################################"
              << std::endl;

    return errorCount;
}