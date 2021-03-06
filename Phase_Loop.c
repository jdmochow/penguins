#include "Phase_Loop.h"
#include "Phase_Placement.h"
#include "Phase_Movement.h"
#include "Phase_Init.h"
#include "FileHandler.h"
#include "Define.h"
#include "System.h"

#include <string.h>

phase = PLACEMENT;
#ifdef INTERACTIVE
turn = 1;
#else
#endif // INTERACTIVE

void setPhase(char *P){
    if(strcmp(P, "movement") == 0) phase = MOVEMENT;
    if(strcmp(P, "placement") == 0) phase = PLACEMENT;
}

void Loop(){
#ifdef INTERACTIVE
    int x,y,z, penguinsCount, winner = 0;

    if(phase == PLACEMENT){
        Placement((turn % nrOfPlayers) + 1);

        clearscr();
        scorePrint();
        boardPrint();

        //each player used all his possible penguins => next phase
        if((getPenguins() == ((turn + 1) / nrOfPlayers)) && ((turn + 1) % nrOfPlayers == 0)) phase = MOVEMENT;
        turn++;
    }
    if(phase == MOVEMENT) {
        Movement((turn % nrOfPlayers) + 1);

        //clearscr();
        scorePrint();
        boardPrint();
        turn++;

        //calculate quantity of penguins on whole board
        penguinsCount = 0;
        for (z = 1; z <= nrOfPlayers; z++) {
            for (y = 0; y < BoardMY; y++) {
                for (x = 0; x < BoardMX; x++) {
                    if (board[x][y] == z + 3) {
                        penguinsCount++;
                    }
                }
            }
        }

        if(penguinsCount == 0)   {
            setRunning(0);
            /*
            clearscr();
            scorePrint();
            boardPrint();
            */
            printGameOver();

            for (z = 0; z < nrOfPlayers; z++) {
                if (score[z] > score[winner])
                    winner = z;
            }
            printf("\n\n\n\nThe winner is PLAYER %d with score %d!\n\n\n\n", winner + 1, score[winner]);
        }
    }
#else

    if(phase == PLACEMENT){
        Placement(turn + 1);
    } else if(phase == MOVEMENT){
        Movement(turn + 1);
    }
    turn++;
    setRunning(0);

#endif //INTERACTIVE
};

void printGameOver() {
            printf("  _____          __  __ ______    ______      ________ _____  \n"
                   " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n"
                   "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n"
                   "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / \n"
                   "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n"
                   " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\\n");
}
