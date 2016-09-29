/*
  Author: Rohit Nambiar
*/

#include "proj4.h"

void doAdd (LIST *l)
{
  /* get group size from input */
  int size = getPosInt();
  if (size < 1)
  {
    printf ("Error: Add command requires an integer value of at least 1\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  /* get group name from input */
  char *name = getName();
  if (NULL == name)
  {
    printf ("Error: Add command requires a name to be given\n");
    printf ("Add command is of form: a <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  bool check;

  check = doesNameExist (l, name);

  if (check == true)  {
    printf("Error: \"%s\" already exists in the list\n", name);
    return;
  }

  printf ("Adding group \"%s\" of size %d\n", name, size);

  addToList (l, size, name, 0);
}


void doCallAhead (LIST *l)
{
  /* get group size from input */
  int size = getPosInt();
  if (size < 1)
  {
    printf ("Error: Call-ahead command requires an integer value of at least 1\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  /* get group name from input */
  char *name = getName();
  if (NULL == name)
  {
    printf ("Error: Call-ahead command requires a name to be given\n");
    printf ("Call-ahead command is of form: c <size> <name>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    printf ("         <name> is the name of the group making the reservation\n");
    return;
  }

  bool check;

  check = doesNameExist (l, name);

  if (check == true)  {
    printf("Error: \"%s\" already exists in the list\n", name);
    return;
  }

  printf ("Adding group \"%s\" of size %d\n", name, size);

  addToList (l, size, name, 1);

}

void doWaiting (LIST *l)
{
  /* get group name from input */
  char *name = getName();
  if (NULL == name)
  {
    printf ("Error: Waiting command requires a name to be given\n");
    printf ("Waiting command is of form: w <name>\n");
    printf ("  where: <name> is the name of the group that is now waiting\n");
    return;
  }

  bool check;

  check = checkListEmpty (l);

  if (check == true) {
    printf ("Error: list is empty\n");
    return;
  }

  check = doesNameExist (l, name);

  if (check == false)  {
    printf("Error: \"%s\" does not exist in the list\n", name);
    return;
  }

  check = updateStatus (l, name);

  if (check == false) {
    printf("Error: Call-ahead group \"%s\" is already in the restaurant\n", name);
    return;
  }

  printf ("Call-ahead group \"%s\" is now in the restaurant\n", name);
}

void doRetrieve (LIST *l)
{
  /* get table size from input */
  int size = getPosInt();
  if (size < 1)
  {
    printf ("Error: Retrieve command requires an integer value of at least 1\n");
    printf ("Retrieve command is of form: r <size>\n");
    printf ("  where: <size> is the size of the group making the reservation\n");
    return;
  }
  clearToEoln();

  bool check;

  check = checkListEmpty (l);

  if (check == true) {
    printf ("Error: list is empty\n");
    return;
  }

  char *name = retrieveAndRemove (l, size);

  if (name == NULL) {
    printf ("Error: No groups on the wait list can be seated at a table of size %d\n", size);
    return;
  }

  printf ("The group \"%s\" was seated at a table\n", name);
}

void doList (LIST *l)
{
  /* get group name from input */
  char *name = getName();
  if (NULL == name)
  {
    printf ("Error: List command requires a name to be given\n");
    printf ("List command is of form: l <name>\n");
    printf ("  where: <name> is the name of the group to inquire about\n");
    return;
  }

  bool check;

  check = checkListEmpty (l);

  if (check == true) {
    printf ("Error: list is empty\n");
    return;
  }

  check = doesNameExist (l, name);

  if (check == false)  {
    printf("Error: \"%s\" does not exist in the list\n", name);
    return;
  }

  ElemType count;

  printf ("Group \"%s\" is behind the following groups\n", name);

  displayGroupSizeAhead (l, name);

  count = countGroupsAhead (l, name);

  printf("There are %d groups ahead of group \"%s\"\n", count, name);
}
 
void doDisplay (LIST *l)
{
  clearToEoln();
  printf ("Display information about all groups\n");

  ElemType count;

  count = displayListInformation (l);

  printf("There are a total of %d groups in the wait list\n", count);
}
