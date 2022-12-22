// CODED BY SAURABH
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NODES 26
#define INT_MAX_def (INT_MAX-10000) //done to take care of the addition manipulations
int (*shortest_path)[NODES]; // shortest path sequence to reaching a particular node
                                     // sortest_path[1] denotes a sequence of sortest_path[1][j] to reach 1 from s_node

void modifyShortestPath(int shortest_path[NODES][NODES], int copyFrom, int copyTo){
    int i;
    for(i=0;i<NODES && shortest_path[copyFrom][i]!=INT_MAX_def;i++){
        shortest_path[copyTo][i]=shortest_path[copyFrom][i];
    }
    shortest_path[copyTo][i]=copyTo;
}

int isAbsent(int s[],int a)
{
    for(int i=0;i<NODES && s[i]!=INT_MAX_def;i++){
        if(s[i]==a)
            return 0;
    }
    return 1;
}

int minimumIndex(int s[],int min_cost[]){

    int min_cost_copy[NODES];
    int i;
    for(i=0;i<NODES;i++){
        if(isAbsent(s,i))
            min_cost_copy[i]=min_cost[i];
        else
            min_cost_copy[i]=INT_MAX_def;
    }

    int min_idx=0;
    for(i=0;i<NODES;i++){
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

int (*dijkstraAlgo(int dataset[NODES][NODES], int s_node,int e_node))[NODES]
{
    int s[NODES]; //contains node sortest path to which from s_node is known
    int min_cost[NODES]; // minimum cost of reaching to a particular node, default filling: INT_MAX_def (infinity)
    //int shortest_path[NODES][NODES]; // shortest path sequence to reaching a particular node
                                     // sortest_path[1] denotes a sequence of sortest_path[1][j] to reach 1 from s_node
    int i,j;
    for(i=0;i<NODES;i++) s[i]=INT_MAX_def;
    for(i=0;i<NODES;i++) min_cost[i]=INT_MAX_def; //O(n)  //filling with infinity
    for(i=0;i<NODES;i++){
        shortest_path[i][0]=s_node; //filling the i,0 with start node considering the fact that the graph is connected and so there will be a path
        for(j=1;j<NODES;j++)
            shortest_path[i][j]=INT_MAX_def; //filling rest with infinity
    } //O(n^2)

    min_cost[s_node]=0;

    //iterate through s array 
        //find the index(not present in s) of the minimum cost
        //put this index in s
        //iterate through min_cost array
            //make change to the min_cost if the cost already present is more than if a new node is entered into the s array

    for(i=0;i<NODES;i++){//iteration for s array
        int min_idx=minimumIndex(s,min_cost); //the index(not present in s) of the minimum cost
        s[i]=min_idx; //pushing this index in s
        if(min_idx==e_node)
            break;
        for(j=0;j<NODES;j++){//iterate through min_cost array
            if(dataset[min_idx][j]!=INT_MAX_def && min_cost[j]>(min_cost[min_idx]+dataset[min_idx][j])){
                min_cost[j]=min_cost[min_idx]+dataset[min_idx][j];
                //modify shortest_path array
                modifyShortestPath(shortest_path,min_idx,j); //copy shortest_path[i]+j
            }
        }
    }
    return shortest_path;
}

int main()
{
	int dataset[26][26]={	{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{3,0,3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,3,0,1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,3,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,3,1,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,2,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,2,0,0,0,3,0,1,0,0,0,3,0,0,0,0,0,0,0,0},
							{0,3,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,2,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
							{0,0,0,0,0,0,3,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,1,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,2,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,2,0,0,1,0,3},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,0,2,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0},
							{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0}
						};
    int i,j;
    for(i=0;i<NODES;i++){
        for(j=0;j<NODES;j++){
            if(dataset[i][j]==0 && i!=j)
                dataset[i][j]=INT_MAX_def; // INT_MAX_def is assumed to be infinity
        }
    }
//UNCOMMENT FOLLOWING PART TO PRINT DATASET ARRAY
    // for(int i=0;i<NODES;i++){
    //     for(int j=0;j<NODES;j++){
    //         printf("%d\t",dataset[i][j]);
    //     }
    //     printf("\n");
    // }
    int s_node=13; // start node
    int e_node=25; // end node
    
    shortest_path=(int (*)[NODES])malloc(sizeof(int)*NODES*NODES);
    shortest_path=dijkstraAlgo(dataset,s_node,e_node);
                            //array,start node,end node
//UNCOMMMENT FOLLOWING PART TO PRINT SHORTEST PATH
    // for(i=0;i<NODES && shortest_path[e_node][i]!=INT_MAX_def;i++){
    //     printf("%d ",shortest_path[e_node][i]);
    // }

}
