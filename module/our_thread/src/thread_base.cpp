/* -*- mode: C++ -*-
 *
 *  Copyright (C) 2019 Feng DING, Hirain
 *
 *  License: Modified BSD Software License Agreement
 *
 */

#include "thread_base.h"

namespace itd {

void* ThreadBase::func(void* arg) {
  ThreadBase *ptr = (ThreadBase*) arg;
  ptr->Run();
  return NULL;
}


int ThreadBase::Start() {
  if (pthread_create(&pid_, NULL, func, (void*)this) != 0) {
    return ThreadStartFailed;
  }
  isAlive_ = true;
  return ThreadNoError;
}

int ThreadBase::Join() {
  if (pthread_join(pid_, NULL) != 0) {
    return ThreadJoinFailed;
  }
  return ThreadNoError;
}

int ThreadBase::Detach() {
  if (pthread_detach(pid_) != 0) {
    return ThreadDetachFailed;
  }
  return ThreadNoError;
}

int ThreadBase::Stop() {
  isAlive_ = false;
  return ThreadNoError;
}

pthread_t ThreadBase::getPid() {
  return pid_;
}

void ThreadBase::setPName(std::string pName) {
  pName_ = pName;
}

std::string ThreadBase::getPName() {
  return pName_;
}


bool ThreadBase::isAlive() {
  return isAlive_;
}


ThreadBase::~ThreadBase() {
  if (isAlive_) {
    pthread_kill(pid_, 0);
  }
}

} // namespace itd
