/*
 *  Author: Kristin Ottofy
 *  Date: July 11, 2010
 *  Program Name: linklist
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "linklist.h"

using namespace std;

struct node * reverseL(struct node *h)
{
	if (h == NULL)	//if the list in empty, there is nothing to reverse so retun NULL
		return NULL;
	
	//if the list contains only one value,
	//there is nothing to reverse to return the one value
	if (h->next == NULL)	 
		return h;
	
	//printf("This function takes a list as a parameter\n");
	//printf("It returns a list that has all the node in reverse order\n");
	
	struct node * newlist = h;	//needs to be reversed list
	struct node * reverselist = NULL;	//a new list to hold the list in reverse
	struct node * next;			//pointer to keep track of the next node
	struct node * current = h;	//pointer to keep track of the current node in list h
	
	//move through list h until it reaches NULL (the end)
	while (current != NULL)
	{
		// the next value is the end, quit looping
		if (current->next == NULL)
		{
			//point current to reverselist
			current->next = reverselist;
			//set reverselist to the current node
			reverselist = current;
			break;
		}
		next = current->next;	//move the pointer next to the next node
		current->next = reverselist;	//point current to reverselist
		reverselist = current;	//set reverselist to the current node
		current = next;			//set the current node to node next
	}
	
	//set newlist to the reversed list and return newlist to finish the function
	newlist = reverselist;
	return newlist;
}

struct node * appendL(struct node *h, int i)
{
	//if the list is empty, add a node with value of i
	if (h == NULL)
	{
		struct node * temp =(node*)malloc(sizeof(node));	//create new temporary node
		temp->n = i;		//set value of temp to i
		temp->next = NULL;	//set the value that temp points to to NULL
		h = temp;			//add the temporary node to the list
		return h;			//finish the function
	}
	
	//if the list contains only one value, add a new node with value of i at the next position
	if (h->next == NULL)
	{
		struct node * temp =(node*)malloc(sizeof(node));	//create new temporary node
		temp->n = i;		//set value of temp to i
		temp->next = NULL;	//set the value that temp points to to NULL
		h->next = temp;		//add the temporary node to the list at the next position
		return h;			//finish the function
	}
	
  //printf("This function creates a new node element to hold the value i\n");
  //printf("Then appends the new node at the tail end of the list\n");

  struct node * newlist = h;		//list to be returned
  struct node * tempnewlist = h;	//temporary newlist to help point through newlist

	//creating a new node to point to head of newlist
	struct node * head =(node*)malloc(sizeof(node));
	
	//setting the node to point to the head of newlist as long as it's not equal to 0
	do
	{
		head = tempnewlist->next;
	}
	while (head->n == 0);
	
  //creating new temporary node to add to newlist
  struct node * temp =(node*)malloc(sizeof(node));

  //searching for end of the newlist
  while(tempnewlist->next!=NULL)	
      tempnewlist = tempnewlist->next;	

  temp->n = i;         //setting temp to value of i
  temp->next = NULL;   //setting temp's sucessor to null
  tempnewlist->next = temp1;	//setting the last value of newlist to point to temp1 which contains i

  //setting the pointer in newlist to the node set to the head
  newlist->next = head;

  //finish the function
  return newlist;
}

struct node * deleteL(struct node *h, int i)
{
	//return NULL is the list is empty
	if (h == NULL)
		return NULL;
	
	//printf("Find all the nodes in a list that has value i. Remove them from the list.\n");
	//printf("The returned list should have all other elements except those with value i.\n");
	//printf("If no nodes left after the delete action, the function should return NULL\n");
	
	struct node * newlist = h;	
	struct node * previous;		//pointer to keep track of the previous node
	struct node * current = newlist;	//pointer to keep track of the current node in newlist
	bool ifDeleted = false;		//helps keep track of where to assign previous
	
	//loop through list until the end
	while(current != NULL)
	{
		//if current node value is equal to i
		if (current->n == i)
		{
			ifDeleted = true;		//a node is being deleted
			if(current == newlist)	// if the current value is at the head, delete the head
			{
				newlist = current->next;
				free(current);
			}
			else	//link the previous node to the node after the current node
				previous->next = current->next;
		}
		//set the previous node to the current node unless a node was deleted
		//in which case previous does not need to change
		if (ifDeleted == false)
			previous = current;
		current = current->next;	//move to the next node in the list
		ifDeleted = false;	//reset ifDeleted
	}
	
	//if all values of newlist were equal to i and therefore deleted, return NULL
	if (newlist == NULL)
		return NULL;
	else	//return the newlist without the nodes with values of i
		return newlist;
}
