#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "get_request.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr,
            "Usage: http_client URL\n");
    exit(1);
  }

  GetRequest req = GetRequest(argv[1]);

  fprintf(stderr, "Server: %s:%hu\nFile: /%s\n", 
      req.server(), req.port(), req.file());
  return 0;
}
