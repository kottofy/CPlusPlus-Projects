#include <iostream>
#include <fstream>

using namespace std;

int main(){
    char rrmFile[15]; 
    char request[3];
    char order[1];
    char rrm[10][10];
    char adjacency[10][10];
    char path[10][10]; 
    char wait[10][10];
    char resourceAllocation[10][1];
    char c;     
    int n;
    char one[2];
    char two[2];
    cout << "Input the name of the RRM file: " << endl;
    cin >> rrmFile;
    cout << "Resource Requirement Matrix: " << endl;
    
    //reads the file with the Resource Requirement Matrix and prints out the matrix
    ifstream file (rrmFile);
    if(file.is_open()){
        for(int i=0; i<10; i++){
            for(int j=0; j<10; j++){
                file >> c;
                rrm[i][j]=c;
                cout << rrm[i][j];
            }
            cout << "\n";
         
        } 
    }
    else{
        cout << "could not open file" << endl;
    }
    for(int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            adjacency[i][j]='0';
        }
    }
    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++){
            path[i][j]='0';
        }
    }
    cout << "INSTRUCTIONS: " << endl;
    cout << "To make a request, type R. " << endl;
    cout << "Then type the process followed by the resource requested (no space)" << endl;
    cout << "Processes and Requests range from 0 to 9. " << endl;
    cout << "To quit, type Q" << endl;
    
    cin >> order;
    while (order[0]=='R'){
        cin >> request;
        cout << "proccess " << request[0] << " requests the allocation of resource " << request[1] << endl;
        one[0]=request[0];
        two[0]=request[1];
        int process = atoi(one);
        int resource = atoi(two);
          
          if(rrm[process][resource]=='0'){
              cout << "The process you entered does not ever use the resource entered. " << endl;
              cin >> order;
              continue;
          }
          //checks to see if resource is already allocated to a process
          if(resourceAllocation[resource][0]=='1'){
              cout << "Resource already in use." << endl;
              cout << "Process " << process << " waits for Resource " << resource << endl; 
              wait[process][resource]='1';
          }         
          else{          
          resourceAllocation[resource][0]='1';
          
          //updates path and adjacency matrices
          //uses 2's instead of 1's so if there is a cycle, matrices can be easily restored
          for(int row=0; row<10; row++){
              if(rrm[row][resource]=='1'){
                  if(row!=process){       
                      adjacency[process][row]='2';
                      path[process][row]='2';
                                      
                      int i=process;
                      int j=row;
                      for(int a=0; a<10; a++){
                          if((path[j][a]=='1')||(path[j][a]=='2')){
                              if(path[i][a]=='1')
                                  path[i][a]='3';
                              else
                                  path[i][a]='2';
                          }
                          if((path[a][i]=='1')||(path[a][i]=='2')){
                              if(path[a][j]=='1')
                                  path[a][j]='3';
                              else
                                  path[a][j]='2';
                          }
                      }
                                                                                    
                  }
              }
          }
          
          }
          for(int b=0; b<10; b++){
              if(path[b][b]=='2'){
                  for(int z=0; z<10; z++){
                      for(int x=0; x<10; x++){
                          if(path[z][x]=='2')
                              path[z][x]='0';
                          else if(path[z][x]=='3')
                              path[z][x]='1';
                          if(adjacency[z][x]=='2')
                              adjacency[z][x]='0';
                      }
                  }
                  resourceAllocation[resource][0]='0';
                  cout << "Process " << process << " waits for resource " << resource << endl;
                  wait[process][resource]='1';
                  break;
              }
          }
          for(int w=0; w<10; w++){
              for(int s=0; s<10; s++){
                  if(path[w][s]=='2')
                      path[w][s]='1';
                  else if(path[w][s]=='3')
                      path[w][s]='1';
                  if(adjacency[w][s]=='2')
                      adjacency[w][s]='1';
              }
          }
          
          for (int i=0; i<10; i++){
             for (int j=0; j<10; j++){
               cout << path[i][j];
             }
             cout << "\n";
          } 
          
          
          cin >> order;
    }
    
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(wait[i][j]=='1'){
                cout << "Process " << i << " waits for Resource " << j << endl;
            }
        }
    }
    
    return 1;
}
    
