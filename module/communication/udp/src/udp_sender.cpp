// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description: udp sender

#include "udp_sender.h"
#include <string>
#include "error_code.h"

namespace itd {
namespace communication {

UdpSender::UdpSender() :  broadcast_(1) { }

UdpSender::~UdpSender() {}

int UdpSender::Setup(const std::string &ip, const int &port) {
  target_ip_ = ip;
  port_ = port;
  return Init();
}

int UdpSender::Init() {
  host_ = gethostbyname(target_ip_.c_str());
  if (host_ == NULL) {
    perror("unknown host\n");
    return UNKOWN_HOST_ERROR;
  }

  inet_ntoa(*(struct in_addr *)host_->h_addr_list[0]);

  remote_server_address_.sin_family = host_->h_addrtype;
  memcpy((char *)&remote_server_address_.sin_addr.s_addr,
	       host_->h_addr_list[0], host_->h_length);
  remote_server_address_.sin_port = htons(port_);

  // socket creation
  socket_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_ < 0) {
    perror("cannot open socket\n");
    return SOCKET_OPEN_ERROR;
  }
  if (setsockopt(socket_, SOL_SOCKET, SO_BROADCAST, &broadcast_, sizeof broadcast_) == -1) {
    perror("setsockopt (SO_BROADCAST)");
    return SOCKET_SETOPT_ERROR;
  }
  // bind any port
  client_address_.sin_family = AF_INET;
  client_address_.sin_addr.s_addr = htonl(INADDR_ANY);
  client_address_.sin_port = htons(0);

  ret_ = bind(socket_, (struct sockaddr *) &client_address_, sizeof(client_address_));
  if (ret_ < 0) {
    perror("cannot bind port\n");
    return SOCKET_BIND_ERROR;
  }
  return NO_ERROR;
}

int UdpSender::Send(const void *msg, const int& len) {
  ret_ = sendto(socket_, msg, len, 0, (struct sockaddr *) &remote_server_address_, sizeof(remote_server_address_));

  if (ret_ < 0) {
    return MSG_SEND_ERROR;
  }
  return NO_ERROR;
}

}  // namespace communication
}  // namespace itd
