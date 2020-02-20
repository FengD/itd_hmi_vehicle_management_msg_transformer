// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description:

#include "tcp_client.h"
#include "error_code.h"

namespace itd {
namespace communication {


TcpClient::TcpClient() {
	socket_ = -1;
	port_ = 0;
	ip_str_ = "";
}

int TcpClient::Setup(const std::string &ip_str, const int &port) {
  port_ = port;
  ip_str_ = ip_str;

  if(socket_ == -1) {
		socket_ = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_ == -1) {
      return SOCKET_OPEN_ERROR;
    }
  }

  if((signed)inet_addr(ip_str_.c_str()) == -1) {
    struct hostent *he;
    struct in_addr **addr_list;
    if ( (he = gethostbyname( ip_str_.c_str() ) ) == NULL) {
      herror("gethostbyname");
      return UNKOWN_HOST_ERROR;
		}
   	addr_list = (struct in_addr **) he->h_addr_list;
		for(int i = 0; addr_list[i] != NULL; i++) {
      ip_.sin_addr = *addr_list[i];
      break;
    }
	}	else {
    ip_.sin_addr.s_addr = inet_addr( ip_str_.c_str() );
  }
	ip_.sin_family = AF_INET;
	ip_.sin_port = htons( port );
	if (connect(socket_ , (struct sockaddr *)&ip_ , sizeof(ip_)) < 0) {
    perror("connect failed. Error");
    return CONNECT_ERROR;
  }
  return NO_ERROR;
}

int TcpClient::Send(const uint8_t *data, const int &data_len) {
	if(socket_ != -1) {
		if( send(socket_, data, data_len * sizeof(uint8_t), 0) < 0) {
			return MSG_SEND_ERROR;
		}
	}
	return NO_ERROR;
}

int TcpClient::Receive(const int &data_len, uint8_t *data) {
  memset(data, 0, data_len * sizeof(uint8_t));
  if( recv(socket_ , data , data_len, 0) < 0) {
    return MSG_RECEIVE_ERROR;
  }
  return NO_ERROR;
}

void TcpClient::Exit() {
  close( socket_ );
}

}  // namespace communication
}  // namespace itd
