/*
 Author: Kristin Ottofy
 Date: July 5, 2010
 Program Name: MobyDick
 */

#include <string>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

// Declaring global variables:

// text will be set to the Moby Dick Text
string text;

// anagram will be set to the scrambled anagram from input
string anagram;	

// removeChars will be used to remove a character in the scrambled anagram 
// so the character will not be evaluated twice
string removeChars;    

// outputValue will be set to the unscrambled anagram for output
string outputValue;		

// textCount will be used to keep track of which character is being 
// evaluated in the text

int textCount;	

// removeCount used to keep track of which character is being evaluated in the removeChars string
int removeCount;    

// setText() will get a character of text from the Moby Dick Text and assign 
// it to the string text until the end of the file
void setText()
{
	char c = getchar();
	while (c != EOF)
	{
		text += c;
		c = getchar();
	}
}

// resetString() will be called when the unscrambeled anagram has not been
// found and will reset the potential unscrambeled anagram output string to nothing
// and the string used to evaulate remaining characters to be found in the anagram
// back to the scrambeled anagram
void resetStrings()
{
	outputValue = "";
    removeChars = anagram;
}

// setUpperOrLowerCase() will evaluate the character's case in the text being
// evaluated since when that character is compared to the scrambeled anagram, 
// the case will be set to lowercase, so when the program copies the character 
// to the unscrambled anagram string it will hold it's original case
int setUpperOrLowerCase()
{
	if (isupper((int)text[textCount]) == 1)	// if is uppercase
        return 1;
    else if (isupper((int)text[textCount]) == 0)	// else if is not uppercase
        return 2;
}

// replaceTextChar() takes the parameter of the case of the original character
// being evaluated, then adds that character to the unscrambeled anagram string
// for output purposes
void replaceTextChar(int upperOrLower)
{
    char a;
    // replace with character based on upperOrLower case format
    if (upperOrLower == 1)
    {
        a = toupper(text[textCount]);
        outputValue = outputValue + a;
    }
	
    if (upperOrLower == 2)
    {
        a = tolower(text[textCount]);
        outputValue = outputValue + a;
    }
}

// removeChar() will remove the character in the unscrambled anagram so
// it is not evaluated more than once. 
void removeChar()
{
    // remove character from string so it is not searched for again
    for (int count = removeCount; count < removeChars.length() - 1; count++)
    {
        removeChars[count] = removeChars[count + 1];
    }
	
	// after this method is called, removeCount will incremement by 1, but since
	// all characters have been pushed back to the character before it, removeCount needs
	// to decrement by 1 to evaluate the next character at the current position
    removeCount--;	
	
	// resize the unscrambled anagram string to be one less since one character was removed
    removeChars.resize(removeChars.length() -1);
}

// getLineNumber() will count the number of carriage returns or new lines are in
// the Moby Dick Text up to the point of the found unscrambled anagram
int getLineNumber()
{
	// lineNumber keeps track of the number of lines found and is incrememnted
	// when a new line is found
    int lineNumber = 1;	// starts at 1 since there is no line 0
    
	// search through text to last charcter found in the anagram
    for (int i = 0; i <= textCount; i++)
    {
        if (text[i] == '\n')	// if new line
        {
            if (text[textCount + 1] != '\r') // if the next character is not carriage return
                lineNumber++;
        }
        else if(text[i] == '\r')	// if carriage return
        {
            if (text[textCount + 1] != '\n')	// if the next character is not a new line
                lineNumber++;
		}
    }
    return  lineNumber;
}

// ifFinished() determines if there are no characters in the scrambled anagram
// left to be evaluated, prints the number of line and the unscrambled anagram,
// and exits successfully
void ifFinished()
{
    if (removeChars.length() == 0)
    {
        int lineCount = getLineNumber();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
        cout << "Line count is: " << lineCount << endl;
        cout << "Output is: " << outputValue << endl;
        exit(0);
    }
}

// setSpace() will add a space to the unscrambled string for output
void setSpace()
{
    outputValue = outputValue + ' ';
}

// ifNewLine() determines whether the character being evaluated is a new line
// and returns true if a space is needed. Only one space will be needed if a 
// new line and a carriage return are present so only returns true for one.
bool ifNewLine()
{
    if (text[textCount] == '\n')
    {
        if (text[textCount + 1] != '\r')
            return true;
        else
            return false;
	}
    else if(text[textCount] == '\r')
    {
        if (text[textCount + 1] != '\n')
            return true;
        else
            return false;
	}
    else
        return false;
}

// ifSpace() determines if the character being evaluated in the text is a space
// and returns true if it is
bool ifSpace()
{
    if (text[textCount] == ' ')
        return true;
    else
        return false;
}

// main()
int main(int argc, char* argv[])
{
	// used to keep track of original case format of text for output purposes
    int upperOrLower;  
	
	// determine if the user has entered enough parameters, if not then exit
	if (argc < 2)
	 {
		 cout << "Not enough parameters." << endl;
		 exit(1);
	 }
	 
	// all parameters will be set to the scrambled anagram
	 for (int i = 1; argv[i] != NULL; i++)
		 anagram += argv[i];
	
	// get the Moby Dick text from standard input
	setText();
	
	// set the scrambled anagram to the string removeChars that will have a character
	// removed if a letter in the scrambled anagram is found. If the anagram is not
	// found, removeChars can be reset to the scrambled anagram
    removeChars = anagram;
	
    // search through each character of the text until the end
    for (textCount = 0; textCount <= text.length(); textCount++)
    {
		// if the character in the text has not been found in the scrambled anagram
		// reset the scrambled anagram string to the original scrambled anagram 
		// string and the ouput string to ""
        if (removeCount == removeChars.length())
        {
            // Jump back to the next character to evaluate in the text otherwise the
			// next character to evaluate will be after the anagram that was not found
            if(outputValue.length() > 0)
                textCount -= outputValue.length();
			
			// reset the scrambled anagram string to the original scrambled anagram
			// string and the output string to ""
            resetStrings();
        }
		
        // loop through the scrambled anagram to see if it matches the character
		// being evaluated in the text
        for (removeCount = 0; removeCount < removeChars.length(); removeCount++)
        {
			// determine the case of the character in the text for output purposes
            upperOrLower = setUpperOrLowerCase();
			
            // if a letter in the text equals a letter in the scrambled anagram
            if (tolower(text[textCount]) == tolower(removeChars[removeCount]))
            {
                replaceTextChar(upperOrLower);	// assign the character in the text to output string
                removeChar();	// remove a character in the scrambled anagram so it is not searched for again
                ifFinished();	// determine if the unscrambled anagram has been found
                break;		// break out of loop and evaluate next character in the text
            }
            else // if the character in the text is not equal to the character in the scrambled anagram
            {
                // if the character in the text being evaluated is a new line and at least one character 
				// has been found, add a space to the output string
                if (ifNewLine() && outputValue.length() > 0)
                {
                    setSpace();
                    break;
                }
				// if the character in the text being evaluated is a space and at least one character 
				// has been found, add a space to the output string
                else if (ifSpace() && outputValue.length() > 0)
                {
                    setSpace();
                    break;
                }
                else	// otherwise, continue searching through the scrambled anagram
                    continue;
            }
        }
    }
}