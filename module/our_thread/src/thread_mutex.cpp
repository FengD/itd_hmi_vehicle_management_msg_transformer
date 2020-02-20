/* -*- mode: C++ -*-
 *
 *  Copyright (C) 2019 Feng DING, Hirain
 *
 *  License: Modified BSD Software License Agreement
 *
 */

#include "thread_mutex.h"

namespace itd {

ThreadMutex::ThreadMutex() {
  int r = pthread_mutex_init(&mutex_,0);
  if(r != 0) { }
}

ThreadMutex::~ThreadMutex() {
  int r = pthread_mutex_destroy(&mutex_);
  if(r != 0) { }
}

void ThreadMutex::Lock() {
  int r = pthread_mutex_lock(&mutex_);
  if(r != 0) { }
}

void ThreadMutex::Unlock() {
  int r = pthread_mutex_unlock(&mutex_);
  if(r != 0) { }
}

EnterCriticalSection::EnterCriticalSection(ThreadMutex * threadMutex) {
  threadMutex_ = threadMutex;
  threadMutex_->Lock();
}

EnterCriticalSection::~EnterCriticalSection() {
  threadMutex_->Unlock();
}

} // namespace itd
