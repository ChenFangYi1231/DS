/*
 * 1. This Program is Developed Solely by Myself: Yes
 * 2. Student ID: 107061207
 * 3. OJ ID: DS2107061207
 * 4. OJ SID: 2186737
 * 5. OJ Score: 10
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// structure to record the state of a person
struct person{
        int row, col, date, recovery;
        // 0:healthy, 1:masked, 2:infected, 3: sick, 4:ICU, 5:dead, 6:recover and infected
        int state;
        int dieCount, flag, inft;   // 1. count for die, 2. record infect other or not, 3. infected time
        int printed;                // be printed or not
        char name[20];
};
float count;        // number of survivors
void simulation(struct person *people, int time, int *ICU, int num);        // function to change state of people
int surrounded(struct person *people, int index, int time, int num);        // check if the people[index] is surrounded by 4 sickers

int main(void)
{
    int r, c, ICU, t, num;
    int i, j, read, row, col, index;
    char s[10];
    struct person *people;          // data of all people

    /* the following record all the input */
    scanf("%d %d %d %d %d", &r, &c, &ICU, &t, &num);
    count = num;
    people = (struct person *)malloc(num * sizeof(struct person));
    for(i = 0; i < num; i++){
        scanf("%d %d %d ", &people[i].date, &people[i].row, &people[i].col);
        scanf("%s %s ", people[i].name, s);
        people[i].dieCount = 0;
        people[i].flag = 0;
        people[i].printed = 0;
        if(strcmp(s, "Sick") == 0){
            people[i].recovery = 15;
            people[i].state = 3;
        }
        else if(strcmp(s, "Healthy") == 0){
            people[i].recovery = 0;
            people[i].state = 0;
        }
        else{
            people[i].recovery = 0;
            people[i].state = 1;
        }
    }
    /* simulate the cell for given time */
    for(i = 0; i < t; i++){
        simulation(people, i, &ICU, num);
    }
    /* the following print the output */
    printf("%.2f%%\n", count / num * 100);
    for(i = 0; i < num; i++){
		if(people[i].state != 4 && people[i].state != 5){
			read = i;       // record the last people needed to be printed
		}
	}
    for(j = 0, row = r, col = c; j < num; j++){
        for(i = 0; i < num; i++){
            if(people[i].row <= row && people[i].printed == 0){
                row = people[i].row;
            }
        }
        for(i = 0; i < num; i++){
            if(people[i].row == row && people[i].col < col && people[i].printed == 0){
                index = i;
                col = people[i].col;
            }
        }
        if(j != read && people[index].state != 4 && people[index].state != 5){
            printf("%s ", people[index].name);
        }
        else if(people[index].state != 4 && people[index].state != 5){
            printf("%s", people[index].name);
        }
        people[index].printed = 1;
        row = r;
        col = c;
    }  
    return 0;
}

