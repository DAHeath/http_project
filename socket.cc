#include "socket.h"

#include <string>
#include <unistd.h>
#include "my_lib.h"

const unsigned short MAX_MESSAGE_SIZE = 255;

void TcpSocket::connectSocket() {
  connect(sock, (struct sockaddr*)&addr, sizeof(addr));
};

void TcpSocket::sendMessage(const char *message) {
  send(sock, message, strlen(message), 0);
};

std::string TcpSocket::receiveMessage() {
  std::string message = "";
  char buffer[MAX_MESSAGE_SIZE+1];
  int length = 1;
  if((length = recv(sock, buffer, MAX_MESSAGE_SIZE, 0)) < 0)
    exitWithMessage("recv() failed");
  while (length > 0) {
    buffer[length] = '\0';
    message += buffer;
    if((length = recv(sock, buffer, MAX_MESSAGE_SIZE, 0)) < 0)
      exitWithMessage("recv() failed");
  }
  return message;
};

void TcpSocket::closeSocket() {
  close(sock);
};
