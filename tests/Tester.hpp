#ifndef __TESTER_HPP__
#define __TESTER_HPP__

#include <functional>
#include <string>
#include <vector>

#include "../src/BinaryTree.hpp"

class Tester {

  public:
    class Test {
      public:
        Test(std::string name, std::function<bool()> tfn);

        std::string name;
        std::function<bool()> tfn;
        bool successfull = false;

        bool runTest(bool logSuccess);
    };

    ~Tester();
    void addTest(std::string name, std::function<bool()> tfn);
    void runTestSuite(bool logSuccess);

  private:
    std::vector<Test *> _tests;
    uint _testN = 0;
    uint _successCount = 0;

    void _displayResults();
};

#endif