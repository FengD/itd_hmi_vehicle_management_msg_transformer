// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description: This file used to define the udp input

#ifndef _UDP_RECEIVER_H_
#define _UDP_RECEIVER_H_

#include <unistd.h>
#include <string>
#include <netinet/in.h>

namespace itd {
namespace communication {

class UdpReceiver {
 public:
  UdpReceiver();
  ~UdpReceiver();
  int Setup(const std::string source_ip, const int port, const std::string multicast_ip = "");
  int GetPacket(const int& packet_size, uint8_t *pkt);
  void set_source_ip_str(const std::string& source_ip_str);
  void set_multicast_ip_str(const std::string& multicast_ip_str);
  void set_port(const int& port);
 private:
  std::string source_ip_str_;
  std::string multicast_ip_str_;
  int port_;
  int sockfd_;
  in_addr source_ip_;
  static const int POLL_TIMEOUT = 1000;
};

}  // namespace communication
}  // namespace itd

#endif // _UDP_RECEIVER_H_
