/* 
 * File:   kottofyBST.cpp
 * Author: Kristin Ottofy
 * Created on March 4, 2011, 10:14 AM
 */

#include <string>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;

string text;
int wordNum = 0, wordCount = 0, lineNum = 0;

struct node {
    string word;
    int freq;
    struct node *left;
    struct node *right;

    node(string str = "", int i = 1) {
        word = str;
        freq = i;
        left = NULL;
        right = NULL;
    }
};

/*calculate the height of the tree*/
int treeHeight(node *node) {
    int height = 0;
    if (node == NULL) //For an empty tree
        return height;
    else {
        height = 1; //for the root
        return height + max(treeHeight(node->left), treeHeight(node->right));
    }
}

/*add a node to the tree*/
void insert(node *&n, string str)
{
 //   cout <<"insert\n";
    if (n == NULL)
    { //if the tree is empty, the root becomes the added node
        n = new node(str);
        wordCount++; //increment the wordCount since a node was added
        return;
    }// find where to insert the node based on value
        // if the word is less than the current node, evaluate the left subtree
        // if the word is greater than the current node, evalutae the right subtree
    else if (str < n->word)
    {
        insert(n->left, str);
    }
    else
    {
        insert(n->right, str);
    }
}

/*return true if the word is a duplicate in the tree, if not return false*/
bool isDuplicate(node *node, string str)
{
    if (node == NULL) //if the tree is empty, then there are no duplicates
        return false;
    else if (str == node->word)
    { // the word has been found in the current node
        node->freq++; //increment the frequency of the node
        return true;
    }//if the word is less than the word at the current node, evaluate the left subtree
    else if (str < node->word)
        return isDuplicate(node->left, str);
        //if the word is greater than the word at the current node, evaluate the right subtree
    else
        return isDuplicate(node->right, str);
}

/*print the words in the tree in postorder*/
void printTree(node *node)
{
    if (node != NULL)
    {
        printTree(node->left); // Evaluate the left subtree.
        cout << node->freq << " - " << node->word  << endl; // Print item in the node.
        printTree(node->right); // Evaluate the right subtree.
    }
}

