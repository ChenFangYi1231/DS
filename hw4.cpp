#include <stdio.h>
#include <stdlib.h>

void minCost(int *pre, int **len, int *dis, int num, int start);    // function to calculate minimum cost
void printPath(int num, int *pre, int start, int dest);             // print path according to start and desitanation

int main(void)
{
    int i, j;
    int num, pairs;
    int *dis, *pre, **len;
    char start, destination, c1, c2;
    
    scanf("%d %d\n", &num, &pairs);     // the following sotre input
    scanf("%c\n", &start);
    scanf("%c\n", &destination);
    dis = new int[num];                 // distance from start point to other points
    pre = new int[num];                 // previous point
    len = new int *[num];               // lengths of every pairs of points
    for(i = 0; i < num; i++){
        len[i] = new int[num];
    }
    for(i = 0; i < num; i++){           // initialize length, -1 represents infinity
        for(j = 0; j < num; j++){
            len[i][j] = -1;
        }
    }
    for(i = 0; i < pairs; i++){         // input distance of pairs
        scanf("%c %c %d\n", &c1, &c2, &j);
        len[c1 - 'A'][c2 - 'A'] = j;
    }
    minCost(pre, len, dis, num, start - 'A');   // calculate min cost
    printf("%d\n", dis[destination - 'A']);     // print cost
    printPath(num, pre, start - 'A', destination - 'A');    // print path
    return 0;
}

void minCost(int *pre, int **len, int *dis, int num, int start)
{
    int *visted = new int[num];
    int i, j, index, min;
    
    for(i = 0; i < num; i++){       // initialization
        visted[i] = 0;              // set S = if this point is visted
        dis[i] = len[start][i];     // distance from start to i
        if(dis[i] != -1){
            pre[i] = start;         // record the previous point if it is conneted to start point
        }
    }
    visted[start] = 1;              // start point is visted
    dis[start] = 0;                 // dis of start point = 0
    for(i = 0; i < num - 1; i++){
        min = 0;                    // find the unvisted point with minimum distance from start point
        for(j = 0; j < num; j++){
            if(visted[j] == 0 && dis[j] != -1 && (min > dis[j] || min == 0)){
                index = j;          // record the index of interested point
                min = dis[j];
            }
        }
        visted[index] = 1;          // the index point is visted
        for(j = 0; j < num; j++){   // update the distance of each point connected to index point
            if(len[index][j] > 0){
                if(visted[j] == 0 && (dis[index] + len[index][j] < dis[j] || dis[j] == -1)){
                    dis[j] = dis[index] + len[index][j];
                    pre[j] = index;     // update the previous point to index point
                }
            }
        }
    }
    return;
}

void printPath(int num, int *pre, int start, int dest)
{
    int i, j, *path = new int[num];
    
    path[num - 1] = dest;           // final point is destination point
    path[0] = start;                // first point is start point
    for(i = num - 2, j = dest; i > 0; i--){ // initialize j to destination point
        path[i] = pre[j];           // path[i] is the previous point of j
        j = path[i];                // update j to path[i]
        if(path[i] == start){       // check if the path is completed
            break;
        }
    }
    for(j = i; j < num ; j++){      // print the path
        if(j != num - 1){
            printf("%c ", 'A' + path[j]);
        }
        else{
            printf("%c", 'A' + path[j]);
        }
        
    }
    delete [] path;
}