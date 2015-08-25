/* 
 * File:   main.cpp
 * Author: Kristin Ottofy
 *
 * Created on March 22, 2011, 12:38 PM
 */

#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int height = 0; //height of tree
int numberOfWords = 0; //total number of words in tree
int numWords4Chars = 0; //number of words that contain between 1-4 characters
int numWords8Chars = 0; //number of words that contain between 5-8 characters
int numWords12Chars = 0; //number of words that contain between 9-12 characters
int numWordsMoreChars = 0; //number of words that contain more than 12 characters
struct node *head; //tree root node
struct node *p;

struct node
{
    string word1;
    string word2;
    string word3;
    int freq1;
    int freq2;
    int freq3;
    struct node *left;
    struct node *right;
    struct node *middle;
    struct node *extra;
    struct node *parent;

    node(string str)
    {
        word1 = str;
        word2 = "";
        word3 = "";
        freq1 = 0;
        freq2 = 0;
        freq3 = 0;
        left = NULL;
        middle = NULL;
        right = NULL;
        extra = NULL;
        parent = NULL;
    }
};

void countWordLength(string str)
{
    if (str.length() < 5)
        numWords4Chars++;
    else if (str.length() < 9)
        numWords8Chars++;
    else if (str.length() < 13)
        numWords12Chars++;
    else
        numWordsMoreChars++;
}

void printTree(node *node)
{
    cout << "  *printTree: ";
    if (node->left == NULL)
    {
         cout << "word1: " << node->word1 << ", freq1: " << node->freq1;
        if (node->word2 == "")
            cout << endl;
        else
            cout << ", word2: " << node->word2 << ", freq2: " << node->freq2 << endl;
    }
    else if (node->word1 != "" && node->word2 != "")
    {
        printTree(node->left);
        cout << "word1: " << node->word1 << ", freq1: " << node->freq1;
        printTree(node->middle);
        cout << ", word2: " << node->word2 << ", freq2:  " << node->freq2 << endl;
        printTree(node->right);
    }
    else //if this node has one key
    {
        printTree(node->left);
        cout << "word1: " << node->word1 << ", freq1: " << node->freq1;
        printTree(node->right);
    }
}

//if word1 < word2, return -1
//if word1 > word2, return 1
//if the words are equal, return 0
int compare(string word1, string word2)
{
    for (int i = 0; i < word1.length() && i < word2.length(); i++)
    {
        if ((int) word1.at(i) < (int) word2.at(i))
            return -1;
        else if ((int) word1.at(i) > (int) word2.at(i))
            return 1;
    }
    return 0;
}

void split(node *n)
{
    cout << "split()\n";
    string temp1 = n->word1;
    string temp2 = n->word2;
    string temp3 = n->word3;
    int int1 = n->freq1;
    int int2 = n->freq2;
    int int3 = n->freq3;

    cout << "n: " << n << endl;;
    cout << "n->left: " << n->left << endl;
    cout << "n->right: " << n->right << endl;
    cout << "n->parent: " << n->parent << endl;

    //if (n does not have a parent)
    if (n->parent == NULL)
    {
        cout << "if (n->parent == NULL)\n";
        //create a new node, p.
 /**/       p = new node(temp2);
        p->freq1++;
        n->parent = p;
        head = p;
        struct node *n1 = new node(temp1);
        n1->freq1 = int1;
        struct node *n2 = new node(temp3);
        n2->freq1 = int3;
        p->left = n1;
        p->right = n2;
        n1->parent = p;
        n2->parent = p;

        if (n->extra != NULL)
        {
            
        }
    }
    //else if parent is available
    else
    {
        struct node *n1 = new node(temp1);
        n1->freq1 = int1;
        struct node *n2 = new node(temp3);
        n2->freq1 = int3;
        p->left = n1;
        p->middle = n2;
        n1->parent = p;
        n2->parent = p;

        cout << "else\n";
/**/        p = n->parent;
        if (p->word2 == "")
        {
            p->word2 = temp2;
            p->freq2++;
            p->left = n1;
            p->middle = n2;
        }
        else //there are 2 words in this node
        {
            /**********PROBLEM OCCURS HERE**********/
            p->word3 = temp2;
            p->freq3++;
            p->right = n1;
            p->extra = n2;
        }
        //p is the parent of n
    }
  
    //if (p now has three items/key
    if (p->word1 != "" && p->word2 != "" && p->word3 != "")
        split(p);
}


