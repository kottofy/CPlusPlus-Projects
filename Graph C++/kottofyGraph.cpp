/* 
 * File:   main.cpp
 * Author: kottofy
 *
 * Created on April 26, 2011, 12:35 PM
 *
 * A program that allocates non-sharable resourcse to processes using the
 * Deadlock avoidance algorithm that can have a maximum of 10 process and 10
 * resources.
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    char fileName[20];
    int rrm[10][10];
    int adjacency[10][10];
    int path[10][10];
    int wait[10][1];
    int alloc[10];
    bool fileIsOpen = false;
    bool deadlock;
    char c;
    int n, m;
    int adj_temp[10][10];
    int path_temp[10][10];

    do
    {
        cout << "\nInput the filename of the RRM: " << endl;
        cin >> fileName;

        //open file and save to char rrm[10][10]
        ifstream file(fileName);
        if (file.is_open())
        {
            fileIsOpen = true;
            cout << "\nResource Requirement Matrix" << endl;
            cout << "  0 1 2 3 4 5 6 7 8 9 " << endl;
            cout << "---------------------" << endl;
            for (int i = 0; i < 10; i++)
            {
                cout << i;
                for (int j = 0; j < 10; j++)
                {
                    file >> c;
                    rrm[i][j] = (int) c - 48;
                    cout << " " << rrm[i][j];
                }
                cout << endl;
            }
        }
        else
        {
            cout << "Could not open file." << endl;
        }
    } while (!fileIsOpen);

    /*initialize all matrices*/
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            adjacency[i][j] = 0;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            path[i][j] = 0;
        }
    }

    /*set wait and alloc to -1 since processes are 0..9*/
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            wait[i][j] = -1;
        }
    }
    for (int i = 0; i < 10; i++)
    {
        alloc[i] = -1;
    }

    cout << "\nENTER 'Q' TO QUIT\n\n";

    int p;
    int r;

    while (1)
    {
        cout << "Please enter \"R\" and a process (0-9) and a resource (0-9): \n> ";
        cin >> c;

        if (c == 'q' || c == 'Q')   //quit
            break;
        else if (c == 'r' || c == 'R')
        {
            cin >> p;
            cin >> r;

            if ((p < 0 || p > 9) || (r < 0 || r > 9))   //if # is not 0..9
            {
                cout << "Incorrect Process Resource pair. Please try again." << endl;
                continue;
            }

            // check to see if process is able to request allocation of resource
            if (rrm[p][r] == 1) // if it equals 1
            {
                cout << "Process " << p << " is requesting allocation of resource " << r << endl;

                // check allocation table
                if (alloc[r] == 1)
                {
                    cout << "Resource is already in use" << endl;
                    cout << "Trying to add to wait table..." << endl;

                    // wait initialized to -1, gets 0..9 for the process,
                    // indexed by resource 0..9
                    if (wait[r][0] > 0)     //if wait contains resource already dedication to a process
                    {
                        cout << "Unable to add to wait table. Resource is probably "
                                << "current being waited on" << endl;
                    }
                    else    //process is able to wait on resource
                    {
                        cout << "Process " << p << " is waiting on resource " << r << endl;
                        wait[r][0] = p;     //wait at resource index contains the process #

                        /*****************************************
                        cout << "\nWait Table: " << endl;
                        cout << "Resource  |  Process" << endl;
                        cout << "--------------------" << endl;
                        for (int i = 0; i < 10; i++)
                        {
                            if (wait[i][0] > -1)
                            {
                                cout << "    " << i << "     |     " << wait[i][0] << endl;
                            }
                        }
                        /********************************************/
                    }
                }
                else // not in alloc table ie not already allocated, try to allocate
                {
                    cout << "Resource is currently not in use. Attempting to allocate..." << endl;

                    // setup TEMP adjacency[][] and path[][]
                    for (n = 0; n < 10; n++)
                    {
                        for (m = 0; m < 10; m++)
                        {
                            adj_temp[n][m] = adjacency[n][m];
                            path_temp[n][m] = path[n][m];
                        }
                    }

                    // take the "process"es found in rrm and update adj_temp[p][process]
                    for (int process = 0; process < 10; process++)
                    {
                        // go through every process in a resource column where it equals the argument p
                        if (rrm[process][r] == 1 && p != process) 
                        {
                            adj_temp[p][process] = 1;
                            path_temp[p][process] = 1;

                            // now update the path_adj[][] using the algorithm:
                            // row i = row i or row j
                            for (n = 0; n < 10; n++)
                            {
                                if (path_temp[p][n] != 0 || path_temp[process][n] != 0)
                                {
                                    path_temp[p][n] = 1;
                                }
                            }
                            // col j = col i or col j
                            for (n = 0; n < 10; n++)
                            {
                                if (path_temp[n][p] != 0 || path_temp[n][process] != 0)
                                {
                                    path_temp[n][process] = 1;
                                }
                            }

                            // check for cycles
                            for (n = 0; n < 10; n++)
                            {
                                if (path_temp[n][n] != 0)
                                {
                                    cout << "Deadlock Found!" << endl;
                                    deadlock = true;
                                    break;  // exit cycle searching loop
                                }
                            }
                            if (deadlock == true) // add to wait table if can
                            {
                                cout << "Trying to add to wait table..." << endl;

                                if (wait[r][0] > 0)
                                {
                                    cout << "Unable to add to wait table. Resource is "
                                            << "currently being waited on" << endl;
                                }
                                else    // process can wait on resource
                                {
                                    cout << "Process " << p << " is waiting on resource " << r << endl;
                                    wait[r][0] = p;

                                    /*****************************************
                                    cout << "\nWait Table: " << endl;
                                    cout << "Resource  |  Process" << endl;
                                    cout << "--------------------" << endl;
                                    for (int i = 0; i < 10; i++)
                                    {
                                        if (wait[i][0] > -1)
                                        {
                                            cout << "    " << i << "     |     " << wait[i][0] << endl;
                                        }
                                    }
                                    /********************************************/
                                }
                                deadlock = false;
                                break;  //exit out of loop since deadlock was found
                            }   //deadlock was not found, commit changes
                            else
                            {
                                /***********************************
                                cout << "\nAdjacency TEMP Matrix\n";
                                cout << "  0 1 2 3 4 5 6 7 8 9 " << endl;
                                cout << "---------------------" << endl;
                                for (int i = 0; i < 10; i++)
                                {
                                    cout << i;
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << " " << adj_temp[i][j];
                                    }
                                    cout << endl;
                                }

                                cout << "\nPath TEMP Matrix\n";
                                cout << "  0 1 2 3 4 5 6 7 8 9 " << endl;
                                cout << "---------------------" << endl;
                                for (int i = 0; i < 10; i++)
                                {
                                    cout << i;
                                    for (int j = 0; j < 10; j++)
                                    {
                                        cout << " " << path_temp[i][j];
                                    }
                                    cout << endl;
                                } */

                                // commit changes for this p,process pair from RRM[p][process]
                                // add to allocation table
                                alloc[r] = 1;   //allocate resource
                                cout << "Allocation Successful!\n";

                                // copy temps into perms
                                for (n = 0; n < 10; n++)
                                {
                                    for (m = 0; m < 10; m++)
                                    {
                                        adjacency[n][m] = adj_temp[n][m];
                                        path[n][m] = path_temp[n][m];
                                    }
                                }
                                break;  
                            }
                        }
                    }
                }
            } // end of if rrm[][] == 1
            else //process is unable to request allocation of resource
            {
                cout << "Process " << p << " is not able to request allocation of resource "
                        << r << endl;
            }

         /*   cout << "\nAdjacency Matrix\n";
            cout << "  0 1 2 3 4 5 6 7 8 9 " << endl;
            cout << "---------------------" << endl;
            for (int i = 0; i < 10; i++)
            {
                cout << i;
                for (int j = 0; j < 10; j++)
                {
                    cout << " " << adjacency[i][j];
                }
                cout << endl;
            }

            cout << "\nPath Matrix\n";
            cout << "  0 1 2 3 4 5 6 7 8 9 " << endl;
            cout << "---------------------" << endl;
            for (int i = 0; i < 10; i++)
            {
                cout << i;
                for (int j = 0; j < 10; j++)
                {
                    cout << " " << path[i][j];
                }
                cout << endl;
            }*/
        }
    } // end of interactive prompt { 'R', 'Q' }

    //END OF PROGRAM

    cout << "\nWait Table: " << endl;
    cout << "Resource  |  Process" << endl;
    cout << "--------------------" << endl;
    for (int i = 0; i < 10; i++)
    {
        if (wait[i][0] > -1)
        {
            cout << "    " << i << "     |     " << wait[i][0] << endl;
        }
    }
    cout << "Goodbye!\n";
    return 0;
}
