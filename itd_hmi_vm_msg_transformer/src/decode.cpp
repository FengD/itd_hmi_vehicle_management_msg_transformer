// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description:

#include "decode.h"
#include <math.h>

#define R 6378137.0
#define F 0.003352811
#define E2 0.006694381

double decodeAduData(const uint8_t *data, const int &index) {
  int index4 = 4 * index;
  return (data[index4] + (data[index4 + 1]<<8) + (data[index4 + 2]<<16) + (data[index4 + 3]<<24)) / 10000.0 - 10000.0;
}

void createAduFromMsg(const uint8_t *data, const std::string &carName, hirain::itd::hmi::demo::api::FromAduMessage *fAduMsg) {
  int i = -1;
  fAduMsg->set_carname(carName);
  fAduMsg->set_pathnum(static_cast<int>(decodeAduData(data, ++i)));
  fAduMsg->set_xfusion(decodeAduData(data, ++i));
  fAduMsg->set_yfusion(decodeAduData(data, ++i));
  fAduMsg->set_yawfusion(decodeAduData(data, ++i));
  fAduMsg->set_vehiclespeed(decodeAduData(data, ++i));
  fAduMsg->set_advstatus(decodeAduData(data, ++i));
  fAduMsg->set_advswitchreturn(decodeAduData(data, ++i));
  fAduMsg->set_softreturn(decodeAduData(data, ++i));
  fAduMsg->set_emergencyreturn(decodeAduData(data, ++i));
  fAduMsg->set_locflag(decodeAduData(data, ++i));
  fAduMsg->set_gpsflagpos(decodeAduData(data, ++i));
  fAduMsg->set_actuatorerror(decodeAduData(data, ++i));
  fAduMsg->set_sensorerror(decodeAduData(data, ++i));
  fAduMsg->set_evaim(decodeAduData(data, ++i));
  fAduMsg->set_navinum(decodeAduData(data, ++i));
  fAduMsg->set_cipo(decodeAduData(data, ++i));
}

double gpsY2Lat(const double &x, const double &h, const double &ref_lat, const double &ref_long) {
    double temp = sqrt(1 - E2 * pow(sin(ref_lat * M_PI / 180.0),2));
    double re = R / temp;
    double reh = (re + h) * cos(ref_lat * M_PI / 180.0);
    double LoctnFactorX = reh * M_PI / 180;
    return x / LoctnFactorX + ref_long;
}

double gpsX2Long(const double &y, const double &h, const double &ref_lat) {
    double temp = sqrt(1 - E2 * pow(sin(ref_lat * M_PI / 180.0),2));
    double temp3 = pow(temp,3);
    double rn = R * (1 - E2) / temp3;
    double rnh = rn + h;
    double LoctnFactorY = rnh * M_PI / 180;
    return y / LoctnFactorY + ref_lat;
}

void encodeAduData(const int &data, const int &index, uint8_t *out) {
    int value = data * 1000;
    int index4 = 4 * index;
    out[index4] = (value & 0xff);
    out[index4 + 1] = ((value>>8) & 0xff);
    out[index4 + 2] = ((value>>16) & 0xff);
    out[index4 + 3] = ((value>>24) & 0xff);
}

void createAduToMsg(const int& pathId, const int& advSwitch, uint8_t *out) {
    int i = -1;
    encodeAduData(pathId, ++i, out);
    encodeAduData(advSwitch, ++i, out);
}
