#ifndef SOCKET_H
#define SOCKET_H

#include <arpa/inet.h>
#include <string.h>
#include <string>

class TcpSocket {
  public:
    TcpSocket(const sockaddr_in address) : 
      addr(address),
      sock(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) { };

    /**
     * Establish a connection with the destination address over TCP.
     */
    void connectSocket();

    /**
     * Send a message over the TCP connection. A connection must first be
     * established by calling connectSocket().
     */
    void sendMessage(const char *message);

    /**
     * Receives incoming message from destination address. Will block until a 
     * message has been received. A connection must first be established by 
     * calling connectSocket().
     */
    std::string receiveMessage();

    /**
     * Closes the connection. Should be called after all transactions with 
     * sendMessage() and receiveMessage() are conducted.
     */
    void closeSocket();
  private:
    const sockaddr_in addr;
    const int sock;
};

#endif
