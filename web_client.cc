#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


#include "get_request.h"
#include "shared_tcp.h"

void exitWithMessage(const char* message) {
  std::cerr << message << "\n";
  exit(1);
}

int main(int argc, char **argv) {
  if (argc < 2) exitWithMessage("Usage: http_client URL\n");

  GetRequest req = GetRequest(argv[1]);

  std::cerr << "Server: " << req.server() << ":" << req.port() << "\n" <<
    "File: " << req.file() << "\n";

  SocketAddress addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = req.ipAddress();
  addr.sin_port = htons(req.port());
  int sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
  std::cerr << "Sending:\n" << req.formattedRequest() << "\n";
  send(sock, req.formattedRequest(), strlen(req.formattedRequest()), 0);


  char buffer[MAX_MESSAGE_SIZE+1];
  int length = 1;
  if((length = recv(sock, buffer, MAX_MESSAGE_SIZE, 0)) < 0)
    exitWithMessage("recv() failed");
  while (length > 0) {
    buffer[length] = '\0';
    std::cout << buffer;
    if((length = recv(sock, buffer, MAX_MESSAGE_SIZE, 0)) < 0)
      exitWithMessage("recv() failed");
  }
  std::cout << "\n";

  close(sock);

  return 0;
}
