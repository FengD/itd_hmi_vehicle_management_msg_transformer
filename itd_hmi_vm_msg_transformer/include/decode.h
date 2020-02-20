// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description:

#ifndef _DECODE_H_
#define _DECODE_H_
#include "msg.pb.h"

double decodeAduData(const uint8_t *data, const int &index) ;

void createAduFromMsg(const uint8_t *data, const std::string &carName, hirain::itd::hmi::demo::api::FromAduMessage *fAduMsg);

double gpsY2Lat(const double &x, const double &h, const double &ref_lat, const double &ref_long);

double gpsX2Long(const double &y, const double &h, const double &ref_lat);

void encodeAduData(const int &data, const int &index, uint8_t *out);

void createAduToMsg(const int& pathId, const int& advSwitch, uint8_t *out);

#endif  // _DECODE_H_
