/*
 * network.c
 *
 *  Created on: Mar 30, 2012
 *      Author: gnu_d
 */

#include "stdio.h"
#include "network.h"
#include "server.h"

int
main(int argc, char **argv)
{
  unsigned int port = 8080;

  int sock = CreateTCPServerSocket(port);
  AcceptTCPConnection(sock);
  printf("Using socket: %d\n", sock);
  return 0;
}