void insert(node *&n, string str)
{
    cout << "insert()\n";
    if (n == NULL)
    {
        n = new node(str);
        n->freq1++;
    }        
    else if (n->left == NULL) //if the node has children
    {
        if (n->word2 == "")    //IF word2 is empty
        {
            if (compare(n->word1, str) == 0) //dulpicate has been found
                n->freq1++;  //since word2 is the same as word1, increase word1 freq
            else    //if word2 is not the same as word1
            {
                n->word2 = str; //word2 becomes str
                n->freq2++;     //increase word2 freq

                if (compare(n->word1, str) == 1)   //IF word1 > word2, swap
                {
                    string one = n->word1;
                    string two = n->word2;
                    int freqOne = n->freq1;
                    int freqTwo = n->freq2;

                    //SWAP word1 and word2
                    n->word1 = two;
                    n->freq1 = freqTwo;
                    n->word2 = one;
                    n->freq2 = freqOne;
                }
            }
        }
        else   //ELSE if word2 is not null
        {
            string one = n->word1;
            string two = n->word2;
            int fre1 = n->freq1;
            int fre2 = n->freq2;

            if (compare(one, str) == 0)      //if str is the same as word1, increase word1 freq
                n->freq1++;
            else if (compare(two, str) == 0) //if str is the same as word2, increase word2 freq
                n->freq2++;
            else                //if str is not the same word as one or two
            {
                n->word3 = str;        //insert word at word3
                string three = n->word3;
                int fre3 = n->freq3++;

             /**********SWAP**********/

                //if word2 < word3 < word1
                if (compare(n->word2, n->word3) == -1 &&
                    compare(n->word3, n->word1) == -1 &&
                    compare(n->word1, n->word2) == 1)
                {
                    n->word1 = two;
                    n->freq1 = fre2;
                    n->word2 = three;
                    n->freq2 = fre3;
                    n->word3 = one;
                    n->freq3 = fre1;
                }
                //if word2 < word1 < word3
                else if (compare(n->word2, n->word1) == -1 &&
                         compare(n->word1, n->word3) == -1 &&
                         compare(n->word3, n->word2) == 1)
                {
                    n->word1 = two;
                    n->freq1 = fre2;
                    n->word2 = one;
                    n->freq2 = fre1;
                    //n->word3 = three;
                    //n->freq3 = fre3;
                }
                //if word3 < word1 < word2
                else if (compare(n->word3, n->word1) == -1 &&
                         compare(n->word1, n->word2) == -1 &&
                         compare(n->word1, n->word2) == 1)
                {
                    n->word1 = three;
                    n->freq1 = fre3;
                    n->word2 = one;
                    n->freq2 = fre1;
                    n->word3 = two;
                    n->freq3 = fre2;
                }
                //if word3 < word2 < word1
                else if (compare(n->word3, n->word2) == -1 &&
                         compare(n->word2, n->word1) == -1 &&
                         compare(n->word1, n->word3) == 1)
                {
                    n->word1 = three;
                    n->freq1 = fre3;
                    //n->word2 = two;
                    //n->freq2 = fre2;
                    n->word3 = one;
                    n->freq3 = fre1;
                }
                //if word1 < word3 < word2
                else if (compare(n->word1, n->word3) == -1 &&
                         compare(n->word3, n->word2) == -1 &&
                         compare(n->word2, n->word1) == 1)
                {
                    //n->word1 = one;
                    //n->freq1 = fre1;
                    n->word2 = three;
                    n->freq2 = fre3;
                    n->word3 = two;
                    n->freq3 = fre2;
                }
                split(n);
               //  head = p;
            }
        }
    }
    else
    {
        if (compare(n->word1, str) == 1)   //if str < word1
            n = n->left;
        else if (compare(n->word2, str) == 1) //if str < word2  
            n = n->middle;
        else //if (compare(str, n->word2) == 1) //if str > word2
            n = n->right;

        n->parent = n;
        insert (n, str);
    }
}