int main(int argc, char* argv[])
{
    int height = 0; //height of tree
    int numberOfWords = 0; //total number of words in tree
    int numWords4Chars = 0; //number of words that contain between 1-4 characters
    int numWords8Chars = 0; //number of words that contain between 5-8 characters
    int numWords12Chars = 0; //number of words that contain between 9-12 characters
    int numWordsMoreChars = 0; //number of words that contain more than 12 characters
    struct node *head; //tree root node

    string line; //hold each line of the text file

    //the two markers used in this code that says when a word has been found are spaces and puncuation
    //so there needs to be a check for whether a punction is in the middle of the word or not
    //if it is then assume it's part of the word, remove it, and add the word to the tree
    while (getline(cin, line))
    { //while !eof
   //     cout << "while (getline(cin,line)) \n";
        string word = ""; //hold the current word to add the the tree
        for (int i = 0; i < line.length(); i++)
        {//evaluate each character of the line
    /*        cout << "word: " << word << endl;
            cout << "line(" << i << "): " << line.at(i) << endl;
            cout << "line: " << line << endl;
            cout << "isalpha: " << isalpha(line.at(i)) << endl;
            cout << "ispunct: " << ispunct(line.at(i)) << endl;
            cout << "isdigit: " << isdigit(line.at(i)) << endl;
            bool isspace = line.at(i) != ' ';
            cout << "isspace: " << isspace << endl;
            //      cout << "isalnum: " << isalnum(line.at(i + 1)) << endl;
            cout << "isblank: " << isblank(line.at(i)) << endl;
            cout << "line.length: " << line.length() << endl;*/

            //if the character is an alphabet letter or digit, add it to the temporary word
            if (isalnum(line.at(i)) > 0)
            {
                word += tolower(line.at(i));
                if (i==line.length()-1)
                {
                    if ((word.length() > 0))
                    {
                        if (!isDuplicate(head, word))
                        {
                            insert(head, word); //add the word to the tree
                            numberOfWords++; //increment total number of words in the tree
                            if (word.length() < 5) //calulate how many characters and increment appropriate count
                                numWords4Chars++;
                            else if (word.length() < 9)
                                numWords8Chars++;
                            else if (word.length() < 13)
                                numWords12Chars++;
                            else
                                numWordsMoreChars++;
                        }
                    }
                }
            }

            //if the character is a punctuation or blank (new line, space, etc...)
            //add the word to the tree or skip that character
            else
            {   
                if ((isblank(line.at(i)) > 0) || (i + 1 < line.length()) && (!isalnum(line.at(i + 1))))
                {
                    if ((word.length() > 0))
                    {
                        if (!isDuplicate(head, word))
                        {
                            insert(head, word); //add the word to the tree
                            numberOfWords++; //increment total number of words in the tree
                            if (word.length() < 5) //calulate how many characters and increment appropriate count
                                numWords4Chars++;
                            else if (word.length() < 9)
                                numWords8Chars++;
                            else if (word.length() < 13)
                                numWords12Chars++;
                            else
                                numWordsMoreChars++;
                        }
                    }
                }
                word = "";
            }


   /*
            if (ispunct(line.at(i)) && !isblank(line.at(i)))
            { //if the character is punctuation and not a space
      //          cout << "ispunct(line.at(i)) && !isblank(line.at(i))) \n";
        //         line.erase(i, 0);                               //erase the character from the string
                if (i + 1 < line.length() && ispunct(line.at(i + 1)))
                { //if the next letter is also punctuation that means a word has been found
         //           cout << "if (i + 1 < line.length() && ispunct(line.at(i + 1)))\n";
                    if (word.length() > 0 && !isDuplicate(head, word))
                    { //if the word is more than 0 characters and is not already in the tree
          //              cout << "if (word.length() > 0 && !isDuplicate(head, word))\n";
                        insert(head, word); //add the word to the tree
                        numberOfWords++; //increment total number of words in the tree
                        if (word.length() < 5) //calulate how many characters and increment appropriate count
                            numWords4Chars++;
                        else if (word.length() < 9)
                            numWords8Chars++;
                        else if (word.length() < 13)
                            numWords12Chars++;
                        else
                            numWordsMoreChars++;
                    }
                    word = ""; //reset word
                }
            }
            else if (isalnum(line.at(i)))
            { //if the character is a letter or digit
        //        cout << "else if (isalnum(line.at(i)))\n";
                if (isalpha(line.at(i))) //if the character is a letter
                {
        //            cout << " if (isalpha(line.at(i))) \n";
                    word += tolower(line.at(i)); //make sure it's all lowercase and add to the word
                } else
                {
        //           cout << "else\n";
                    word += line.at(i); //else add it to the word
                }
            }
            else
            { //ELSE the word needs to be added to the tree
        //        cout << "else\n";
                if (word.length() > 0 && (isalnum(word.at(0))))
                {
          //          cout << " if (word.length() > 0 && (isalnum(word.at(0))))\n";
                    if (!isDuplicate(head, word))
                    { //if the word is not a duplicate
         //               cout << "if (!isDuplicate(head, word))\n";
                        insert(head, word); //add the word to the tree
                        numberOfWords++; //increment the total number of words
                        if (word.length() < 5) //calulate how many characters and increment appropriate count
                            numWords4Chars++;
                        else if (word.length() < 9)
                            numWords8Chars++;
                        else if (word.length() < 13)
                            numWords12Chars++;
                        else
                            numWordsMoreChars++;
                    } else
        //                cout << "skipped if\n";
                    word = ""; //reset word
                }
            }
        } */
    }

    height = treeHeight(head); //calculate the height of the tree

    cout << "\nThe height of the BST is " << height << endl;
    cout << "The number of distinct nodes/words is " << numberOfWords << endl;
    cout << "The number of words that have between 1 to 4 characters is " << numWords4Chars << endl;
    cout << "The number of words that have between 5 to 8 characters is " << numWords8Chars << endl;
    cout << "The number of words that have between 9 to 12 characters is " << numWords12Chars << endl;
    cout << "The number of words that have more than 12 characters is " << numWordsMoreChars << endl;
    cout << "Word Histogram(freq - word): " << endl;
    printTree(head);

    return 0;
    }
}
