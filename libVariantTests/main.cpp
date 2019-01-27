// main.cpp : Defines the entry point for the console application.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <gtest/gtest.h>

#include "gtesthelper.h"

int main(int argc, char **argv)
{
  gTestHelper & hlp = gTestHelper::getInstance();
  if (hlp.isProcessorX86())
  {
    if (hlp.isDebugCode())
      ::testing::GTEST_FLAG(output) = "xml:libVariantTests.x86.debug.xml";
    else
      ::testing::GTEST_FLAG(output) = "xml:libVariantTests.x86.release.xml";
  }
  else if (hlp.isProcessorX64())
  {
    if (hlp.isDebugCode())
      ::testing::GTEST_FLAG(output) = "xml:libVariantTests.x64.debug.xml";
    else
      ::testing::GTEST_FLAG(output) = "xml:libVariantTests.x64.release.xml";
  }

  ::testing::GTEST_FLAG(filter) = "*";
  ::testing::InitGoogleTest(&argc, argv);

  int wResult = RUN_ALL_TESTS(); //Find and run all tests
  return wResult; // returns 0 if all the tests are successful, or 1 otherwise
}
