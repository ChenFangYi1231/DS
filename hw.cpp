/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 107061207
 * 3. OJ ID: DS2107061207
 * 4. OJ SID: 2159236
 * 5. OJ Score: 12
 */
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

int result = 0;
class block{
    public:
        block(int r, int c, char *ch);
        int row, col;
        char *contains;
};

int match(block map, block puzzle, int cursor_r, int cursor_c);
block put(block map, block puzzle, int cursor_r, int cursor_c);
block Rotate(block p);
block flip(block p);
void solvePuzzle(block *puzzles, block pattern, int n_puzzle, int index);


int main(void)
{
    int i, j;
    int n_puzzle, n_map, row, col;
    char *ch, c;
    block *puzzles, *maps;

    cin>>n_puzzle;
    puzzles = (class block *) malloc(8 * n_puzzle * sizeof(class block));
    maps = (class block *) malloc(sizeof(class block));
    for(i = 0; i < n_puzzle; i++){
        cin>>col>>row;
        ch = new char[row * col];
        for(j = 0; j < col * row; ){
            cin>>c;
            if(c != '\n' && c !=' '){
                ch[j] = c;
                j++;
            }
        }
        puzzles[8 * i] = block(row, col, ch);
        puzzles[8 * i + 1] = Rotate(puzzles[8 * i]);
        puzzles[8 * i + 2] = Rotate(puzzles[8 * i + 1]);
        puzzles[8 * i + 3] = Rotate(puzzles[8 * i + 2]);
        puzzles[8 * i + 4] = flip(puzzles[8 * i]);
        puzzles[8 * i + 5] = flip(puzzles[8 * i + 1]);
        puzzles[8 * i + 6] = flip(puzzles[8 * i + 2]);
        puzzles[8 * i + 7] = flip(puzzles[8 * i + 3]);
        delete [] ch;
    }
    cin>>n_map;
    for(i = 0; i < n_map; i++){
        cin>>col>>row;
        ch = new char[row * col];
        for(j = 0; j < col * row; ){
            cin>>c;
            if(c != '\n' && c !=' '){
                ch[j] = c;
                j++;
            }
        }
        *maps = block(row, col, ch);
        delete [] ch;
        result = 0;
        solvePuzzle(puzzles, *maps, n_puzzle, 0);
        if(result){
            cout<<"Yes"<<endl;
        }
        else{
            cout<<"No"<<endl;
        }
    }
    
    delete [] maps;
    delete [] puzzles;
    return 0;
}

void solvePuzzle(block *puzzles, block pattern, int n_puzzle, int index)
{
    int i, j, k, flag;

    if(index == n_puzzle){
        for(i = 0, flag = 0; i < pattern.row * pattern.col && !flag; i++){
            if(pattern.contains[i] == '-'){
                flag = 1;
            }
        }
        if(!flag){
            result = 1;
        }
        return;
    }
	if(result){
		return;
	}
    for(k = 0; k < 8; k++){
        for(j = 0; j < pattern.col; j++){
            for(i = 0; i < pattern.row; i++){
                if(match(pattern, puzzles[8 * index + k], i, j)){
                    solvePuzzle( puzzles, put(pattern, puzzles[8 * index + k], i, j), n_puzzle, index + 1);
                }
            }
        }
    }
    return;
}

block::block(int r, int c, char *ch)
{
    int i;

    row = r;
    col = c;
    contains = new char[row * col];
    for(i = 0; i < row * col; i++){
        contains[i] = ch[i];
    }
}

block flip(block p)
{
    block *temp;
    char temp_ch1[p.row][p.col], temp_ch2[p.col * p.row];
    int i, j, count;

    for(i = 0,count = 0; i < p.row; i++){
        for(j = 0; j < p.col; j++){
            temp_ch1[p.row - i -1][j] = p.contains[count];
            count++;
        }
    }
    for(i = 0, count = 0; i < p.row; i++){
        for(j = 0; j < p.col; j++){
            temp_ch2[count] = temp_ch1[i][j];
            count++;
        }
    }
    temp = (class block*) malloc(sizeof(class block));
    *temp = block(p.row, p.col, temp_ch2);

    return *temp;
}

block Rotate(block p)
{
    block *temp;
    char temp_ch1[p.col][p.row], temp_ch2[p.col * p.row];
    int i, j, count;

    for(i = 0,count = 0; i < p.row; i++){
        for(j = 0; j < p.col; j++){
            temp_ch1[j][p.row - i - 1] = p.contains[count];
            count++;
        }
    }
    for(i = 0, count = 0; i < p.col; i++){
        for(j = 0; j < p.row; j++){
            temp_ch2[count] = temp_ch1[i][j];
            count++;
        }
    }
    temp = (class block *) malloc(sizeof(class block));
    *temp = block(p.col, p.row, temp_ch2);
    
    return *temp;
}


block put(block map, block puzzle, int cursor_r, int cursor_c)
{
    int i, j, p1, p4, count;
    block *temp;
    char *c;

    
    c = new char[map.row * map.col];
    p1 = cursor_r * map.col + cursor_c;
    p4 = (cursor_r + puzzle.row - 1) * map.col + (cursor_c + puzzle.col - 1);
    for(i = 0; i < map.col * map.row; i++){
        c[i] = map.contains[i];
    }
    temp = (class block *) malloc(sizeof(class block));
    *temp = block(map.row, map.col, c);
    for(i = p1, j = 0, count = 1; i <= p4; j++){
        if(map.contains[i] == '-' && puzzle.contains[j] == 'O')
            temp->contains[i] = 'V';
        if(count == puzzle.col){
            i = i + (map.col - puzzle.col) + 1;
            count = 1;
        }
        else{
            i++;
            count++;
        }
    }
    delete [] c;
    return *temp;
}

int match(block map, block puzzle, int cursor_r, int cursor_c)
{
    int i, j, p1, p4, count;

    if(map.row - cursor_r < puzzle.row || map.col - cursor_c < puzzle.col)
        return 0;
    p1 = cursor_r * map.col + cursor_c;
    p4 = (cursor_r + puzzle.row - 1) * map.col + (cursor_c + puzzle.col - 1);
    for(i = p1, j = 0, count = 1; i <= p4; j++){
        if((puzzle.contains[j] == 'O') && (map.contains[i] == 'V' || map.contains[i] == 'O'))
            return 0;
        
        else if(count == puzzle.col){
            i = i + (map.col - puzzle.col) + 1;
            count = 1;
        }
        else{
            i++;
            count++;
        }
    }
    return 1;
}