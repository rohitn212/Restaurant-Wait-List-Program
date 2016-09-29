/*
	Author: Rohit Nambiar
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int ElemType;
typedef char SegType;
typedef enum {false, true} bool;
extern bool debugMode;
#define LENGTH 30

// hidden implementation of list_struct
typedef struct node NODE;

typedef struct list_struct LIST;

extern void clearToEoln ();
extern int getNextNWSChar ();
extern int getPosIn ();
extern char *getName ();
extern void clearToEoln();
extern void printCommands();
extern void doAdd (LIST *l);
extern void doCallAhead (LIST *l);
extern void doWaiting (LIST *l);
extern void doRetrieve (LIST *l);
extern void doList (LIST *l);
extern void doDisplay (LIST *l);
extern LIST *lst_create (); 
extern bool checkListEmpty (LIST *l);
extern void addToList (LIST *l, ElemType size, SegType name [], ElemType condition);
extern bool doesNameExist (LIST *l, SegType name []);
extern bool updateStatus (LIST *l, SegType name []);
extern SegType *retrieveAndRemove (LIST *l, ElemType size);
extern ElemType countGroupsAhead (LIST *l, SegType name []);
extern void displayGroupSizeAhead (LIST *l, SegType name []);
void printArray (SegType array [], ElemType length);
extern ElemType displayListInformation (LIST *l);
