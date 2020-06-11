/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 107061207
 * 3. OJ ID: DS2107061207
 * 4. OJ SID: 2260784
 * 5. OJ Score: 10
 */

#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h> 
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

struct node{

    char type;
    int visted;
    int correct;
    int direct;
    int path;
};

struct value{
    int L1, N1, N2, level;
    float L2;
    int num;
};

int deadend(struct node **maze, int row, int col, int r, int c);
void findPath(struct node **maze, int row, int col);
void evalute(struct node **maze, struct value *v, int row, int col);
void sorting(struct value v[], int num);
bool compare(struct value a, struct value b);
void print(struct node **m, struct value *v, int row, int col);

int main(void)
{
    int num, w, h, numMaze;
    int i, j, k;
    char ch;
    node **maze;
    value *mazeLevel;

    scanf("%d\n", &num);
    mazeLevel = new value[num];
    
    for(i = 0; i < num; i++){

        scanf("%d\n%d %d\n", &numMaze, &w, &h);
        maze = new node*[h];
        for(j = 0; j < h; j++){
            maze[j] = new node[w];
        }
        
        for(j = 0; j < h; j++){
            for(k = 0; k < w; ){
                scanf("%c ", &ch);
                if(ch == 'N' || ch == '.'){
                    maze[j][k].type = ch;
                    maze[j][k].visted = 0;
                    maze[j][k].direct = 0;
                    maze[j][k].correct = 0;
                    maze[j][k].path = 0;
                    k++;
                }
                
            }
        }
        findPath(maze, h, w);
        evalute(maze, &(mazeLevel[numMaze - 1]), h, w);
        mazeLevel[numMaze - 1].num = numMaze;
        for(j = 0; j < h; j++){
            delete [] maze[j];
        }
    }
    sorting(mazeLevel, num);
    return 0;
}

void findPath(struct node **maze, int row, int col)
{
    stack <int> r;
    stack <int> c;
    int cur_r = 1, cur_c = 0, L1;;
    int next_r, next_c;
    
    r.push(cur_r);
    c.push(cur_c);
    while(!r.empty()){
        maze[cur_r][cur_c].correct = 0;
        cur_r = r.top();
        cur_c = c.top();
        maze[cur_r][cur_c].correct = 1;
        r.pop();
        c.pop();
        while(maze[cur_r][cur_c].direct < 4){
            if(maze[cur_r][cur_c].direct == 0 && cur_c != col - 1){
                next_r = cur_r;
                next_c = cur_c + 1;
            }
            else if(maze[cur_r][cur_c].direct == 1){
                next_r = cur_r + 1;
                next_c = cur_c ;
            }
            else if(maze[cur_r][cur_c].direct == 2 && cur_c != 0){
                next_r = cur_r;
                next_c = cur_c - 1;
            }
            else if(maze[cur_r][cur_c].direct == 3){
                next_r = cur_r - 1;
                next_c = cur_c;
            }
            maze[cur_r][cur_c].direct++;
            if(next_r == row - 2 && next_c == col - 1){
                maze[cur_r][cur_c].correct = 1;
                maze[next_r][next_c].correct = 1;
                return;
            }
            if(maze[next_r][next_c].type == '.' && maze[next_r][next_c].visted == 0){
                maze[cur_r][cur_c].correct = 1;
                r.push(cur_r);
                c.push(cur_c);
                cur_r = next_r;
                cur_c = next_c;
                maze[cur_r][cur_c].visted = 1;
            } 
        }
    }
}

int deadend(struct node **maze, int row, int col, int r, int c)
{
    int result = 0;

    if(maze[r - 1][c].type != '.' || maze[r - 1][c].visted == 1){
        result++;
    }
    if(maze[r + 1][c].type != '.' || maze[r + 1][c].visted == 1){
        result++;
    }
    if(c != 0){
        if(maze[r][c - 1].type != '.' || maze[r][c - 1].visted == 1){
            result++;
        }
    }
    if(c != col - 1){
        if(maze[r][c + 1].type != '.' || maze[r][c + 1].visted == 1){
            result++;
        }
    }
    if(result == 4){
        return 1;
    }
    else if(c == col - 1 && result == 3){
        return 1;
    }
    else if(c == 0 && result == 3){
        return 1;
    }
    return 0;
    
}

