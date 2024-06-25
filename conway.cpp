#include <stdio.h>
#include <windows.h>

using namespace std;

#define N 31
const char c = (char)254;

//Display board
void showBoard(char b[N][N]){
    // printf("-----------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%c",b[i][j]);
        }
        printf("\n");
    }
    printf("\r");
    // printf("-----------------------------------------------------------------------------------------------------------\n");
}

//Count the live neighbors of a cell at board[i][j]
int countLiveNeighbors(char b[N][N],int i, int j){
    int num = 0;
    
    if(b[i-1][j] == c){num++;}
    if(b[i+1][j] == c){num++;}
    if(b[i][j-1] == c){num++;}
    if(b[i][j+1] == c){num++;}
    if(b[i-1][j-1] == c){num++;}
    if(b[i+1][j-1] == c){num++;}
    if(b[i-1][j+1] == c){num++;}
    if(b[i+1][j+1] == c){num++;}

    return num;
}

//Returns true if the cell at board[i][j] is alive. Else, false
bool isLive(char b[N][N], int i, int j){
    if(b[i][j]==c){return true;}
    else{return false;}
}

/* Updates the board and population for one generation.
 * Passes through the board twice:
    Pass 1: Counts live neighbors for each cell and stores it in table t
    Pass 2: Updates each cell on the board b based on the c'sgol rules and the corresponding value in t
 */
void generate(char b[N][N], int t[N][N], int &pop){
    int n = N;
    for(int i = 1; i<n-1; i++){
        for(int j = 1; j<n-1; j++){
            t[i][j] = countLiveNeighbors(b,i,j);
        }
    }

    for(int i = 1; i<n-1; i++){
        for(int j = 1; j<n-1; j++){
            if(isLive(b,i,j)){
                //rule 1: a live cell with < 2 live neighbors will die (underpopulation)
                if(t[i][j]<2){b[i][j] = ' ';pop--;continue;}
                //rule 2: a live cell with 2 or 3 live neighbors will survive
                if(t[i][j]==2 || t[i][j]==3){continue;}
                //rule 3: a live cell with > 3 live neighbors will die (overpopulation)
                if(t[i][j]>3){b[i][j] = ' ';pop--;continue;}
                
            }
            else{
                //rule 4: a dead cell with 3 live neighbors will become alive (reproduction)
                if(t[i][j]==3){b[i][j] = c;pop++;continue;}
            }  
        }
    }
}

void setup(char b[N][N], int &pop){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            b[i][j] = ' ';
        }
    }

    //starting population

    //Glider
    b[6][6] = c;
    b[6][5] = c;
    b[6][7] = c;
    b[5][7] = c;
    b[4][6] = c;

    //another glider
    b[6+5][6] = c;
    b[6+5][5] = c;
    b[6+5][7] = c;
    b[5+5][7] = c;
    b[4+5][6] = c;

    // 4 blinker generator
    // b[11][13] = c;
    // b[12][13] = c;
    // b[13][13] = c;
    // b[14][13] = c;
    // b[15][13] = c;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(isLive(b,i,j)){pop++;}
        }
    }

    
}



//Driver Code
int main(){
    //Change the population and the maximum number of generations to simulate
    int population = 0;
    int maxGen = 100;
    unsigned delay = 100;

    char board[N][N] = {' '};
    int ntable[N][N] = {0};

    //Initialize board
    setup(board,population);
    int gen = 0;

    //loop to run simulation
    while(gen <= maxGen){
        printf("Population: %d          Generation: %d\n", population, gen);
        showBoard(board);

        printf("\r");
        fflush(stdout);

        generate(board,ntable, population);
        Sleep(delay);

        if(population==0){break;}
        
        gen++;
    }

    return 0;
}