#ifndef __TESTER_HPP__
#define __TESTER_HPP__

#include <functional>
#include <string>
#include <vector>

#include "../src/BinaryTree.hpp"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

/* Add more options here */
#define SUCCESS ANSI_COLOR_GREEN
#define ERROR ANSI_COLOR_RED
#define WARNING ANSI_COLOR_YELLOW

#define setColour(colour) colour
#define resetColour() ANSI_COLOR_RESET

class Tester {

  public:
    class Test {
      public:
        Test(std::string name,
             std::function<std::pair<bool, std::string>()> tfn);

        std::string name;
        std::function<std::pair<bool, std::string>()> tfn;
        bool successfull = false;
        std::string executionLog;

        bool runTest(bool logSuccess, bool verbose);
    };

    ~Tester();
    void addTest(std::string name,
                 std::function<std::pair<bool, std::string>()> tfn);
    uint runTestSuite(bool logSuccess, bool verbose);

  private:
    std::vector<Test *> _tests;
    uint _testN = 0;
    uint _successCount = 0;

    void _displayResults();
};

#endif