// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description: udp sender

#ifndef _UDP_SENDER_H_
#define _UDP_SENDER_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <string>

namespace itd {
namespace communication {

class UdpSender {
 public:
  UdpSender();
  ~UdpSender();
  int Send(const void *msg, const int& len);
  int Setup(const std::string &ip, const int &port);

 private:
  std::string target_ip_;
  int port_;
  int socket_, ret_;
  struct sockaddr_in client_address_, remote_server_address_;
  struct hostent *host_;
  int broadcast_;
  int Init();
};

}  // namespace communication
}  // namespace itd

#endif // _UDP_SENDER_H_
