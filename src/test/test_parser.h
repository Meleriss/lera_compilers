#ifndef TEST_PARSER_H
#define TEST_PARSER_H

#include <cxxtest/ErrorPrinter.h>

class test_parser : public CxxTest::TestSuite
{
public:
  void test_1();
  void test_if();
  void test_while();
  void test_error_semi();
  void test_callfunc();
  void test_error_callfunc();
};

#endif