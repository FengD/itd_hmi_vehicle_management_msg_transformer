// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description:

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netdb.h>
#include <vector>

namespace itd {
namespace communication {

class TcpClient {
  private:
   int socket_;
   std::string ip_str_;
   int port_;
   struct sockaddr_in ip_;

  public:
   TcpClient();
   int Setup(const std::string &ip_str, const int &port);
   int Send(const uint8_t *data, const int &data_len);
   int Receive(const int &data_len, uint8_t *data);
   void Exit();
};

}  // namespace communication
}  // namespace itd

#endif  // TCP_CLIENT_H
