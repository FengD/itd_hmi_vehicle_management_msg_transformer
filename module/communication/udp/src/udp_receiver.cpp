// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description: This file used to define the udp input

#include "udp_receiver.h"
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string>
#include "error_code.h"

namespace itd {
namespace communication {

UdpReceiver::UdpReceiver()
  : source_ip_str_(""),
    multicast_ip_str_(""),
    port_(-1),
    sockfd_(-1) { }

UdpReceiver::~UdpReceiver(void) {
  (void) close(sockfd_);
}

int UdpReceiver::Setup(const std::string source_ip, const int port, const std::string multicast_ip) {
  source_ip_str_ = source_ip;
  port_ = port;
  multicast_ip_str_ = multicast_ip;
  if (source_ip_str_.empty()) {
    perror("empty source ip\n");
    return IP_EMPTY_ERROR;
  }
  inet_aton(source_ip_str_.c_str(), &source_ip_);


  sockfd_ = socket(PF_INET, SOCK_DGRAM, 0);
  if (sockfd_ == -1) {
    // Socket Error
    perror("socket\n");
    return SOCKET_OPEN_ERROR;
  }

  // my address information
  sockaddr_in my_addr;
  // initialize to zeros
  memset(&my_addr, 0, sizeof(my_addr));
  // host byte order
  my_addr.sin_family = AF_INET;
  // port in network byte order
  my_addr.sin_port = htons(port_);
  // automatically fill in my IP
  my_addr.sin_addr.s_addr = INADDR_ANY;
  // used for open multipule udp connnect
  int opt = 1;
  setsockopt( sockfd_, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt) );

  if (bind(sockfd_, (sockaddr *) &my_addr, sizeof(sockaddr)) == -1) {
    // Bind Error
    perror("bind\n");
    return SOCKET_BIND_ERROR;
  }

  if (fcntl(sockfd_, F_SETFL, O_NONBLOCK|FASYNC) < 0) {
    perror("non-block\n");
    return NON_BLOCKERR;
  }

  if (!multicast_ip_str_.empty()) {
    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(multicast_ip_str_.c_str());
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if ( setsockopt(sockfd_, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mreq, sizeof(mreq)) < 0) {
      perror("setsockopt\n");
      return SOCKET_SETOPT_ERROR;
    }
  }
  return NO_ERROR;
}

int UdpReceiver::GetPacket(const int& packet_size, uint8_t *pkt) {
  struct pollfd fds[1];
  fds[0].fd = sockfd_;
  fds[0].events = POLLIN;

  sockaddr_in sender_address;
  socklen_t sender_address_len = sizeof(sender_address);

  while (true) {
    do {
      int retval = poll(fds, 1, POLL_TIMEOUT);
      // poll() error?
      if (retval < 0) {
        if (errno != EINTR)
          perror("poll() error\n");
        return POLL_ERROR;
      }
      // poll() timeout?
      if (retval == 0) {
        printf("poll() timeout\n");
        return TIMEOUT_ERROR;
      }
      // device error?
      if ((fds[0].revents & POLL_ERROR)
          || (fds[0].revents & POLLHUP)
          || (fds[0].revents & POLLNVAL)) {
        perror("poll() reports error\n");
        return DEVICE_ERROR;
      }
    } while ((fds[0].revents & POLLIN) == 0);

    // Receive packets that should now be available from the
    // socket using a blocking read.
    ssize_t nbytes = recvfrom(sockfd_, &pkt[0],
                              packet_size,  0,
                              (sockaddr*) &sender_address,
                              &sender_address_len);

    if (nbytes < 0) {
      if (errno != EWOULDBLOCK) {
        perror("recvfail\n");
        return MSG_RECEIVE_ERROR;
      }
    } else if ((size_t) nbytes == (size_t)packet_size) {
      if (source_ip_str_ != "" && sender_address.sin_addr.s_addr != source_ip_.s_addr)
        continue;
      else
        break; // done
    }
  }
  return NO_ERROR;
}

void UdpReceiver::set_source_ip_str(const std::string& source_ip_str) {
  source_ip_str_ = source_ip_str;
}

void UdpReceiver::set_multicast_ip_str(const std::string& multicast_ip_str) {
  multicast_ip_str_ = multicast_ip_str;
}

void UdpReceiver::set_port(const int& port) {
  port_ = port;
}

}  // namespace communication
}  // namespace itd