/*
node* findKey(node *&n, string str, bool success)
{
    if (str.compare(n->word1) == 0 || str.compare(n->word2) == 0)
        success = true;
    else if (n->left == NULL && (str.compare(n->word1) != 0 && str.compare(n->word2) != 0))
        success = false;
    else if (n->word2 != "")
    {
     //   if (searchkey < smaller key of the node)
       if (compare(str, n->word1) == -1)
            findKey(n->left, str, success);
       else if (compare(str, n->word2) == -1)
            findKey(n->middle, str, success);
        else // if (searchkey  > larger key of the node)
            findKey(n->right, str, success);
        }
    else
    {
        if (compare(str, n->word1) == -1)
            findKey(n->left, str, success);
        else
            findKey(n->right, str, success);
        }
}
 */

/*
 *
 */
int main(int argc, char** argv)
{
    string line = "";
    string word = "";
    int lineNum = 1;

    while (getline(cin, line))
    {
        //   cout << "length: " << line.length() << endl;
        //   cout << "lineNum: " << lineNum << " - " << line << endl;

        for (int i = 0; i < line.length(); i++)
        {
            //cout << "line.at(" << i << "): " << line.at(i) << endl;
            //cout << "ascii: " << (int) line.at(i) << endl;

            //alpha
            if (((int) line.at(i) > 64 && (int) line.at(i) < 91) || ((int) line.at(i) > 96 && (int) line.at(i) < 123))
            {
                word += tolower(line.at(i));
            }//numbers
            else if ((int) line.at(i) > 47 && (int) line.at(i) < 58)
            {
                word += line.at(i);
            }//everything else...periods, spaces, new lines, etc
                //make a new word
            else
            {
                //checks to see if char is hyphen or apostrophe
                if ((int) line.at(i) == 45 || (int) line.at(i) == 39)
                {
                    if (i + 1 < line.length())
                       // cout << "isalnum: " << isalnum(line.at(i + 1)) << endl;
                    //check for multiple non-alpha chars at next char
                    if (i + 1 < line.length() && isalnum(line.at(i + 1)) == 0)
                    {
                        if (word != "")
                        {
            cout << "WORD: " << word << endl;
                            countWordLength(word);
                            insert(head, word);
                            word = "";
                            printTree(head);
                        }
                    }//continue to next if statement
                            else
                            {
                                //  cout << "continue\n";
                                continue;
                            }
                    }
                    if (word != "")
                    {
              cout << "WORD: " << word << endl;
                        countWordLength(word);
                        insert(head, word);
                        word = "";
                        printTree(head);
                    }
                }
                //check if end of line
                if (i + 1 == line.length() && word != "")
                {
                 cout << "word: " << word << endl;
                    countWordLength(word);
                    insert(head, word);
                    word = "";
                    printTree(head);
                }
            }
            lineNum++;
        }

        cout << "\nThe height of the 2-3 Tree is " << height << endl;
        cout << "The number of distinct nodes/words is " << numberOfWords << endl;
        cout << "The number of words that have between 1 to 4 characters is " << numWords4Chars << endl;
        cout << "The number of words that have between 5 to 8 characters is " << numWords8Chars << endl;
        cout << "The number of words that have between 9 to 12 characters is " << numWords12Chars << endl;
        cout << "The number of words that have more than 12 characters is " << numWordsMoreChars << endl;
        cout << "Word Histogram(freq - word): " << endl;
        printTree(head);
        return 1;
    }
