/*
 * Author: Kristin Ottofy
 * Last Edited: Friday, February 18, 2011
 *
 * Project: CSCI 2720 Assignment 1
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include "linklist.h"
#include <sys/time.h>

using namespace std;

int listSize = 0;
int* array;
double t1, t2;
    timeval tim;

void setTime() {
    // start time
    gettimeofday(&tim, NULL);
    t1 = tim.tv_sec + (tim.tv_usec / 1000000.0);
}

void getTime() {

    //end time
    gettimeofday(&tim, NULL);
    t2 = tim.tv_sec + (tim.tv_usec / 1000000.0);

    printf("\n%.6lf seconds elapsed.\n", t2 - t1);
}

bool used(int *arr, int num)
{
    for (int i = 0; i < listSize; i++)
        if (arr[i] == num)
            return false;
    return true;
}

/* 1. to generate N numbers using a random number generator
 * (intergers between x and y) and store them in a list
 * (can be implemented using an array or linked list */
int* generateRandomNumbers() {
    int min = 0, max = 0, N = 0;

    cout << "\nPlease enter the total number of elements (N): ";
    cin >> N;
    cout << "\nPlease enter the minimum number (X): ";
    cin >> min;
    cout << "\nPlease enter the maximum number (Y): ";
    cout << "\nNote: Y-X must be greater than or equal to N --  ";
    cin >> max;

    if (max-min+1 < N && N > 0)
    {
        cout << "Not correct\n";
        return array;
    }

    cout << "\nGenerating random numbers\n";
    setTime();

    int range = max - min + 1;

    listSize = N;
    int* newList = new int[listSize];

    for (int i = 0; i < listSize; i++) {
        int randomNumber = rand() / 100 % range + min;
            newList[i] = randomNumber;
    }
    getTime();
    return newList;
}

/* 2. read a list of integers from a txt file*/
int* readIn() {
    cout << "Please enter the name of the input file\n";
    cout << "Max of 20 characters\n";

    char inputFilename[20];
    string line;
    cin >> inputFilename;

    listSize = 0;

    ifstream input;
    input.open(inputFilename);

    if (input.fail()) {
        cout << "Input file error" << endl;
        return array;
    }

    cout << "Reading\n";
    setTime();

    for (int i = 0; input.good(); i++) {
        getline(input, line);
        listSize++;
    }
    listSize--;

    input.clear();
    input.seekg(0);
    int* newList = new int[listSize];

    for (int i = 0; i < listSize; i++) {
        getline(input, line);
        newList[i] = atoi(line.c_str());
    }

    input.close();
    getTime();
    listSize++;
    return newList;
}

/* 3. sort a list of numbers using QuickSort
    http://www.algolist.net/Algorithms/Sorting/Quicksort
 */
