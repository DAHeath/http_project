#include "get_request.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <iostream>
#include <string.h>

#define DEFAULT_HTTP_PORT 80

const char *GetRequest::file() {
  char *file = initCharArray();
  char dummy[length()];
  int res = sscanf(_url, "http://%[^/]/%s", dummy, file);
  if (EOF == res) exitWithBadUrl();
  else if (res < 1) exitWithInvalidRequest();
  else if (1 == res) file[0] = '\0';
  assert(NULL != file);
  return file;
};

const char *GetRequest::server() {
  unsigned short dummy;
  char *server = initCharArray();
  const char *raw = rawServer();
  int res = sscanf(raw, "%[^:]:%hu", server, &dummy);
  free((char*)raw);
  if (EOF == res) exitWithBadUrl();
  else if (res < 1) exitWithInvalidRequest();
  assert(NULL != server);
  return server;
}

const unsigned short GetRequest::port() {
  unsigned short port;
  char dummy[length()];
  const char *raw = rawServer();
  int res = sscanf(raw, "%[^:]:%hu", dummy, &port);
  free((char*)raw);
  if (EOF == res) exitWithBadUrl();
  else if (1 == res) port = DEFAULT_HTTP_PORT;
  else if (res < 1) exitWithInvalidRequest();
  assert(port > 0);
  return port;
}

const unsigned int GetRequest::length() {
  return strlen(_url)+1;
}

const char *GetRequest::rawServer() {
  char *server = initCharArray();
  char dummy[length()];
  int res = sscanf(_url, "http://%[^/]/%s", server, dummy);
  return server;
};

char *GetRequest::initCharArray() {
  return (char*) malloc(length()*sizeof(char));
};

void GetRequest::exitWithMessage(std::string message) {
  std::cerr << message;
  exit(1);
};

void GetRequest::exitWithBadUrl() {
  exitWithMessage(std::string("Failed to parse URL: ") + 
      strerror(errno) + 
      "\n");
};

void GetRequest::exitWithInvalidRequest() {
  exitWithMessage(std::string("Error: ") + 
      _url + 
      " is not a valid request\n");
};
