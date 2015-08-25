README.txt
Author: Kristin Ottofy
Email: kottofy@gmail.com
Date: March 13, 2011
Program Name: KottofyBST

This program will read in a text file, insert each word into a binary search tree, and output some information and a word histogram. 

Note: This program converts all words to lowercase and removes all punctuation. Words that contain one punctuation such as an apostrophe or a hyphen will remove the apostrophe and save the word as a whole. I.E. the word "child-like" will be converted to "childlike" regardless of the fact that those are indeed 2 different words. 

To compile this program, type "make all"
To run this program, type ./BST.out < file.txt > output.txt
	file.txt is the name of the file being read into the program
	output.txt is the name of the file to output the summary

Example output:	*Word Histogram not included
The height of the BST is 32
The number of distinct nodes/words is 17864
The number of words that have between 1 to 4 characters is 1906
The number of words that have between 5 to 8 characters is 9796
The number of words that have between 9 to 12 characters is 5460
The number of words that have more than 12 characters is 702
Word Histogram:
