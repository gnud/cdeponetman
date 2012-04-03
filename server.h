/*
 * server.h
 *
 *  Created on: Mar 30, 2012
 *      Author: gnu_d
 */

#ifndef SERVER_H_
#define SERVER_H_

void DieWithError(char *errorMessage);  /* Error handling function */
int CreateTCPServerSocket(unsigned short port);
int AcceptTCPConnection(int servSock);
void *ThreadMain(void *threadArgs);
void *ThreadMain(void *arg);            /* Main program of a thread */
void HandleTCPClient(int clntSocket);

#endif /* SERVER_H_ */