void simulation(struct person *people, int time, int *ICU, int num)
{
    int i, j;
    int r1, c1, r2, r3 , c3, c4, c;

    for(i = 0; i < num && people[i].date <= time; i++){
        if(people[i].state == 3){
            /* if the person is sick, add recovery time to others according to different infected / sick time */
            if((people[i].inft - time == -2 && people[i].flag == 1) || people[i].flag == 2){
				r1 = people[i].row - 1;
            	c1 = people[i].col;
            	r2 = people[i].row + 1;
            	r3 = people[i].row ;
            	c3 = people[i].col - 1;
            	c4 = people[i].col + 1;
				if(people[i].flag == 2){
					c = 0;
					for(j = 0; j <= num && people[j].date <= time; j++){
						if(people[j].row == r1 && people[j].col == c1 && people[j].state == 3 && people[j].inft != time - 1){
                    		c++;
                		}
                		else if(people[j].row == r2 && people[j].col == c1 && people[j].state == 3 && people[j].inft != time - 1){
                    		c++;
                		}
                		else if(people[j].row == r3 && people[j].col == c3 && people[j].state == 3 && people[j].inft != time - 1){
                    		c++;
                		}
                		else if(people[j].row == r3 && people[j].col == c4 && people[j].state == 3 && people[j].inft != time - 1){
                   			c++;
                		}
            		}
            		if(c != 0){     // calculate sick neighbors for recovery time
                		people[i].recovery = 14 + 7 * c;
            		}
				}
                for(j = 0; j <= num && people[j].date <= time; j++){
                    if(people[j].row == r1 && people[j].col == c1){
                        if(people[j].state == 3){
                            people[j].recovery += 7;
                        }
                    }
                    else if(people[j].row == r2 && people[j].col == c1){
                        if(people[j].state == 3){
                            people[j].recovery += 7;
                        }
                    }
                    else if(people[j].row == r3 && people[j].col == c3){
                        if(people[j].state == 3){
                            people[j].recovery += 7;
                        }
                    }
                    else if(people[j].row == r3 && people[j].col == c4){
                        if(people[j].state == 3){
                            people[j].recovery += 7;
                        }
                    }
                }
                people[i].flag = 0;     // add recovery time once
            }
            people[i].recovery--;       // recovery time - 1
            if(people[i].recovery == 0){
                people[i].state = 6;    // if recovey time = 0, check if there are sick neighbors
            }
            
            if(surrounded(people, i, time, num)){
                people[i].dieCount++;           // if surrounded = 1, dieCount + 1
                if(people[i].dieCount == 7){    // check if the person is dead
                    people[i].state = 5;
                    count -= 1;                 // survivors - 1
                }
            }
        }
    }
    for(i = 0; i <= num && people[i].date <= time; i++){
        if(people[i].date == time && people[i].state == 3){     // insert a sick person -> infect others
            r1 = people[i].row - 1;
            c1 = people[i].col;
            r2 = people[i].row + 1;
            r3 = people[i].row ;
            c3 = people[i].col - 1;
            c4 = people[i].col + 1;
            people[i].flag = 2;
            for(j = 0; j <= num && people[j].date <= time; j++){
                if(people[j].row == r1 && people[j].col == c1){
                    if(people[j].state == 0){
                        people[j].state = 6;
                    }
                }
                else if(people[j].row == r2 && people[j].col == c1){
                    if(people[j].state == 0){
                        people[j].state = 6;
                    }
                }
                else if(people[j].row == r3 && people[j].col == c3){
                    if(people[j].state == 0){
                        people[j].state = 6;
                    }
                }
                else if(people[j].row == r3 && people[j].col == c4){
                    if(people[j].state == 0){
                        people[j].state = 6;
                    }
                }
            }
        }    
        else if(people[i].date == time && people[i].state == 0){    // insert a healthy person -> check if there are sick neighbors
            c = 0;
            r1 = people[i].row - 1;
            c1 = people[i].col;
            r2 = people[i].row + 1;
            r3 = people[i].row ;
            c3 = people[i].col - 1;
            c4 = people[i].col + 1;
            for(j = 0; j <= num && people[j].date <= time; j++){
                if(people[j].row == r1 && people[j].col == c1 && people[j].state == 3){
                    c++;
                }
                else if(people[j].row == r2 && people[j].col == c1 && people[j].state == 3){
                    c++;
                }
                else if(people[j].row == r3 && people[j].col == c3 && people[j].state == 3){
                    c++;
                }
                else if(people[j].row == r3 && people[j].col == c4 && people[j].state == 3){
                    c++;
                }
            }
            if(c != 0){
                people[i].state = 6;
            }
        }
        else if(people[i].state == 2){      // infected yesterday -> change state to sick and infect others
            people[i].state = 3;
            r1 = people[i].row - 1;
            c1 = people[i].col;
            r2 = people[i].row + 1;
            r3 = people[i].row ;
            c3 = people[i].col - 1;
            c4 = people[i].col + 1;
            for(j = 0; j <= num && people[j].date <= time; j++){
                if(people[j].row == r1 && people[j].col == c1){
                    if(people[j].state == 0){
                        people[j].state = 6;
                    }
                }
                else if(people[j].row == r2 && people[j].col == c1){
                    if(people[j].state == 0){
                        people[j].state = 6;
                    }
                }
                else if(people[j].row == r3 && people[j].col == c3){
                    if(people[j].state == 0){
                        people[j].state = 6;
                    }
                }
                else if (people[j].row == r3 && people[j].col == c4){
                    if(people[j].state == 0){
                        people[j].state = 6;
                    }
                }
            }
        }
        
    }
    for(i = 0; i < num && people[i].date <= time; i++){
        if(people[i].state == 6){       // infected today -> calulate recovery time according to neighbors
            c = 0;
            r1 = people[i].row - 1;
            c1 = people[i].col;
            r2 = people[i].row + 1;
            r3 = people[i].row ;
            c3 = people[i].col - 1;
            c4 = people[i].col + 1;
            for(j = 0; j < num && people[j].date <= time; j++){
                if(people[j].row == r1 && people[j].col == c1 && people[j].state == 3){
                    c++;
                }
                else if(people[j].row == r2 && people[j].col == c1 && people[j].state == 3){
                    c++;
                }
                else if(people[j].row == r3 && people[j].col == c3 && people[j].state == 3){
                    c++;
                }
                else if(people[j].row == r3 && people[j].col == c4 && people[j].state == 3){
                    c++;
                }
            }
            if(c != 0){     // more than 1 sick neghibors -> infected -> initialize other data
                people[i].state = 2;
                people[i].dieCount = 1;
                people[i].recovery = 14 + 7 * c;
                people[i].inft = time;
                people[i].flag = 1;
            }
            else{           // otherwise the person recover
                people[i].state = 0;
                people[i].dieCount = 1;
            }
        }
        else if(people[i].state == 3){      // check if a sick person needs to go to ICU
            if(people[i].recovery > 28 && (*ICU) > 0){
                people[i].state = 4;
                (*ICU) -= 1;
            }
        }
    }
}

int surrounded(struct person *people, int index, int time, int num)
{
    int j, r1, c1, r2, r3 , c3, c4, count = 0;      // count : number of sick neighbors

    r1 = people[index].row - 1;
    c1 = people[index].col;
    r2 = people[index].row + 1;
    r3 = people[index].row ;
    c3 = people[index].col - 1;
    c4 = people[index].col + 1;
    for(j = 0; j <= num && people[j].date <= time; j++){
        if(people[j].row == r1 && people[j].col == c1 && people[j].state == 3){
            count++;
        }
        else if(people[j].row == r2 && people[j].col == c1 && people[j].state == 3){
            count++;
        }
        else if(people[j].row == r3 && people[j].col == c3 && people[j].state == 3){
            count++;
        }
        else if(people[j].row == r3 && people[j].col == c4 && people[j].state == 3){
            count++;
        }
    }
    if(count == 4){     // there are 4 sick neighbors -> return 1
        return 1;
    }
    else{               // otherwise, return 0
        return 0;
    }
}