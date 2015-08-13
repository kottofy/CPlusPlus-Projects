/*
 *  Author: Kang Li
 *  Date: July 8, 2010
 *  Program Name: linklist
 */


struct node {
    int n;
    struct node * next;
};

struct node * reverseL(struct node * h);
struct node * appendL(struct node *h, int i);
struct node * deleteL(struct node *h, int i);


