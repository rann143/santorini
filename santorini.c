#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void printBoard (int r, int c, char board[][c]) {
    // Print Column numbers
    for (int i = 0; i < 7; i++) {
        if (i == 0) {
            printf("  ");
        } else {
            printf("%d ", i);
        }
    }

    printf("\n");

    for (int i = 0; i < r; i++)
    {
        // Print Row numbers
        printf("%d ", i + 1);

        // Print board
        for (int j = 0; j < c; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
        }
}

typedef struct {
        int r;
        int c;
} Coordinate;

Coordinate pickStart() {
    int r, c;
    int size = 6;
    Coordinate result;
    printf("Pick Your Starting Position: (X Y coordinates): \n");
    scanf("%d %d", &r, &c); 

    if ((r >= 0 && r <= size) && (c >= 0 && c <= size)) {
        printf("Placed at %d %d\n", r, c);
        result.r = r - 1;
        result.c = c - 1;
        return result;
    }
    else
    {
        printf("Out of bounds. Try again: \n");
        return pickStart();
    }
}

Coordinate pickAIStart(Coordinate pCoor) {
    Coordinate result;
    int random_r;
    int random_c;

    srand(time(NULL));
    int maxR = (pCoor.r + 1 > 5) ? 5 : pCoor.r + 1;
    int maxC = (pCoor.c + 1 > 5) ? 5 : pCoor.c + 1;

    int minR = (pCoor.r - 1 < 0) ? 0 : pCoor.r - 1;
    int minC = (pCoor.c - 1 < 0) ? 0 : pCoor.c - 1;
    
    do {
       random_r = (rand() % (maxR - minR + 1)) + minR;
       random_c = (rand() % (maxC - minC + 1)) + minC;
    } while (random_r == pCoor.r && random_c == pCoor.c);


        result.r = random_r;
        result.c = random_c;
        return result;
}

// This function isn't really needed, we can just create a global variable hasFinished
bool hasFinished(int r, int c, char board[][c]) {
    int towersFinished = 0;
    int towersCrushed = 0;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (board[i][j] - '0' == 4) {
                towersFinished++;
            }

            if (board[i][j] - '0' == 0) {
                towersCrushed++;
            }
        }
    }

    if (towersCrushed >= 10 || towersFinished >= 10) {
        return true;
    } else {
        return false;
    }
}

Coordinate playerMove(Coordinate pCoor, Coordinate aiCoor) {
    int r, c;
    int size = 6;
    Coordinate result;

    int maxR = (pCoor.r + 1 >= size) ? size - 1 : pCoor.r + 1;
    int maxC = (pCoor.c + 1 >= size) ? size - 1 : pCoor.c + 1;

    int minR = (pCoor.r - 1 < 0) ? 0 : pCoor.r - 1;
    int minC = (pCoor.c - 1 < 0) ? 0 : pCoor.c - 1;

    printf("Pick Your Move: (Row Col coordinates): \n");
    scanf("%d %d", &r, &c);
    r--;
    c--;
    printf("chose: %d %d\n", r, c);
    printf("prev: %d %d\n", pCoor.r, pCoor.c);

    if (!(r <= maxR && r >= minR)) {
        printf("r NOT in range\n");
    };
    if (!(c <= maxC && c >= minC)) {
        printf("c NOT in range\n");
    };
    if ((r == pCoor.r && c == pCoor.c)) {
        printf("rc is same as current\n");
    };
    if ((r == aiCoor.r && c == aiCoor.c)) {
        printf("rc is in ai location\n");
    };

    if ((r <= maxR && r >= minR) && (c <= maxC && c >= minC) && (r != pCoor.r || c != pCoor.c) && (r != aiCoor.r || c != aiCoor.c)) {
        printf("Placed at %d %d\n", r, c);
        result.r = r;
        result.c = c;
        return result;
    }
    else
    {
        printf("Out of bounds. Try again: \n");
        return playerMove(pCoor, aiCoor);
    }
}

// Coordinate aiMove() {

// }

int main (void) {
    char board[6][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            board[i][j] = '2';
        }
    }

    bool hasFinished = false;

    printBoard(6, 6, board);

    Coordinate currentCoor = pickStart();
    char value = board[currentCoor.r][currentCoor.c];
    board[currentCoor.r][currentCoor.c] = 'P';
    Coordinate aiStartingCoor = pickAIStart(currentCoor);
    board[aiStartingCoor.r][aiStartingCoor.c] = 'A';

    printBoard(6, 6, board);

    do {
        Coordinate prev = currentCoor;
        currentCoor = playerMove(currentCoor, aiStartingCoor);

        int newNum = (value - '0') + 1;
        board[prev.r][prev.c] = newNum + '0';
        value = board[currentCoor.r][currentCoor.c];
        
        board[currentCoor.r][currentCoor.c] = 'P';
        printBoard(6, 6, board);
    } while (hasFinished == false);

        printf("Done!\n");

    // do {
    //     // player move
    //     // update board
    //     // check if player won
    //     // ai move
    //     // update board
    //     // check if ai won
    // } while (/*hasFinished == false*/)

    return 0;
}

