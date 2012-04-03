/*
 * cmdMan.c
 *
 *  Created on: Mar 31, 2012
 *      Author: gnu_d
 */

#include <sys/socket.h> /* for send() */
#include <mxml.h>

#define QUIT -1
#define PULL 1
#define PUSH 2
#define MSG 3

typedef struct
{
  char *key;
  int val;
} t_symstruct;

static t_symstruct lookuptable[] =
  {
    { "PULL", PULL },
    { "PUSH", PUSH },
    { "MSG",  MSG  },
    { "QUIT", QUIT } };

#define NKEYS (sizeof(lookuptable)/sizeof(t_symstruct))

int
keyfromstring(char *key)
{
  int i;
  for (i = 0; i < NKEYS; i++)
    {
      t_symstruct *sym = lookuptable + i;
      if (strcasecmp(sym->key, key) == 0)
        return sym->val;
    }
  return 6;
}

void
parseCMD(int *clntSocket, char *buffer)
{
  mxml_node_t *tree;
  printf("The xml was: %s\n", (char *) buffer);
  tree = mxmlLoadString(NULL, buffer, MXML_NO_CALLBACK);

  mxml_node_t *node = mxmlFindElement(tree, tree, "cmd", NULL, NULL,
      MXML_DESCEND);
  mxml_node_t *n_node = mxmlFindElement(node, tree, "name", NULL, NULL,
      MXML_DESCEND);
  mxml_node_t *arg1_node = mxmlFindElement(node, tree, "arg1", NULL, NULL,
      MXML_DESCEND);
  char * cmd = mxmlGetText(n_node, 0);
  char * arg = mxmlGetText(arg1_node, 0);
  printf("The cmd was: %s and has argument: %s\n", cmd, arg);
int key = keyfromstring(cmd);

  switch (key)
    {
  case PULL: /* ... */
    downloadFileCMD();
    break;
  case PUSH: /* ... */
    break;
  case MSG: /* ... */
    break;
  case QUIT: /* ... */
    break;
  default:
    printf("The cmd was %s", (char *)cmd);
    break;
    }

  //char *newMsg = "";
  //send(*clntSocket, newMsg, strlen(newMsg), 0);
}
