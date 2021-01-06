#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "board.h"

 int getRival (int player) {
  switch (player) {
    case 1: 
      return 2; 
    case 2: 
      return 1;
    default: printf("illegal\n"); 
    return 0;
  }
}

int getScore (int player, int * board) {
  int i, count;
  count = 0;
    for (i=1; i<=88; i++){
      if (board[i] == player){
            count++;
            }
    }    
  return count;
}


char getChip (int piece) {
  //0 = empty | [0] = * 
  //1 = black | [1] = b 
  //2 = white | [2] = w
  //          | [3] = ? error  
   static char chipSymbol[5] = "*bw?"; 
  return(chipSymbol[piece]);
}

int isPlayValid (int move) {
  if ((move >= 11) && (move <= 88) && (move%10 >= 1) && (move%10 <= 8)){
    return 1;
  } 
  else {
    return 0;
    }
}

int EvaluateDifference (int player, int * board) { 
  int i;
  int oppCount; 
  int playerCount;
  int opp;              
  int difference;  

  playerCount = 0; 
  oppCount = 0;                      
  opp = getRival(player); 

  //for loop that counts all the pieces for each player in the board
  for (i=1; i<=88; i++) {
    if (board[i] == player) playerCount++;
    if (board[i] == opp) oppCount++;
  }

  difference = playerCount - oppCount;

  //returns the piece difference between two playes 
  return (difference);
}
