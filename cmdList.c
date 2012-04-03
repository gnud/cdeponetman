/*
 * cmdList.c
 *
 *  Created on: Mar 31, 2012
 *      Author: gnu_d
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <mxml.h>



void listUserCMD(int *clntSocket){
  FILE *fp;
  mxml_node_t *tree;
  char *newMsg = "";
  send(*clntSocket, newMsg, strlen(newMsg), 0);
}
#define SENDBUFSIZE 2   /* Size of receive buffer */
void downloadFileCMD(int *clntSocket){
  FILE *fp;
  mxml_node_t *tree;
  char *newMsg = "1234567890";
  char echoBuffer[SENDBUFSIZE]; /* Buffer for echo string */
  char *to;




  char *test1   = "abcdefghijabcdefghijabcdefghijk";
  char *verify;

for(int b=0; b<=strlen(newMsg); b+=SENDBUFSIZE){
    verify = strndup(test1+b, SENDBUFSIZE); /* shorter then first strndup !!! */
    fprintf(stderr,">%s<\n",(char*)verify);
}
//
//      char *test1   = "abcdefghijabcdefghijabcdefghijk";
//      char *verify;
//      verify = strndup(test1+5, 5); /* shorter then first strndup !!! */
//
//
//      to=strndup(newMsg, 2);
//      printf("Current buffer: %s\n", to);
//      printf("Current buffer: %s\n", verify);
//
//      //send(*clntSocket, newMsg[b], strlen(newMsg), 0);
//  }
  while (1){
  }
}
