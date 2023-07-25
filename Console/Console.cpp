#include <iostream>
#include <winsock2.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

class HttpClient {
public:
    HttpClient(const std::string& host) : m_host(host) {
        WSADATA wsaData;
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != 0) {
            throw std::runtime_error("WSAStartup failed: " + std::to_string(iResult));
        }
        m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (m_socket == INVALID_SOCKET) {
            throw std::runtime_error("socket failed: " + std::to_string(WSAGetLastError()));
        }
        m_server.sin_family = AF_INET;
        m_server.sin_port = htons(80);
        m_server.sin_addr.s_addr = inet_addr(m_host.c_str());
    }

    std::string Get(const std::string& path, const std::string& query) {
        std::string request = "GET " + path + "?" + query + " HTTP/1.1\r\n" +
            "Host: " + m_host + "\r\n" +
            "Connection: close\r\n\r\n";
        if (connect(m_socket, (SOCKADDR*)&m_server, sizeof(m_server)) == SOCKET_ERROR) {
            throw std::runtime_error("connect failed: " + std::to_string(WSAGetLastError()));
        }
        if (send(m_socket, request.c_str(), request.size(), 0) == SOCKET_ERROR) {
            throw std::runtime_error("send failed: " + std::to_string(WSAGetLastError()));
        }
        std::string response;
        char buffer[1024];
        int recvSize;
        do {
            recvSize = recv(m_socket, buffer, sizeof(buffer), 0);
            if (recvSize > 0) {
                response.append(buffer, recvSize);
            }
        } while (recvSize > 0);
        if (closesocket(m_socket) == SOCKET_ERROR) {
            throw std::runtime_error("closesocket failed: " + std::to_string(WSAGetLastError()));
        }
        WSACleanup();
        return response;
    }

private:
    std::string m_host;
    SOCKET m_socket;
    SOCKADDR_IN m_server;
};

int main() {
    HttpClient client("168.168.88.111");
    std::string response = client.Get("/User/GetUserInfo", "username=123");
    std::cout << "Response body: " << response.substr(response.find("\r\n\r\n") + 4);
    return 0;
}
