#include <iostream>       // stdout, stderr
#include <arpa/inet.h>    // sockaddr_in, htons, etc.
#include <unistd.h>       // close
#include <string.h>       // strlen
#include <stdlib.h>       // exit

#include "my_lib.h"       // exitWithMessage
#include "get_request.h"
#include "socket.h"

const unsigned short MAX_MESSAGE_SIZE = 255;

const sockaddr_in buildAddress(GetRequest req) {
  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = req.ipAddress();
  addr.sin_port = htons(req.port());
  return addr;
}

std::string getResponse(GetRequest req, sockaddr_in addr) {
  TcpSocket socket = TcpSocket(addr);
  socket.connectSocket();
  socket.sendMessage(req.formattedRequest());
  std::string response = socket.receiveMessage();
  socket.closeSocket();
  return response;
}

int main(int argc, char **argv) {
  if (argc < 2) exitWithMessage("Usage: http_client URL\n");

  GetRequest req = GetRequest(argv[1]);
  std::cerr << "Server: " << req.server() << ":" << req.port() << "\n" <<
    "File: " << req.file() << "\n" <<
    "Sending:\n" << req.formattedRequest() << "\n";
  sockaddr_in addr = buildAddress(req);
  std::string response = getResponse(req, addr);

  int location = response.find("\r\n\r\n") + 4;
  std::string header = response.substr(0, location);
  std::string body = response.substr(location);
  std::cerr << header;
  std::cout << body;

  return 0;
}
