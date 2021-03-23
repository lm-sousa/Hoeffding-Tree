#include "Tester.hpp"
#include <iostream>
#include <ostream>
#include <string>

Tester::Test::Test(std::string name, std::function<bool()> tfn)
    : name(name), tfn(tfn) {}

bool Tester::Test::runTest(bool logSuccess) {
    this->successfull = (this->tfn)();

    if (!this->successfull) {
        std::cout << "FAILED --> Test '" << this->name << "'" << std::endl;
    } else if (logSuccess) {
        std::cout << "passed --> Test '" << this->name << "'" << std::endl;
    }

    return this->successfull;
}

Tester::~Tester() {
    for (auto test : this->_tests) {
        delete test;
    }
}

void Tester::addTest(std::string name, std::function<bool()> tfn) {
    Tester::Test *t = new Tester::Test(name, tfn);
    this->_tests.push_back(&*t);
    _testN++;
}

void Tester::runTestSuite(bool logSuccess) {
    for (auto t = this->_tests.begin(); t != this->_tests.end(); t++) {
        Test &currentTest = **t;
        this->_successCount += currentTest.runTest(logSuccess);
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