/* -*- mode: C++ -*-
 *
 *  Copyright (C) 2019 Feng DING, Hirain
 *
 *  License: Modified BSD Software License Agreement
 *
 */

#ifndef _THREAD_MUTEX_H_
#define _THREAD_MUTEX_H_

#include <pthread.h>

namespace itd {

class ThreadMutex {
 private:
  pthread_mutex_t  mutex_;

 public:
  ThreadMutex();
  ~ThreadMutex();
  void Lock();
  void Unlock();
};

class EnterCriticalSection {
 private:
  ThreadMutex * threadMutex_;
 public:
  EnterCriticalSection(ThreadMutex * threadMutex);
  ~EnterCriticalSection();
};

} // namespace itd

#endif // _THREAD_MUTEX_H_
