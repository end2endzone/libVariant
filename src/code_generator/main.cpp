// main.cpp : Defines the entry point for the console application.
//

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include "CodeGenerator.h"

int _tmain(int argc, _TCHAR* argv[])
{
  generateDeclarations();
  generateDefinitions();

  return 0;
}

