#include "my_lib.h"

#include <iostream>
#include <stdlib.h>

void exitWithMessage(const char* message) {
  std::cerr << message << "\n";
  exit(1);
};