void evalute(struct node **maze, struct value *v, int row, int col)
{
    int i, j, L1 = 0, L2 = 0, N1 = 0, N2 = 0;
    int count, *p1, max, index;
    int cur_r, cur_c, next_r, next_c;
    stack <int> r;
    stack <int> c;
    queue <int> path;

    for(i = 1; i < row - 1; i++){
        for(j = 0; j < col; j++){
            maze[i][j].visted = 0;
            maze[i][j].direct = 0;
            if(maze[i][j].type == '.' && maze[i][j].correct == 1){
                L1++;
                if(maze[i - 1][j].type == '.' && maze[i - 1][j].correct == 0){
                    r.push(i);
                    c.push(j);
                    N1++;
                }
                if(maze[i + 1][j].type == '.' && maze[i + 1][j].correct == 0){
                    r.push(i);
                    c.push(j);
                    N1++;
                }
                if(j != col - 1){
                    if(maze[i][j + 1].type == '.' && maze[i][j + 1].correct == 0){
                        r.push(i);
                        c.push(j);
                        N1++;
                    }
                }
                if(j != 0){
                    if( maze[i][j - 1].type == '.' && maze[i][j - 1].correct == 0){
                        r.push(i);
                        c.push(j);
                        N1++;
                    }
                }
            }
        }
    }

    while(!r.empty()){
        count = 0;
        index = 0;
        cur_r = r.top();
        cur_c = c.top();
        
        count = maze[cur_r][cur_c].path;
        r.pop();
        c.pop();
        while(maze[cur_r][cur_c].direct < 4){
            if(maze[cur_r][cur_c].direct == 0 && cur_c != col - 1){
                next_r = cur_r;
                next_c = cur_c + 1;
            }
            else if(maze[cur_r][cur_c].direct == 1){
                next_r = cur_r + 1;
                next_c = cur_c ;
            }
            else if(maze[cur_r][cur_c].direct == 2 && cur_c != 0){
                next_r = cur_r;
                next_c = cur_c - 1;
            }
            else if(maze[cur_r][cur_c].direct == 3){
                next_r = cur_r - 1;
                next_c = cur_c;
            }
            maze[cur_r][cur_c].direct++;
            if(maze[next_r][next_c].type == '.' && maze[next_r][next_c].visted == 0 && !maze[next_r][next_c].correct){
                maze[cur_r][cur_c].visted = 1;
                maze[cur_r][cur_c].path = count;
                r.push(cur_r);
                c.push(cur_c);
                cur_r = next_r;
                cur_c = next_c;
                maze[cur_r][cur_c].visted = 1;
                count++;
                index = 1;
            }
            
        }
        if(index && maze[cur_r][cur_c].correct == 0 && deadend(maze, row, col, cur_r, cur_c)){     
            path.push(count);
            N2++;
            maze[cur_r][cur_c].path = count;
        }
        
    }
    if(N2 > 0){
        p1 = new int[N2];
        for(i = 0; i < N2; i++){
            p1[i] = path.front();
            path.pop();
        }
        for(i = 0; i < N2; i++){
            max = 0;
            for(j = i; j < N2; j++){
                if(p1[j] > max){
                    index = j;
                    max = p1[j];
                }
            }
            p1[index] = p1[i];
            p1[i] = max;
        }
    
        if(N2 % 2 == 0){
            L2 = (p1[N2 / 2] + p1[N2 / 2 - 1]) / 2.0;
        }
        else{
            L2 = p1[(int) N2 / 2];
        }
    }
    else{
        L2 = 0;
    }
    v->L1 = L1 - 1;
    v->L2 = L2;
    v->N1 = N1;
    v->N2 = N2;
    v->level = (N1 + N2) * (L1 - 1 + L2);
    delete [] p1;
}

void sorting(struct value v[], int num)
{
    int i, j, min, index;
    struct value temp;

    sort(v, v + num,compare);
    for(i = num - 1; i >= 0; i--){
        printf("%d\n", v[i].num);
        printf("%d %d %d %d %g\n", v[i].level, v[i].N1, v[i].N2, v[i].L1, v[i].L2);
    }
}

bool compare(struct value a, struct value b)
{
    if(a.level != b.level)
        return a.level > b.level;
    if(a.N1 != b.N1)
        return a.N1 > b.N1;
    if(a.N2 != b.N2)
        return a.N2 > b.N2;
    if(a.L1 != b.L1)
        return a.L1 > b.L1;
    if(a.L2 != b.L2)
        return a.L2 > b.L2;
    
    return a.num > b.num;
}

void print(struct node **m, struct value* v, int row, int col)
{
    int i, j;

    printf("%d %d %d %f %d\n", v->N1, v->N2, v->L1, v->L2, v->level);
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            printf("%c ", m[i][j].type);
        }
        printf("\n");
    }
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            printf("%d ", m[i][j].correct);
        }
        printf("\n");
    }
}