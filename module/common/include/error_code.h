// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description: error code

#ifndef _ERROR_CODE_H_
#define _ERROR_CODE_H_

enum CommunicationStatus {
  CONNECT_ERROR = -12,
  UNKOWN_HOST_ERROR = -11,
  IP_EMPTY_ERROR = -10,
  SOCKET_SETOPT_ERROR = -9,
  NON_BLOCKERR = -8,
  SOCKET_BIND_ERROR = -7,
  SOCKET_OPEN_ERROR = -6,
  MSG_SEND_ERROR = -5,
  MSG_RECEIVE_ERROR = -4,
  TIMEOUT_ERROR = -3,
  POLL_ERROR = -2,
  DEVICE_ERROR = -1,
  NO_ERROR = 0
};

#endif  // _ERROR_CODE_H_
