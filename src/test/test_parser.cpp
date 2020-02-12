#include "test_parser.h"
#include "../../include/scanner.h"
#include "../../include/NClassDec.h"

extern int eRow;
extern int eCol;

void test_parser::test_1()
{
  NClassDec *root;
  
  TS_ASSERT_EQUALS(parse("data/test/test1.cs", &root, false), 0);

	delete root;
}

void test_parser::test_if()
{
  NClassDec *root;
  
  TS_ASSERT_EQUALS(parse("data/test/test_if.cs", &root, false), 0);

	delete root;
}

void test_parser::test_while()
{
  NClassDec *root;
  
  TS_ASSERT_EQUALS(parse("data/test/test_while.cs", &root, false), 0);

	delete root;
}

void test_parser::test_error_semi()
{
  NClassDec *root;
  
  TS_ASSERT_EQUALS(parse("data/test/test_error_semi.cs", &root, false), 1);
  TS_ASSERT_EQUALS(eRow, 6);
  TS_ASSERT_EQUALS(eCol, 3);

	delete root;
}

void test_parser::test_callfunc()
{
  NClassDec *root;
  
  TS_ASSERT_EQUALS(parse("data/test/test_callfunc.cs", &root, false), 0);

	delete root;
}

void test_parser::test_error_callfunc()
{
  NClassDec *root;
  
  TS_ASSERT_EQUALS(parse("data/test/test_error_callfunc.cs", &root, false), 1);
  TS_ASSERT_EQUALS(eRow, 5);
  TS_ASSERT_EQUALS(eCol, 12);

	delete root;
}