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

const char *GetRequest::file() const {
  char *file = initCharArray();
  int res = sscanf(_url, "http://%*[^/]/%s", file);
  if (0 == res) file[0] = '\0';

  assert_message(EOF != res, "Invalid request");
  assert(NULL != file);

  return file;
};

const char *GetRequest::server() const {
  char *server = initCharArray();
  const char *raw = rawServer();
  int res = sscanf(raw, "%[^:]:%*u", server);
  free((char*)raw);

  assert_message(EOF != res, "Invalid request");
  assert(NULL != server);

  return server;
};

const unsigned short GetRequest::port() const {
  unsigned short port;
  const char *raw = rawServer();
  int res = sscanf(raw, "%*[^:]:%hu", &port);
  if (EOF == res) port = DEFAULT_HTTP_PORT;
  free((char*)raw);

  assert(port > 0);

  return port;
};

const unsigned long GetRequest::ipAddress() const {
  const char *name = server();
  const struct hostent *addr = gethostbyname(name);

  assert_message(NULL != addr, "gethostbyname() failed.");

  free((char*)name);
  return *((unsigned long *)addr->h_addr_list[0]);
};

const char *GetRequest::formattedRequest() const {
  std::string response = 
    std::string("GET /") + file() + " HTTP/1.1\r\n" +
    "Host: " + server() + "\r\n" + 
    "Connection: keep-alive\r\n" + //TODO this is not the correct type!!
    "\r\n"; 
  return response.c_str();
};

const unsigned int GetRequest::length() const {
  return strlen(_url)+1;
};

const char *GetRequest::rawServer() const {
  char *server = initCharArray();
  int res = sscanf(_url, "http://%[^/]/%*s", server);

  assert(NULL != server);
  return server;
};

char *GetRequest::initCharArray() const {
  return new char[length()];
};

