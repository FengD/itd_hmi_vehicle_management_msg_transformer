/* mode: C++ -*-
*
*  Copyright (C) 2019 Feng DING, Hirain
*
*  License: Modified BSD Software License Agreement
*
*/

#ifndef _MACRO_DEFINE_H_
#define _MACRO_DEFINE_H_

// thread start and detach
#define SDT(switch, thread)\
if (switch) {\
  LOGINFO("%s start: %d\n", thread->getPName().c_str(), thread->Start());\
  LOGINFO("deatch: %d\n", thread->getPName().c_str(), thread->Detach());\
}
// thread start and join
#define SJT(switch, thread)\
if (switch) {\
  LOGINFO("%s start: %d\n", thread->getPName().c_str(), thread->Start());\
  LOGINFO("%s join: %d\n", thread->getPName().c_str(), thread->Join());\
}
// thread stop
#define ST(switch, thread)\
if (switch) {\
  LOGINFO("%s start: %d\n", thread->getPName().c_str(), thread->Stop());\
}

#endif // _MACRO_DEFINE_H_
