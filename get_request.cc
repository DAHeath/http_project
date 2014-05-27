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

const std::string GetRequest::file() const {
  char file[_url.length()];
  int res = sscanf(_url.c_str(), "http://%*[^/]/%s", file);
  if (0 == res) file[0] = '\0';

  assert_message(EOF != res, "Invalid request");
  assert(NULL != file);

  return "/" + std::string(file);
};

const std::string GetRequest::server() const {
  char server[_url.length()];
  const std::string raw = rawServer();
  int res = sscanf(raw.c_str(), "%[^:]:%*u", server);

  assert_message(EOF != res, "Invalid request");
  assert(NULL != server);

  return server;
};

const unsigned short GetRequest::port() const {
  unsigned short port;
  const std::string raw = rawServer();
  int res = sscanf(raw.c_str(), "%*[^:]:%hu", &port);
  if (EOF == res) port = DEFAULT_HTTP_PORT;

  assert(port > 0);

  return port;
};

const unsigned long GetRequest::ipAddress() const {
  const std::string name = server();
  const struct hostent *addr = gethostbyname(name.c_str());

  assert_message(NULL != addr, "gethostbyname() failed.");

  return *((unsigned long *)addr->h_addr_list[0]);
};

const std::string GetRequest::formattedRequest() const {
  return std::string("GET ") + file() + " HTTP/1.1\r\n" +
    "Host: " + server() + "\r\n" + 
    "Connection: keep-alive\r\n" + //TODO this is not the correct type!!
    "\r\n"; 
};

const std::string GetRequest::rawServer() const {
  char server[_url.length()];
  int res = sscanf(_url.c_str(), "http://%[^/]/%*s", server);

  assert(NULL != server);
  return server;
};
