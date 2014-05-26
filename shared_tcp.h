#ifndef SHARED_TCP_H
#define SHARED_TCP_H

const unsigned short MAX_MESSAGE_SIZE = 255;

typedef struct sockaddr_in SocketAddress;

class Socket {
  public:
    Socket(const int socket, const SocketAddress address) :
      _socket(socket), _address(address) {
    }

    void makeConnection() {
      connect(_socket, (struct sockaddr*)&_address, sizeof(_address));
    };

    void sendMessage(const char* message) {
      send(_socket, message, strlen(message), 0);
    };

    void endConnection() {
      close(_socket);
    };

    const Socket acceptConnection() {
      SocketAddress connectionAddress;
      unsigned int addressLength = sizeof(connectionAddress);
      int connectionSocket = accept(
          _socket, 
          (struct sockaddr*)&connectionAddress,
          &addressLength
      );
      return Socket(connectionSocket, connectionAddress);
    }

    void printIncomingMessage() {
      char buffer[MAX_MESSAGE_SIZE+1];
      int length = recv(_socket, buffer, MAX_MESSAGE_SIZE, 0);
      while (length > 0) {
        buffer[length] = '\0';
        printf("%s", buffer);
        length = recv(_socket, buffer, MAX_MESSAGE_SIZE, 0);
      }
    }
  private:
    const int _socket;
    const SocketAddress _address;
};

#endif
