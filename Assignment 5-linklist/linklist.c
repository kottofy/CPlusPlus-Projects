/*
 *  Author: Kang Li
 *  Date: July 8, 2010
 *  Program Name: linklist
 */

/*
Please implement a program that takes a list of number
from the standard input, sorts them, and prints the
output in order based on value
(from lowest to highest values).
*/   

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "linklist.h"

using namespace std;

void foo()
{
  struct node *p;
  p = (struct node *) malloc(sizeof(struct node));

  // doing something unrelated
}


void printNodes(struct node *h)
{
  struct node * p;
  printf("List Start:\n");
  p = h;
  while (p!=NULL) {
    cout << p->n << " ";
    p=p->next;
  }
  printf("\nList End.\n");
}

struct node * sortL(struct node *h)
{
  struct node *p, *q, *r, *s, *newlist;

  newlist=NULL;
  p = h;

  while (p!=NULL) {
                          //do something with current node (pointed by p)
    r=p->next;
    q=newlist;
    if (q==NULL) {        // The newlist is empty. simply take p as the new list.
	  newlist = p;
	  p->next = q;
    }
    else {                // The newlist is not empty. Need to insert p to newlist.

      if (p->n <= q->n) { // value smaller than the value in the newlist head node
	newlist = p;
	p->next = q;
      }
      else {              //need to find a place to insert

	//while((q!=NULL) && (p->n > q->n)) q=q->next;
	while (q!=NULL)
	  if (p->n > q->n) q=q->next;
	  else break;
	                  // all nodes in newlist before q contain values greater than p->n
	s=newlist;
	while(s->next!=q) s=s->next;

	                  // now insert p to newlist
	p->next=q;
	if (s!=NULL) s->next=p;
      }
    }
    p=r;
  }

  return newlist;
}


int main()
{
  struct node *p, *head;

  int i;

  // read data into the link list
  head = NULL;
  cin >> i;
  while (i!=0) {
    p = (struct node *)malloc(sizeof(struct node));
    p->n = i;
    p->next = head;
    head = p;
    cin >> i;
  }

  // print out content in the list

  cout << "before sort\n";
  printNodes(head);

  cin >> i;
  head = appendL(head, i);
  cout << "after 1st append\n";
  printNodes(head);

  head = reverseL(head);
  cout << "after 1st reverse\n";
  printNodes(head);

  cin >> i;
  head = deleteL(head, i);
  cout << "after 1st delete\n";
  printNodes(head);

  head = reverseL(head);
  cout << "after 2nd reverse\n";
  printNodes(head);

  cin >> i;
  head = appendL(head, i);
  cout << "after 2nd append\n";
  printNodes(head);

  cout << "\n";
  head = sortL(head);
  cout << "after sort\n";
  printNodes(head);

  p=head;
  while (p!=NULL) {
    free(head);
    head=p->next;
    p=head;
  }

  return 0;
}
