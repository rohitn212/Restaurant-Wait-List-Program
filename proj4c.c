/*
	Author: Rohit Nambiar
*/

#include "proj4.h"

struct node {
  SegType grpName [LENGTH];
    ElemType grpSize;
    enum {call, wait} status;
    struct node *next;
};

struct list_struct  {
    NODE *front;
    NODE *back;
};

LIST *lst_create () {
  LIST *l = NULL;

  l = malloc(sizeof(LIST));

  l->front = NULL;
  l->back = NULL;
  return l;
}

bool checkListEmpty (LIST *l) {
  
  bool check = false;

  if (l -> front == NULL)
    check = true;

  return check;
}

void addToList (LIST *l, ElemType size, SegType name [], ElemType condition)  {

  NODE *new = NULL;

  new = malloc (sizeof (NODE));

  new -> grpSize = size;

  if (condition == 0)
    new -> status = wait;
  else
    new -> status = call;

  strcpy (new -> grpName, name);

  if (l == NULL || l->back == NULL) {
    new -> next = l -> front;
    l -> front = new;
    l -> back = new;
  }
  
  else  {
    new -> next = NULL;
    l -> back -> next = new;
    l -> back = new;
  }
}

bool doesNameExist (LIST *l, SegType name []) {

  bool check = false;

  NODE *curr = NULL;
  curr = l -> front;

  while (curr != NULL)  {

    if (strcmp (name, curr -> grpName) == 0)  {
      check = true;
      return check;
    }

    curr = curr -> next;
  }
  return check;
}

bool updateStatus (LIST *l, SegType name [])  {

  bool check = false;

  NODE *curr = NULL;
  curr = l -> front;

  while (strcmp (name, curr -> grpName) != 0) {

    if (debugMode == true)  {
      printf ("Debug Info: Group Name - \"%s\"\n", curr -> grpName);
      printf ("Debug Info: Group Size - %d\n", curr -> grpSize);
      printf ("Debug Info: Group Status - ");
      if (curr -> status == call)
        printf ("call-ahead\n");
      else
        printf ("waiting in restaurant\n");
    }

    curr = curr -> next;
  }

  if (curr -> status == wait)
    return check;
  else  {
    curr -> status = wait;
    check = true;
    return check; 
  }
}


SegType *retrieveAndRemove (LIST *l, ElemType size) {

  NODE *curr = NULL;
  curr = l -> front;
  NODE *prev=curr;

  while (curr -> grpSize > size || curr -> status != wait)  {
   
    if (debugMode == true)  {
      printf ("Debug Info: Group Name - \"%s\"\n", curr -> grpName);
      printf ("Debug Info: Group Size - %d\n", curr -> grpSize);
      printf ("Debug Info: Group Status - ");
      if (curr -> status == call)
        printf ("call-ahead\n");
      else
        printf ("waiting in restaurant\n");
    }

    prev = curr;
    curr = curr -> next;
    if (curr==NULL)
      return;
  }

  static SegType temp [LENGTH];

  strcpy (temp, curr -> grpName);

  if (l -> front == l -> back)  {
    free (l -> front);
    l -> front = NULL;
    l -> back = NULL;
  }
  else  {
    if (  curr == l -> front) 
      l -> front = curr -> next;
    else
      prev -> next = curr -> next;
    free(curr);
  }

  return temp;
}

ElemType countGroupsAhead (LIST *l, SegType name [])  {

  ElemType count=0;

  NODE *curr = NULL;
  curr = l -> front;

  while (strcmp (name, curr -> grpName) != 0) {
    curr = curr -> next;
    count++;
  }
  return count;
}

void displayGroupSizeAhead (LIST *l, SegType name []) {

  NODE *curr = NULL;
  curr = l -> front;

  while (strcmp (name, curr -> grpName) != 0) {
    
    printf ("Group Size:%d\n", curr -> grpSize);

    if (debugMode == true)  {
      printf ("Debug Info: Group Name - \"%s\"\n", curr -> grpName);
      printf ("Debug Info: Group Size - %d\n", curr -> grpSize);
      printf ("Debug Info: Group Status - ");
      if (curr -> status == call)
        printf ("call-ahead\n");
      else
        printf ("waiting in restaurant\n");
    }

    curr = curr -> next;
  }
}

ElemType displayListInformation (LIST *l) {

  NODE *curr = NULL;
  curr = l -> front;

  ElemType count=0;

  while (curr != NULL)  {
    
    printf ("Group Name: \"%s\"\n", curr -> grpName);
    
    printf ("Group Size: %d\n", curr -> grpSize);
    
    printf ("Group Status: ");
    if (curr -> status == call)
      printf ("call-ahead\n");
    else
      printf ("waiting in restaurant\n");

    count++;

    curr = curr -> next;
  }

  return count;
}
