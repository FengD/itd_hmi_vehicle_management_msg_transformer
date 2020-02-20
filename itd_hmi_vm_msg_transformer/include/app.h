// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description:


#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <string>
#include <yaml-cpp/yaml.h>

namespace itd {
namespace communication {
  class UdpSender;
  class UdpReceiver;
  class TcpClient;
}  // namespace communication
}  // namespace itd

class ThreadUdpReceive;
class ThreadTcpReceive;


class Application {
 public:
  Application(const std::string &configFilePath);
  ~Application();

  void Init();
  void Start();
  void Stop();

 private:
  YAML::Node config_;
  itd::communication::UdpSender *udpSender;
  itd::communication::UdpReceiver *udpReceiver;
  itd::communication::TcpClient *tcpClient;
  ThreadUdpReceive *threadUdpReceive;
  ThreadTcpReceive *threadTcpReceive;
};

#endif // _APPLICATION_H_
