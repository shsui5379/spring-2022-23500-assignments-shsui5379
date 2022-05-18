#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../commons/doctest.h"

#include "Dictionary.h"

TEST_CASE("valid size")
{
   CHECK_NOTHROW(new Dictionary(1));
   CHECK_THROWS(new Dictionary(0), INVALID_SIZE);
}