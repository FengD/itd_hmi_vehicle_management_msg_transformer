// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description:

#include "app.h"
#include "udp_receiver.h"
#include "udp_sender.h"
#include "tcp_client.h"
#include "thread_base.h"
#include "macro_define.h"
#include "msg.pb.h"
#include "decode.h"

class ThreadUdpReceive : public itd::ThreadBase {
 private:
  itd::communication::UdpReceiver *udpRec_;
  itd::communication::TcpClient *tcpClient_;
  uint8_t data_[1000];
  std::string out_;
  int outSize_;
  std::string carName_;
  int msgLength_;
  float delta_x, delta_y, height;
  double ref_lat, ref_long;

 public:
  ThreadUdpReceive(itd::communication::UdpReceiver *udpRec,
                   itd::communication::TcpClient *tcpClient)
                   : udpRec_(udpRec), tcpClient_ (tcpClient), carName_(""), msgLength_(0) {
    setPName("udpRec");

  }
  ~ThreadUdpReceive() {}

  void setParam(YAML::Node config) {
    carName_ = config["car_name"].as<std::string>();
    msgLength_ = config["from_adu_message_len"].as<int>();
    delta_x = config["route_reference"]["delta_x"].as<float>();
    delta_y = config["route_reference"]["delta_y"].as<float>();
    height = config["route_reference"]["height"].as<float>();
    ref_lat = config["route_reference"]["latitude"].as<double>();
    ref_long = config["route_reference"]["longtitude"].as<double>();
  }

  void Run() {
      int counter = 0;
      while (1) {
        memset(data_, 0, sizeof(data_));
        int rc = udpRec_->GetPacket(msgLength_, data_);
  		if (rc == 0) {
            counter++;
            if (counter < 20){
                continue;
            } else {
                counter = 0;
            }
            hirain::itd::hmi::demo::api::FromAduMessage *fAduMsg_ = new hirain::itd::hmi::demo::api::FromAduMessage();
            createAduFromMsg(data_, carName_, fAduMsg_);
            fAduMsg_->set_xfusion(gpsX2Long(
                fAduMsg_->xfusion() + delta_x,
                height,
                ref_lat
            ));
            fAduMsg_->set_yfusion(gpsY2Lat(
                fAduMsg_->yfusion() + delta_y,
                height,
                ref_lat,
                ref_long
            ));

            hirain::itd::hmi::demo::api::Message outMsg;
            outMsg.set_type(hirain::itd::hmi::demo::api::Message_MessageType_FromAduMessage);
            outMsg.set_allocated_from(fAduMsg_);

            outSize_ = outMsg.ByteSize();
            void *buffer = malloc(outSize_);
            outMsg.SerializeToArray(buffer, outSize_);
            out_.assign((char *)buffer, outSize_);
            tcpClient_->Send((uint8_t*)out_.c_str(), outSize_);
  		}
    }
  }
};

class ThreadTcpReceive : public itd::ThreadBase {
 private:
  itd::communication::UdpSender *udpSend_;
  itd::communication::TcpClient *tcpClient_;
  char data_[2000];
  uint8_t out_[1500];
 public:
  ThreadTcpReceive(itd::communication::UdpSender *udpSend,
                   itd::communication::TcpClient *tcpClient )
                   : udpSend_(udpSend), tcpClient_ (tcpClient){
    setPName("tcpRec");
  }
  ~ThreadTcpReceive() {}

  void Run() {
    while (1) {
        memset(data_, 0, sizeof(data_));
        memset(out_, 0, sizeof(out_));
      tcpClient_->Receive(sizeof(data_), (uint8_t*)data_);
      hirain::itd::hmi::demo::api::Message inMsg;
      inMsg.ParseFromArray(data_, strlen(data_));
      if (inMsg.has_to()) {
          createAduToMsg(inMsg.to().pathnumori(), inMsg.to().advswitch(), out_);
          udpSend_->Send(out_, sizeof(out_));
      }
    }
  }
};

Application::Application(const std::string &configFilePath) {
  udpSender = new itd::communication::UdpSender();
  udpReceiver = new itd::communication::UdpReceiver();
  tcpClient = new itd::communication::TcpClient();
  config_ = YAML::LoadFile(configFilePath.c_str());
  threadUdpReceive = new ThreadUdpReceive(udpReceiver, tcpClient);
  threadTcpReceive = new ThreadTcpReceive(udpSender, tcpClient);
}

void Application::Init() {
  threadUdpReceive->setParam(config_["car"]);

  udpSender->Setup(config_["udp"]["send"]["ip"].as<std::string>(),
                   config_["udp"]["send"]["port"].as<int>());
  udpReceiver->Setup(config_["udp"]["receive"]["ip"].as<std::string>(),
                     config_["udp"]["receive"]["port"].as<int>(),
                     config_["udp"]["receive"]["multicast_ip"].as<std::string>());
  tcpClient->Setup(config_["tcp"]["client"]["ip"].as<std::string>(),
                   config_["tcp"]["client"]["port"].as<int>());
}

Application::~Application() {
  Stop();
  delete udpSender;
  delete udpReceiver;
  delete tcpClient;
  delete threadUdpReceive;
  delete threadTcpReceive;
}

void Application::Start() {
  threadTcpReceive->Start();
  threadTcpReceive->Detach();
  threadUdpReceive->Start();
  threadUdpReceive->Join();
}

void Application::Stop() {
  tcpClient->Exit();
  threadTcpReceive->Stop();
  threadUdpReceive->Stop();
}
