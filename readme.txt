使用说明

* 使用以下指令执行

`./<可行性文件> <配置文件>`

* 配置文件说明

car:
  car_name: test (车辆名称，与数据库中的车牌号对应)
  from_adu_message_len: 64 （adu发送的消息长度）
  to_adu_message_len: 1500 （adu接收的消息长度）
  route_reference:
    delta_x: 410 （地图delta_x）
    delta_y: -230（地图delta_y）
    longtitude: 121.9232812 （地图原点long）
    latitude: 30.8657519 （地图原点lat）
    height: 4.45

udp:
  send:
    ip: 192.168.0.98 （adu ip）
    port: 3333       （adu 接收端口）
  receive:
    ip: 192.168.0.98   （adu ip）
    port: 8002   （adu 发送端口）
    multicast_ip: ""  （组播地址，不使用不填）
tcp:
  client:
    ip: 192.168.1.101  （tcp服务地址）
    port: 9998  （tcp服务端口号）
