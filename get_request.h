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
    GetRequest(const std::string url): _url(url) { };

    /**
     * Returns a string representation of the file specified by this request.
     *
     * For example, 'http://google.com:8080/file' would yield '/file'.
     */
    const std::string file() const;

    /**
     * Returns a string representation of the server specified by this request.
     *
     * For example, 'http://google.com:8080/file' would yield 'google.com'.
     */
    const std::string server() const;

    /**
     * Returns the port specified by the request.
     *
     * For example,'http://google.com:8080/file' would yield '8080'.
     * In the event that no port is specified, it should return the default 
     * value of port 80.
     */
    const unsigned short port() const;

    /**
     * Returns the ip address of the server. A DNS lookup is performed on the
     * server name to get this information.
     */
    const unsigned long ipAddress() const;

    /**
     * Returns a string representation of the get request that is fit for 
     * sending to a server. In this simple example, only the 'host' and 
     * 'connection' header fields will be filled out.
     */
    const std::string formattedRequest() const;
  private:
    const std::string _url;
    const std::string rawServer() const;
};

#endif
