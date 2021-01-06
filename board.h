#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

extern void * freshBoard(void); //sets up a fresh board 

extern void display(int * board); //displays the board

extern void flipChip (int move, int player, int * board, int direction);

extern void placeChipOnBoard (int move, int player, int * board);

extern void nextMove (int (* play) (int, int *), int player, int * board, int flag);

extern void coordinateGame (int (* blackPieceP1) (int, int *), int (* whitePieceP1) (int, int *), int flag);

extern void userInterface (void);

extern char getChip (int piece); //gets the chip symbol to display on board 

extern int getRival (int player); //returns opposite player

extern int getScore (int player, int * board); //itterates through board and counts chips of a given player 

extern int humanPlayer (int, int *); 

extern int * copyBoard (int * board); //makes copy of board

extern int isPlayValid (int move); //checks if move is in the scope 

extern int switchPlayer (int * board, int prevPlayer, int flag); //switches player

extern int findChip(int spot, int player, int * board, int direction); //takes openents chip and find a chip the same color

extern int checkPossibleFlip (int move, int player, int * board, int direction);

extern int isPlayLegal (int move, int player, int * board);

extern int isLegal (int player, int * board);

extern int EvaluateDifference (int player, int * board);