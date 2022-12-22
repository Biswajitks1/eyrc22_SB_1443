// CODED BY SAURABH
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NODES 26
#define INT_MAX_def (INT_MAX-10000) //done to take care of the addition manipulations

void modifyShortestPath(int shortest_path[NODES][NODES], int copyFrom, int copyTo){
    int i;
    for(i=0;i<NODES && shortest_path[copyFrom][i]!=INT_MAX_def;i++){
        shortest_path[copyTo][i]=shortest_path[copyFrom][i];
    }
    shortest_path[copyTo][i]=copyTo;
}

int isAbsent(int s[],int a) //checks if a is absent in s
{
    for(int i=0;i<NODES && s[i]!=INT_MAX_def;i++){
        if(s[i]==a)
            return 0;
    }
    return 1;
}

int minimumIndex(int s[],int min_cost[]){ //finds index(not present in s) of minimum cost from min_cost

    int min_cost_copy[NODES];
    for(int i=0;i<NODES;i++){
        if(isAbsent(s,i))
            min_cost_copy[i]=min_cost[i];
        else
            min_cost_copy[i]=INT_MAX_def;
    }

    int min_idx=0;
    for(int i=0;i<NODES;i++){
        if(min_cost_copy[i]<min_cost_copy[min_idx])
            min_idx=i;
    }
    return min_idx;
}

void print1Darray(int a[],int n){
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}

void dijkstraAlgo(int dataset[NODES][NODES], int s_node)
{
    int s[NODES]; //contains node sortest path to which from s_node is known
    int min_cost[NODES]; // minimum cost of reaching to a particular node, default filling: INT_MAX_def (infinity)
    int shortest_path[NODES][NODES]; // shortest path sequence to reaching a particular node
                                     // sortest_path[1] denotes a sequence of sortest_path[1][j] to reach 1 from s_node

    for(int i=0;i<NODES;i++) s[i]=INT_MAX_def;
    for(int i=0;i<NODES;i++) min_cost[i]=INT_MAX_def; //O(n)  //filling with infinity
    for(int i=0;i<NODES;i++){
        shortest_path[i][0]=s_node; //filling the i,0 with start node considering the fact that the graph is connected and so there will be a path
        for(int j=1;j<NODES;j++)
            shortest_path[i][j]=INT_MAX_def; //filling rest with infinity
    } //O(n^2)

    min_cost[s_node]=0;

    //iterate through s array 
        //find the index(not present in s) of the minimum cost
        //put this index in s
        //iterate through min_cost array
            //make change to the min_cost if the cost already present is more than that if we traverse through new node entered into the s array

    for(int i=0;i<NODES;i++){//iteration for s array
        int min_idx=minimumIndex(s,min_cost); //the index(not present in s) of the minimum cost
        s[i]=min_idx; //pushing this index in s
        for(int j=0;j<NODES;j++){//iterate through min_cost array
            if(dataset[min_idx][j]!=INT_MAX_def && min_cost[j]>(min_cost[min_idx]+dataset[min_idx][j])){
                min_cost[j]=min_cost[min_idx]+dataset[min_idx][j];
                //modify shortest_path array
                modifyShortestPath(shortest_path,min_idx,j); //copy shortest_path[i]+j
            }
        }
    }

    //PRINTING
    for(int i=0;i<NODES;i++){
        printf("To reach Node: %d\n\tPath: ",i);
        for(int j=0;j<NODES && shortest_path[i][j]!=INT_MAX_def;j++){
            printf("%d ",shortest_path[i][j]);
        }
        printf("\n\tCost: %d\n",min_cost[i]);
    }
}

void main()
{
    //dataset.txt file is used to fill the dataset array
    int dataset[NODES][NODES];
    FILE *file;
    file=fopen("dataset.txt","r");
    for(int i=0;i<NODES;i++){
        for(int j=0;j<NODES;j++){
            fscanf(file,"%d,",&dataset[i][j]);
            if(dataset[i][j]==0 && i!=j)
                dataset[i][j]=INT_MAX_def; // INT_MAX_def is assumed to be infinity
        }
        fscanf(file,"\n");
    }
    fclose(file);

//UNCOMMENT FOLLOWING PART TO PRINT DATASET ARRAY
    // for(int i=0;i<NODES;i++){
    //     for(int j=0;j<NODES;j++){
    //         printf("%d\t",dataset[i][j]);
    //     }
    //     printf("\n");
    // }
                
    dijkstraAlgo(dataset,0);
                //array,start node
}
