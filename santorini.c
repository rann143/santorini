#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void printBoard (int r, int c, char board[][c]) {
    // Print Column numbers
    for (int i = 0; i < 7; i++) {
        if (i == 0) {
            printf("    ");
        } else {
            printf("%d ", i);
        }
    }

    printf("\n");
    printf("\n");

    for (int i = 0; i < r; i++)
    {
        // Print Row numbers
        printf("%d   ", i + 1);

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
bool checkHasFinished(int r, int c, char board[][c]) {
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

int announceWinner(int r, int c, char board[][c]) {
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

    if (towersFinished >= 10) {
        printf("You've won!\n Towers Completed: %d\n Towers Destroyed: %d\n", towersFinished, towersCrushed);
        return 0;
        }
    else
    {
        printf("You LOST YOU LOST\n Towers Completed: %d\n Towers Destroyed: %d\n", towersFinished, towersCrushed);
        return 0;
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

Coordinate aiMove(Coordinate pCoor, Coordinate aiCoor) {
    Coordinate result;
        int random_r;
        int random_c;

        srand(time(NULL));
        int maxR = (aiCoor.r + 1 > 5) ? 5 : aiCoor.r + 1;
        int maxC = (aiCoor.c + 1 > 5) ? 5 : aiCoor.c + 1;

        int minR = (aiCoor.r - 1 < 0) ? 0 : aiCoor.r - 1;
        int minC = (aiCoor.c - 1 < 0) ? 0 : aiCoor.c - 1;
        
        do {
        random_r = (rand() % (maxR - minR + 1)) + minR;
        random_c = (rand() % (maxC - minC + 1)) + minC;
        } while ((random_r == aiCoor.r && random_c == aiCoor.c) || (random_r == pCoor.r && random_c == pCoor.c));


            result.r = random_r;
            result.c = random_c;
            return result;
}

void updateSquaresPlayer(int r, int c, char board[][c], int updatedValue, Coordinate playerPos, Coordinate aiPos) {
    for (int i = 0; i < 6; i++) {

        for (int j = 0; j < 6; j++) {
            if (i == playerPos.r && (i != playerPos.r || j != playerPos.c) && (i != aiPos.r || j != aiPos.c)) {
                board[i][j] = updatedValue;
                char tmp = board[i][j];
                
            }
            if (j == playerPos.c && (i != playerPos.r || j != playerPos.c) && (i != aiPos.r || j != aiPos.c)) {
                board[i][j] = updatedValue;
                char tmp = board[i][j];
                
            }

            if ((abs(playerPos.r - i) == abs(playerPos.c - j)) && (i != playerPos.r || j != playerPos.c) && (i != aiPos.r || j != aiPos.c)){
               board[i][j] = updatedValue; 
            }
        }
    }
    printf("\n");
}

void updateSquaresAI(int r, int c, char board[][c], Coordinate playerPos, Coordinate aiPos) {
    for (int i = 0; i < 6; i++) {

        for (int j = 0; j < 6; j++) {
            int currentCoorValue = board[i][j] - '0';
            char updatedValue = (currentCoorValue - 1) < 0 ? '0' : (currentCoorValue - 1) + '0';
            if (i == aiPos.r && (i != playerPos.r || j != playerPos.c) && (i != aiPos.r || j != aiPos.c))
            {
                board[i][j] = updatedValue;
                char tmp = board[i][j];
            }
            if (j == aiPos.c && (i != playerPos.r || j != playerPos.c) && (i != aiPos.r || j != aiPos.c)) {
                board[i][j] = updatedValue;
                char tmp = board[i][j];
                
            }

            if ((abs(aiPos.r - i) == abs(aiPos.c - j)) && (i != playerPos.r || j != playerPos.c) && (i != aiPos.r || j != aiPos.c)){
               board[i][j] = updatedValue; 
            }
        }
    }
    printf("\n");
}

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
    Coordinate aiCoor = pickAIStart(currentCoor);
    char aiValue = board[aiCoor.r][aiCoor.c];
    board[aiCoor.r][aiCoor.c] = 'A';

    printBoard(6, 6, board);

    do {
        
        Coordinate prev = currentCoor;
        currentCoor = playerMove(currentCoor, aiCoor);

        char newNum = ((value - '0') + 1) > 4 ? '4' : ((value - '0') + 1)  + '0';
        board[prev.r][prev.c] = newNum;
        updateSquaresPlayer(6, 6, board, newNum, currentCoor, aiCoor);
        value = newNum;
        // printf("current value %c\n", value);

        board[currentCoor.r][currentCoor.c] = 'P';
        


        Coordinate aiPrev = aiCoor;
        aiCoor = aiMove(currentCoor, aiCoor);

        char newAiNum = ((aiValue - '0') - 1) < 0 ? '0' : ((aiValue - '0') - 1) + '0';
        
        updateSquaresAI(6, 6, board, currentCoor, aiCoor);
        board[aiPrev.r][aiPrev.c] = newAiNum;
        aiValue = newAiNum;
        board[aiCoor.r][aiCoor.c] = 'A';

        printBoard(6, 6, board);

        bool check = checkHasFinished(6, 6, board);
        if (check) {
            hasFinished = true;
        }
    } while (hasFinished == false);

        announceWinner(6, 6, board);
        char replay;
        printf("Would you like to play again? y/n:\n");
        scanf(" %c", &replay);

        if (replay == 'y') {
            printf("Starting New Game\n");
            return main();
        }
        else if (replay == 'n')
        {
            printf("Closing game. Restart to Play.\n");
            return 0;
        } else {
            printf("Invalid response. closing game; restart to play again\n");
            return 0;
        }

        return 0;
}