void QuickSort(int left, int right) {
    if (array == NULL) {
        cout << "Please create a list\n";
        return;
    }
    int i = left, j = right;
    int tmp;
    int pivot = array[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j) {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        QuickSort(left, j);

    if (i < right)
        QuickSort(i, right);
}

void merge(int low, int mid, int high) {
    int h, i, j, b[50], k;
    h = low;
    i = low;
    j = mid + 1;

    while ((h <= mid) && (j <= high)) {
        if (array[h] <= array[j]) {
            b[i] = array[h];
            h++;
        } else {
            b[i] = array[j];
            j++;
        }
        i++;
    }
    if (h > mid) {
        for (k = j; k <= high; k++) {
            b[i] = array[k];
            i++;
        }
    } else {
        for (k = h; k <= mid; k++) {
            b[i] = array[k];
            i++;
        }
    }
    for (k = low; k <= high; k++) array[k] = b[k];
}

void merge_sort(int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
}

/* 4. sort a list of numbers using MergeSort
 * http://www.cplusplus.happycodings.com/Algorithms/code17.html*/
void MergeSort() {
    if (array == NULL) {
        cout << "Please create a list\n";
        return;
    }
    merge_sort(0, listSize);
}

/* 5. sort a list of numbers using SelectionSort
 * http://www.fredosaurus.com/notes-cpp/algorithms/sorting/selectionsort.html*/
void SelectionSort() {
    if (array == NULL) {
        cout << "Please create a list\n";
        return;
    }

    for (int pass = 0; pass < listSize - 1; pass++) {
        int potentialSmallest = pass; // assume this is smallest

        //--- Look over remaining elements to find smallest.
        for (int i = pass + 1; i < listSize; i++) {
            if (array[i] < array[potentialSmallest]) {
                //--- Remember index for latter swap.
                potentialSmallest = i;
            }
        }

        //--- Swap smallest remaining element
        int temp = array[pass];
        array[pass] = array[potentialSmallest];
        array[potentialSmallest] = temp;
    }
}

/* 6. sort a list of numbers using ExchangeSort/BubbleSort
 * http://www.algolist.net/Algorithms/Sorting/Bubble_sort */
void BubbleSort(int n) {
    if (array == NULL) {
        cout << "Please create a list\n";
        return;
    }
    bool swapped = true;
    int j = 0;
    int tmp;

    while (swapped) {
        swapped = false;
        j++;
        for (int i = 0; i < n - j; i++) {
            if (array[i] > array[i + 1]) {
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
                swapped = true;
            }
        }
    }
}

/* 7. search for a given number in the sorted list = use Binary Search method*/
int BinarySearch(int first, int last, int number) {
    if (array == NULL) {
        cout << "Please create a list\n";
        return -1;
    }
    QuickSort(0, listSize-1);

    while (first <= last) {
        int middle = (first + last) / 2;
        if (array[middle] == number)
            return middle;
        else if (array[middle] > number)
            last = middle - 1;
        else
            first = middle + 1;
    }
    return -1;
}

/* 8. insert a given number into the correct sorted position in the list*/
void insert(int number) {
    if (array == NULL) {
        cout << "Please create a list\n";
        return;
    }
    setTime();
    array[listSize] = number;
    listSize++;
    QuickSort(0, listSize - 1);
    getTime();
}

/* 9. delete a given number from the sorted list*/
void toDelete(int deleteNumber) {
    if (array == NULL) {
        cout << "Please create a list\n";
        return;
    }
    setTime();
    
    int num = BinarySearch(0, listSize - 1, deleteNumber);
    if (num < 0)
        cout << "Number could not be found.\n";
    else
        for (int i = num; i < listSize; i++)
            array[i] = array[i + 1];
    listSize--;
    getTime();
}

/* 10. output (to a file) the content of the list*/
int output() {
    cout << "Enter the name of the output file: ";
    cout << "Max of 20 characters\n";

    char outputFilename[20];
    cin >> outputFilename;

    ofstream output;
    output.open(outputFilename);

    for (int i = 0; i < listSize; i++)
        output << array[i] << "\n";

    output.close();
    return 0;
}

void printArray() {
    for (int i = 0; i < listSize; i++)
        cout << array[i] << "\n";
}

/*Prompt user to enter a number to select item from a list*/
int select() {
    int numberSelection = 0;

    do {
        cout << "\nSELECT A NUMBER FROM THE LIST:\n";
        cout << "1. Generate random numbers\n";
        cout << "2. Read a list of number from a text file\n";
        cout << "3. Sort a list of numbers using QuickSort\n";
        cout << "4. Sort a list of numbers using MergeSort\n";
        cout << "5. Sort a list of numbers using SelectionSort\n";
        cout << "6. Sort a list of numbers using BubbleSort/ExchangeSort\n";
        cout << "7. Search for a given number in the sorted list using Binary Search\n";
        cout << "8. Insert a given number in the sorted list\n";
        cout << "9. Delete a given number from the sort list\n";
        cout << "10. Output the content of the list to a file\n";
        cout << "11. Print current array\n";
        cout << "12. Quit\n";
        cout << "Choose: ";

        cin >> numberSelection;

        if (numberSelection < 0 || numberSelection > 12)
            cout << "Please try again\n";
    } while (numberSelection < 0 || numberSelection > 12);

    return numberSelection;
}

/*
 * 
 */
int main() {

    int selection = 0;
    do {
        selection = select();

        switch (selection) {
            case 1:
            {
                array = generateRandomNumbers();
                break;
            }
            case 2:
            {
                array = readIn();
                break;
            }
            case 3:
            {
                setTime();
                QuickSort(0, listSize - 1);
                getTime();
                break;
            }
            case 4:
            {
                setTime();
                MergeSort();
                getTime();
                break;
            }
            case 5:
            {
                setTime();
                SelectionSort();
                getTime();
                break;
            }
            case 6:
            {
                setTime();
                BubbleSort(listSize - 1);
                getTime();
                break;
            }
            case 7:
            {
                cout << "Which number would you like to search for?\n";
                int number;
                cin >> number;
                setTime();
                BinarySearch(0, listSize - 1, number);
                getTime();
                cout << number << " successfully found\n";
                break;
            }
            case 8:
            {
                int number;
                cout << "Which number would you like to insert? \n";
                cin >> number;
                insert(number);
                break;
            }
            case 9:
            {
                int number;
                cout << "Which number would you like to delete? \n";
                cin >> number;
                toDelete(number);
                break;
            }
            case 10:
            {
                output();
                break;
            }
            case 11:
            {
                printArray();
                break;
            }
        }
    } while (selection != 12);

    cout << "Goodbye\n";
    return 0;
}


