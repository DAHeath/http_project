#include "get_request.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <iostream>
#include <string.h>
#include <netdb.h>

#include "my_lib.h"

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

const unsigned long GetRequest::ipAddress() {
  const char *name = server();
  const struct hostent *addr = gethostbyname(name);
  if (NULL == addr) exitWithMessage("gethostbyname() failed.");
  free((char*)name);
  return *((unsigned long *)addr->h_addr_list[0]);
}

const char *GetRequest::formattedRequest() {
  std::string response = 
    std::string("GET /") + file() + " HTTP/1.1\r\n" +
    "Host: " + server() + "\r\n" + 
    "Connection: keep-alive\r\n" + //TODO this is not the correct type!!
    "\r\n"; 
  return response.c_str();
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

void GetRequest::exitWithBadUrl() {
  exitWithMessage((std::string("Failed to parse URL: ") + 
      strerror(errno)).c_str());
};

void GetRequest::exitWithInvalidRequest() {
  exitWithMessage((std::string("Error: ") + 
      _url + " is not a valid request").c_str());
};
