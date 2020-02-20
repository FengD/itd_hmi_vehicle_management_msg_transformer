// Copyright (C) 2020 Hirain Technologies
// License: Modified BSD Software License Agreement
// Author: Feng DING
// Description:

#include <iostream>
#include <signal.h>
#include "app.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("no config file given\n");
    return -1;
  }

  Application app(argv[1]);
  app.Init();
  app.Start();
  app.Stop();
	return 0;
}
