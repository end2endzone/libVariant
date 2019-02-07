// main.cpp : Defines the entry point for the console application.
//

#include <stdio.h>

#include "CodeGenerator.h"

int main(int argc, char* argv[])
{
  generateDeclarations();
  generateDefinitions();

  return 0;
}

