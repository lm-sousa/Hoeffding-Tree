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
        std::cout << "FAILED --> Test '" << this->name << "'" << std::endl;
        if (verbose) {
            std::cout << "\t" << this->executionLog << std::endl;
        }
    } else if (logSuccess) {
        std::cout << "Passed --> Test '" << this->name << "'" << std::endl;
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

void Tester::runTestSuite(bool logSuccess, bool verbose) {
    for (auto t = this->_tests.begin(); t != this->_tests.end(); t++) {
        Test &currentTest = **t;
        this->_successCount += currentTest.runTest(logSuccess, verbose);
    }

    std::cout << std::endl;
    std::cout << "############################################################"
              << std::endl;
    std::cout << "Test Results:" << std::endl;
    std::cout << "\t" << this->_successCount << "/" << this->_testN
              << " tests were sucessfull." << std::endl;
    std::cout << "############################################################"
              << std::endl;
}