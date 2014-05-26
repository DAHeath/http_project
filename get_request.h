#ifndef GET_REQUEST_H
#define GET_REQUEST_H

#include <string>

/**
 * An encapsulation of an http get request. One should should be constructed 
 * with a string of the request in the form:
 * 'http://[SERVER]:[PORT]/[FILE/OF/INTEREST]'
 * The ':[PORT]' section of the request is optional, an disregarding it will 
 * cause the port yield a default value.
 */
class GetRequest {
  public:
    GetRequest(const char* url): _url(url) { };

    /**
     * Returns a string representation of the file specified by this request.
     * It is the responsibility of the user to delete the returned string.
     */
    const char *file();

    /**
     * Returns a string representation of the server specified by this request.
     * It is the responsibility of the user to delete the returned string.
     */
    const char *server();

    /**
     * Returns the port specified by the request.
     */
    const unsigned short port();

    /**
     * Returns an entity containing the ip address of the server.
     */
    const unsigned long ipAddress();

    /**
     * Returns a string representation of the get request that is fit for 
     * sending to a server. In this simple example, only the 'host' and 
     * 'connection' header fields will be filled out.
     */
    const char *formattedRequest();
  private:
    const char *_url;
    const unsigned int length();
    const char *rawServer();
    char *initCharArray();
    void exitWithBadUrl();
    void exitWithInvalidRequest();
    void exitWithMessage(std::string message);
};

#endif
