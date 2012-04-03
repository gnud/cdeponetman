/*
 * server.c
 *
 *  Created on: Mar 30, 2012
 *      Author: gnu_d
 */

#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <string.h>     /* for memset() */
#include <pthread.h>        /* for POSIX threads */

#define MAXPENDING 5    /* Maximum outstanding connection requests */

void
DieWithError(char *errorMessage)
{
  printf("The server is dead, msg: %s", (char*) errorMessage);
}

int
CreateTCPServerSocket(unsigned short port)
{
  int sock; /* socket to create */
  struct sockaddr_in echoServAddr; /* Local address */

  /* Create socket for incoming connections */
  if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    DieWithError("socket() failed");

  /* Construct local address structure */
  memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
  echoServAddr.sin_family = AF_INET; /* Internet address family */
  echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
  echoServAddr.sin_port = htons(port); /* Local port */

  /* Bind to the local address */
  if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
    DieWithError("bind() failed");

  /* Mark the socket so it will listen for incoming connections */
  if (listen(sock, MAXPENDING) < 0)
    DieWithError("listen() failed");

  return sock;
}
/* Structure of arguments to pass to client thread */
struct ThreadArgs
{
  int clntSock; /* Socket descriptor for client */
  char *host;
};
void *
ThreadMain(void *threadArgs)
{
  int clntSock; /* Socket descriptor for client connection */

  /* Guarantees that thread resources are deallocated upon return */
  // pthread_detach(pthread_self());

  /* Extract socket file descriptor from argument */
  clntSock = ((struct ThreadArgs *) threadArgs) -> clntSock;
  //free(threadArgs);              /* Deallocate memory for argument */

  HandleTCPClient(clntSock);

  return (NULL);
}

/*
 * Return client id
 */
int
AcceptTCPConnection(int servSock)
{
  int clntSock; /* Socket descriptor for client */
  struct sockaddr_in echoClntAddr; /* Client address */
  unsigned int clntLen; /* Length of client address data structure */
  pthread_t threadID; /* Thread ID from pthread_create() */
  struct ThreadArgs *threadArgs; /* Pointer to argument structure for thread */
  /* Set the size of the in-out parameter */
  clntLen = sizeof(echoClntAddr);

  printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
  int times = 0;

  // Wait forever
  for (;;)
    {
      /* Wait for a client to connect */
      if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,
          &clntLen)) < 0)
        DieWithError("accept() failed");
      times++;

      /* clntSock is connected to a client! */
      printf("looped %d times\n", times);

      /* Create separate memory for client argument */
      if ((threadArgs = (struct ThreadArgs *) malloc(sizeof(struct ThreadArgs)))
          == NULL)
        DieWithError("malloc() failed");
      threadArgs -> clntSock = clntSock;

      /* Create client thread */
      if (pthread_create(&threadID, NULL, ThreadMain, (void *) threadArgs) != 0)
        DieWithError("pthread_create() failed");

      // Thread less
      //      printf("with thread %ld\n", (long int) threadID);
      //HandleTCPClient(clntSock);
    }

  return clntSock;
}
#define RCVBUFSIZE 1000   /* Size of receive buffer */

void
HandleTCPClient(int clntSocket)
{
  char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */
  int recvMsgSize; /* Size of received message */

  /* Receive message from client */
  if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    DieWithError("recv() failed");

  /* Send received string and receive again until end of transmission */
  while (recvMsgSize > 0) /* zero indicates end of transmission */
    {
      char *newMsg;
      int close_line = 0;
      switch (atoi(echoBuffer))
        {
      case 1:
        newMsg = "cpu: you asked me one\n";
        if (send(clntSocket, newMsg, strlen(newMsg), 0))
          DieWithError("case 1 sending failed");
        break;
      case 2:

        break;
      case 3:
        newMsg = "cpu: die motherfucker !\n";
        if (send(clntSocket, newMsg, strlen(newMsg), 0))
          DieWithError("case 1 sending failed");
        close_line = 1;
        break;
      default:
        parseCMD(clntSocket, echoBuffer);
        break;
        }
      if (close_line)
        break;
      /* Echo message back to client */
      //      if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
      //        DieWithError("send() failed");

      /* See if there is more data to receive */
      if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
    }

  close(clntSocket); /* Close client socket */
}
