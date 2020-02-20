/* -*- mode: C++ -*-
 *
 *  Copyright (C) 2019 Feng DING, Hirain
 *
 *  License: Modified BSD Software License Agreement
 *
 */

#ifndef _THREAD_BASE_H_
#define _THREAD_BASE_H_

#include <pthread.h>
#include <signal.h>
#include <string>

namespace itd {
class ThreadBase {
  enum ThreadStat {
    ThreadStartFailed = -3,
    ThreadJoinFailed,
    ThreadDetachFailed,
    ThreadNoError
  };
 private:
  static void* func(void* arg);
  pthread_t pid_;
  bool isAlive_;
  std::string pName_;

 public:
  int Start();
  int Join();
  int Detach();
  int Stop();

  pthread_t getPid();
  void setPName(std::string pName);
  std::string getPName();
  bool isAlive();

  virtual void Run() = 0;
  virtual ~ThreadBase();
};
} // namespace itd

#endif // _THREAD_BASE_H_
