#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define SIZE 100

const int DIRECTIONS[8]={-11, -10, -9, -1, 1, 9, 10, 11};

//values of the chips
const int AVAILABLE = 0;  //open spots have a value of 0
const int B = 1; //black chips have a value of 1
const int W = 2; //white chips have a value of 2
const int OUTER = 3; //outer chips have a value of 3



//we will evaluate the board with this score

const int WIN = 2000;         //W (win) will be the score a computer player will need to win 
const int L = -2000;        //L (loss) will be the score used to denote a loss


//This global variable will be used to keep count of the number of boards that get examined
//during the min max search. This variable is going to be used in the simulateMatch function 
//to get a visual representation of the results.

long int BOARDS;

void * freshBoard(void); //sets up a fresh board 
void display(int * board); //displays the board
void flipChip (int move, int player, int * board, int direction);
void placeChipOnBoard (int move, int player, int * board);
void nextMove (int (* play) (int, int *), int player, int * board, int flag);
void coordinateGame (int (* blackPieceP1) (int, int *), int (* whitePieceP1) (int, int *), int flag);
void userInterface (void);
char getChip (int piece); //gets the chip symbol to display on board 
int getRival (int player); //returns opposite player
int getScore (int player, int * board); //itterates through board and counts chips of a given player 
int humanPlayer (int, int *); 
int * copyBoard (int * board); //makes copy of board
int isPlayValid (int move); //checks if move is in the scope 
int switchPlayer (int * board, int prevPlayer, int flag); //switches player
int findChip(int spot, int player, int * board, int direction); //takes openents chip and find a chip the same color
int checkPossibleFlip (int move, int player, int * board, int direction);
int isPlayLegal (int move, int player, int * board);
int isLegal (int player, int * board);
int * legalBotMoves (int player, int * board);
int bot(int, int *);
int EvaluateDifference (int player, int * board);
int minMaxSearch (int player, int * board, int play, int (* evalFunc) (int, int *));
int maximum (int player, int * board, int play, int (* evalFunc) (int, int *));
int minimum (int player, int * board, int play, int (* evalFunc) (int, int *));
int lookAhead1(int, int *);
int lookAhead3(int, int *);
int lookAhead5(int, int *);
int weightedLookAhead1(int, int *);
int weightedLookAhead3(int, int *);
int weightedLookAhead5(int, int *);
int * randomizeBoard(void);
void simulateMatch (void);



//2D array. Going to use it to access what kind of game user wants to play 

void * GAME_TYPE[9][4] = {
   {"human", "human", humanPlayer}, //human player
   {"computer", "computer --> random gameplay ", bot},
   {"diff1", "computer --> 1 move look ahead |Easy| ", lookAhead1}, 
   {"diff3", "computer --> 3 move look ahead |Intermediate| ", lookAhead3},
   {"diff5", "computer --> 5 move look ahead |Hard| ", lookAhead5},
   {"weightDiff1", "computer --> WEIGHTED 1 move look ahead |Easy-Hard| ", weightedLookAhead1}, 
   {"weightDiff3", "computer --> WEIGHTED 3 move look ahead |Intermediate-Hard| ", weightedLookAhead3},
   {"weightDiff5", "computer --> WEIGHTED 5 move look ahead |Hard-HARD| youre going to lose", weightedLookAhead5},
   {NULL, NULL, NULL}
 };

typedef int (* fpc) (int, int *);

//if the current player is black --> value of 1, return 2 --> white
//return 1 when value of 2 is given 
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

//getScore() counts the number of chips each player has on the board
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



 //this method makes a copy of the board. 
 //mallocs space for a board. 
 //copies the value of the board it receives, stores it in a new poiter board
int * copyBoard (int * board) {
  int i;
  int * newBoard;
  newBoard = (int *)malloc(SIZE * sizeof(int));

  for (i=0; i<SIZE; i++) {
    newBoard[i] = board[i];
  }
  return newBoard;
}


void * freshBoard(void){ 

int i; //counter to create board 
int * othelloBoard; 
othelloBoard = (int *)malloc(SIZE * sizeof(int));


    //this for loop sets the spots on the board to 0, outer spots to 3
    for (i = 0; i<=9; i++){ 
        othelloBoard[i]=OUTER;
    } 
    for (i = 10; i<=89; i++){
        if (i%10 >= 1 && i%10 <= 8){
            othelloBoard[i]=AVAILABLE; 
        } 
        else{
            othelloBoard[i]=OUTER;
        } 
    }

    for (i = 90; i<=99; i++) {
        othelloBoard[i]=OUTER;
    }

  //Places 4 pieces in the center of the board, 2 black, 2 white diagonal to eachother. 
  othelloBoard[44]=W; 
  othelloBoard[45]=B; 
  othelloBoard[54]=B; 
  othelloBoard[55]=W;

  return othelloBoard;
}


//method to move player. takes player and board as parameters. Doesnt do much yet. 
int humanPlayer (int player, int * board) { 
  int move;
  printf("\n%c's turn, move must cause rival's chip to flip\nLocation example: 34\nHINT: trap the piece\n\nenter desired location:", getChip(player));
  scanf("%d", &move); //takes user input from terminal
  return move;
}

char getChip (int piece) {
  //0 = empty | [0] = * 
  //1 = black | [1] = b 
  //2 = white | [2] = w
  //          | [3] = ? error  
  static char chipSymbol[5] = "*bw?"; 
  return(chipSymbol[piece]);
}


//Method to display board 
void display(int * board){


int row; //row var
int col; // column var

printf("\n     1   2   3   4   5   6   7   8\n");
printf("   +---+---+---+---+---+---+---+---+\n");

//for loop that creates an 8 by 8 board 
    for(row=1; row<=8; row++){  
      printf("%d|  ", 10*row); //every row will print the number of the row multiplied by 10. y axis will go up by 10's
      for (col=1; col<=8; col++)
      printf("%c   ", getChip(board[col + (10 * row)])); //created a char array, [0] holds *, [1] holds b, [2] holds w. will return the correct chip on the board
    printf("\n");
    printf("   +---+---+---+---+---+---+---+---+\n");
    }
          //Prints the scoe 
          printf("\n\n           Score: %c=%d | %c=%d\n\n",  getChip(B), getScore(B, board), getChip(W), getScore(W, board));


}

// checks if the attempted move is allowed. Must be a nonperimeter space. 
//return 1 for valid, 0 for not allowed
int isPlayValid (int move) {
  if ((move >= 11) && (move <= 88) && (move%10 >= 1) && (move%10 <= 8)){
    return 1;
  } 
  else {
    return 0;
    }
}


//findChip method is a function that starts from a spot that is occupied 
//by the getRival. It moves in the given direction from itteretared DIRECTIONS array. 
//it goes through all the oppenents chips until it finds one that is occupied, it looks for opponenets chips that are trapped --> causing a flip 
//returns a 0 if a spot is not found before bumping into an available or outer spot meaning not chip was found
//called by checkPossibleFlip
int findChip(int spot, int player, int * board, int direction) {
  while (board[spot] == getRival(player)){
    spot = spot + direction;
  } 
  if (board[spot] == player){
    return spot;
  } 
  else{
    return 0;
  } 
}


//takes a spot that the player is thinking of moving, returs the oppenets chips that are trapped 
// the opponents chip. if not spot is found --> return 0
int checkPossibleFlip (int move, int player, int * board, int direction) {
  int c;
  c = move + direction;
  if (board[c] == getRival(player)){
    return findChip(c+direction, player, board, direction);
  }  
  else {
    return 0;
  } 
}


//this function checks if the move is legal
//attempts to flip rivals piece by calling checkPossible flip function.
//it considers spots and seraches in all directions for atleast one spot
//if it finds a spot it returns 1, 0 if none found
int isPlayLegal (int move, int player, int * board) {

  int i;
  if (!isPlayValid(move)) {
    return 0;
  } 
  if (board[move]==AVAILABLE) {
    i=0;
    while (i<=7 && !checkPossibleFlip(move, player, board, DIRECTIONS[i])) i++;
    if (i==8) return 0; else return 1;
  }   
  else return 0;
}


//flips the chip if the play is valid 
//trapped pieces will be flipped 
void flipChip (int move, int player, int * board, int direction) {

  int bracketChip;
  int i;
  bracketChip = checkPossibleFlip(move, player, board, direction);
  if (bracketChip) {
     i = move + direction;
     do {
      board[i] = player;
      i = i + direction;
    } while (i != bracketChip);
  }
}


//places the players chip (symbol) on the board where the player indicates. Flips any chips that 
//are trapped 
void placeChipOnBoard (int move, int player, int * board) {
  int i;
  board[move] = player;
  for (i=0; i<=7; i++) {
    flipChip(move, player, board, DIRECTIONS[i]);
  } 
}

//returns 1 if the player has legal moves, 0 if none are available. 
//called by switchPlayer()
int isLegal (int player, int * board) {
  int move;
  move = 11;
  //logic 
  while (move <= 88 && !isPlayLegal(move, player, board)) move++;
  if (move <= 88) 
  return 1; 
  else return 0;
}


//switches the player 
int switchPlayer (int * board, int prevPlayer, int flag) {
  int rival;
  rival = getRival(prevPlayer); //switch places
  if (isLegal(rival, board)) { //check if the move is legal
    return rival;
  } 
  if (isLegal(prevPlayer, board)) {
    if (flag) printf("%c no moves available, skip turn.\n", getChip(rival));
    return prevPlayer; //return previous player if rival has no moves
  }
  return 0;
}



//reprints the board with the new chips
//promps the getRival to enter desired move 
//checks if the plays are legal, if theyre not, will be prompted to enter another location 
void nextMove (int (* play) (int, int *), int player, int * board, int flag) {
  int move;

  if (flag) {
  display(board);
  move = (* play)(player, board);
  }

  if (isPlayLegal(move, player, board)) {
     if (flag) printf("%c moves to %d\n", getChip(player), move);
     placeChipOnBoard(move, player, board); 
  }
  else {
     printf("Illegal move %d\n", move);
     nextMove(play, player, board, flag); //Recursive call until a valid move is input
  }
}

//method for computer player
int * legalBotMoves (int player, int * board) {
  int move;
  int i;
  int * moves;
  moves = (int *)malloc(65 * sizeof(int));
  
  moves[0] = 0; //ensures move count is 0 
  i = 0;
  //itterate through the whole board to find all legal plays
  for (move=11; move<=88; move++) 
    if (isPlayLegal(move, player, board)) {
      i++;
      moves[i]=move;
    }
  moves[0]=i;
  return moves;
}

//method for computer player
//machine chooses randonly from the avaiable moves 
int bot(int player, int * board) {
  int random;
  int * moves;
  moves = legalBotMoves(player, board);
  random = moves[(rand() % moves[0]) + 1]; //picks a random move from all the lagal moves 
  free(moves);
  return(random);
}


// This functions evaluates the difference in number of pieces between the players.
//going to call this function in minMaxSearch() Funtion
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


//this function is identical to EvaluateDifference() except it has an array that gives weight to each spot. 
//the weight on the array gives the value of each play. 
//weights are added to determine which plays should be prioratized when the 
//computer is tryingf to make a move. The highet the value of a move, the better the move will be.
//the perimeter is evaluated to zero because it has no importance, we wont be using those spots for moves. 
//according to ultraboardgames.com the corner spots are the best plays a player can obtain.
//the negative spots should be avoided as it can potantially create a vulnerable play causing you points.

int weightedEvaluation (int player, int * board) {
  int i;
  int oppCount; 
  int playerCount;
  int opp;              
  int difference;  

  const int boardWeight[100]={0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                              0,120,-20, 20,  5,  5, 20,-20,120,  0,
                              0,-20,-40, -5, -5, -5, -5,-40,-20,  0,
                              0, 20, -5, 15,  3,  3, 15, -5, 20,  0,
                              0,  5, -5,  3,  3,  3,  3, -5,  5,  0, 
                              0,  5, -5,  3,  3,  3,  3, -5,  5,  0, 
                              0, 20, -5, 15,  3,  3, 15, -5, 20,  0,
                              0,-20,-40, -5, -5, -5, -5,-40,-20,  0,
                              0,120,-20, 20,  5,  5, 20,-20,1210, 0,
                              0,  0,  0,  0,  0,  0,  0,  0,  0,  0};

  playerCount = 0; 
  oppCount = 0;      
  oppCount = getRival(player);

  //for loop that counts all the pieces for each player in the board with weight for min max search 
  for (i=1; i<=88; i++) {
     if (board[i] == player) playerCount = playerCount + boardWeight[i];
     if (board[i] == oppCount) oppCount = oppCount + boardWeight[i];
  }

  //returns the piece difference between two players
  difference = playerCount - oppCount;

  return (difference);
}


//this function essentially makes a "play" move look ahead using the EvaluateDifference()
// previously created to evaluate board. it will look for and create scenarios 
// with legal plays per player. the play that has the best "maximum" score in the simulated board 
// will be move that is returned by minMaxSearch(). The function determines the score of every board 
// by calling on the EvaluateDifference(). It will be gameover if no player can move from the current board


int minMaxSearch (int player, int * board, int play, int (* evalFunc) (int, int *)) {


  int * moves;
  int * newBoard;
  int i;
  int maxScore;
  int nextToMove;
  int updatedScore;
  int bestPlay;


  int maximum (int, int *, int, int (*) (int, int *)); 
  int minimum (int, int *, int, int (*) (int, int *)); 

  //get all the legal plays for the current player
  moves = legalBotMoves(player, board); 

  //a legal lay will exceed this score
  maxScore = L - 1;  /* any legal move will exceed this score */


  //for loop that itterates through all the legal plays
  for (i = 1; i <= moves[0]; i++) {
    newBoard = copyBoard(board); BOARDS = BOARDS + 1;
    placeChipOnBoard(moves[i], player, newBoard);
    nextToMove = switchPlayer(newBoard, player, 0);

    //evaluate the outcome of the game if the next to move is 0. Black chip = 1. White chip = 2
    //end of game if 0 is detected
    if (nextToMove == 0) {  
         updatedScore = EvaluateDifference(player, newBoard);
         if (updatedScore > 0) updatedScore = WIN; //win 
         if (updatedScore < 0) updatedScore = L; //loss
    }

    if (nextToMove == player) //rival cant move
       updatedScore = maximum(player, newBoard, play - 1, evalFunc);

    if (nextToMove == getRival(player))
       updatedScore = minimum(player, newBoard, play - 1, evalFunc);

    if (updatedScore > maxScore) {
        maxScore = updatedScore;
        //better play was found
        bestPlay = moves[i]; 
    }
    free(newBoard);
  }

  free(moves);
  return(bestPlay);

}


// This function will be used to return the maximum board score posible from  the availble plays.
//called by the minMaxSearch algorithm
int maximum (int player, int * board, int play, int (* evalFunc) (int, int *)) {
  
  int * moves;
  int * newBoard;
  int i;
  int maxScore;
  int nextToMove;
  int updatedScore;

  int minimum (int, int *, int, int (*) (int, int *)); 

  //if play is equal to 0, maximum should return the value of the evaluateDifference function
  if (play == 0) return((* evalFunc) (player, board));

  moves = legalBotMoves(player, board);
  maxScore = L - 1;

  //if play does not equal 0, simulate all plays that can be made by the player
  for (i = 1; i <= moves[0]; i++) {
    newBoard = copyBoard(board); BOARDS = BOARDS + 1;
    placeChipOnBoard(moves[i], player, newBoard);
    nextToMove = switchPlayer(newBoard, player, 0);

    //W if its a win for the player
    //L if its a win for the rival
    // 0 if its a draw
    if (nextToMove == 0) {
         updatedScore = EvaluateDifference(player, newBoard);
         if (updatedScore > 0) updatedScore = WIN;
         if (updatedScore < 0) updatedScore = L;
    }

    //the backed up score is determined through this logic,
    //if the current player can move and its the next to move, call the maximum function to get max score, update the score
    //if its the opponents turn to move, get the minimum score
    // if the updated score is less than the max score, make the max score the updated score

    if (nextToMove == player) 
       updatedScore = maximum(player, newBoard, play-1, evalFunc);
    if (nextToMove == getRival(player))
       updatedScore = minimum(player, newBoard, play-1, evalFunc);
    if (updatedScore > maxScore) maxScore = updatedScore;
    free(newBoard);
  }
  free(moves);
  return(maxScore);
}


// This function should return the minimum simulated score from the pool of possible plays.
//called by the minMaxSearch algorithm

int minimum (int player, int * board, int play, int (* evalFunc) (int, int *)) {
 
  int * moves;
  int * newBoard;
  int i;
  int minScore;
  int nextToMove;
  int updatedScore;

  //if play is equal to 0, minimum should return the value of the evaluateDifference function
  if (play == 0) return((* evalFunc) (player, board));

  moves = legalBotMoves(getRival(player), board);
  minScore = W + 1;

  //if play is equal to 0, all if the rivals possible plays should be simulated
  for (i=1; i <= moves[0]; i++) {
    newBoard = copyBoard(board); BOARDS = BOARDS + 1;
    placeChipOnBoard(moves[i], getRival(player), newBoard);
    nextToMove = switchPlayer(newBoard, getRival(player), 0);

    //W if its a win for the player
    //L if its a win for the rival
    // 0 if its a draw
    if (nextToMove == 0) {
         updatedScore = EvaluateDifference(player, newBoard);
         if (updatedScore > 0) updatedScore = WIN;
         if (updatedScore < 0) updatedScore = L;
    }


    //the backed up score is determined through this logic,
    //if the current player can move and its the next to move, call the maximum function to get max score, update the score
    //if its the opponents turn to move, get the minimum score
    // if the updated score is smaller than the min score, make the min score the updated score

    if (nextToMove == player) 
       updatedScore = maximum(player, newBoard, play-1, evalFunc);
    if (nextToMove == getRival(player))
       updatedScore = minimum(player, newBoard, play-1, evalFunc);
    if (updatedScore < minScore) minScore = updatedScore;
    free(newBoard);
  }
  free(moves);
  return(minScore);
}


int lookAhead1(int player, int * board) { //1 play lookahed
  return(minMaxSearch(player, board, 1, EvaluateDifference));   
}

int lookAhead3(int player, int * board) { //3 play lookahed
  return(minMaxSearch(player, board, 3, EvaluateDifference));   
}

int lookAhead5(int player, int * board) { //5 play lookahed
  return(minMaxSearch(player, board, 5, EvaluateDifference));   
}

////////////// WEIGHTED LOOK AHEADS //////////////

int weightedLookAhead1(int player, int * board) { //1 play lookahed | Weighted
  return(minMaxSearch(player, board, 1, weightedEvaluation));   
}

int weightedLookAhead3(int player, int * board) { //3 play lookahed | Weighted
  return(minMaxSearch(player, board, 3, weightedEvaluation));   
}

int weightedLookAhead5(int player, int * board) { //5 play lookahed | Weighted
  return(minMaxSearch(player, board, 5, weightedEvaluation));   
}

//sets the game up
//creates a new empty board with starting chips 
void coordinateGame (int (* blackPieceP1) (int, int *), int (* whitePieceP1) (int, int *), int flag) {
  int * board;
  int player;
  board = freshBoard(); 
  player = B; //assign the first play to Black chip

  do {
    if (player == B) nextMove(blackPieceP1, B, board, flag);
    else nextMove(whitePieceP1, W, board, flag);
    player = switchPlayer(board, player, flag);
  }
  while (player != 0);
  if (flag) {
     printf("The game is over. Final result:\n");
     display(board);
  }
}



//randomize board is going to be used to simulate games between different computer player modes
//we are going to call this function in the simulateMatch() function. Non random computer modes will 
//return the same moves in everygame. randomizeBoard starts off with a clean board and uses the computer to 
// return 10 moves, 5 fro each. 

int * randomizeBoard (void) {
  int currentPlayer;
  int prevPlayer;
  int i;
  int * board;
  
  board = freshBoard();
  currentPlayer = B;
  i=1;
  do {
    if (currentPlayer == B) nextMove(bot, B, board, 0);
    else nextMove(bot, W, board, 0);
    prevPlayer = currentPlayer;
    currentPlayer = switchPlayer(board, currentPlayer, 0);
    if (prevPlayer == currentPlayer) {
       free(board);
       return(randomizeBoard());
    }
    i++;
  }
  while (currentPlayer != 0 && i<=8);
  if (currentPlayer==0) {
     free(board);
     return(randomizeBoard());
  }
  else return(board);
}




//simulate match puts each computer gametype against eachother. It does this by itterating 
//through our gametype array and incrementing. For sake of time, it is only set up to simulate 1 game for each 
//other wise it would take way too long to compute. I went with 3 games to show the best out of 3. 
//output is supposed to be printed 
void simulateMatch (void) {

  int player;
  int i;
  int j;
  int k;
  int countDifference;
  int iwins;
  int jwins;
  int * game1;
  int * game2;

  long int iboards, jboards;

  i=1;
  while (GAME_TYPE[i+1][0] != NULL) { // go againt one of the strategies
    j = i + 1;
    while (GAME_TYPE[j][0] != NULL) { // goes against another strategy
      iwins = 0; jwins = 0; iboards = 0; jboards = 0;
      for (k=1; k<=2; k++) { //play each gametype as black player and white player
        game1 = randomizeBoard();   //simulate it 2 times each for the sake of time
        game2 = copyBoard(game1);
        player = B;
        do {
          if (player == B) {
             BOARDS = 0;
             nextMove((fpc)GAME_TYPE[i][2], B, game1, 0);
             iboards = iboards + BOARDS;
	  }
          else {
             BOARDS = 0;
             nextMove((fpc)GAME_TYPE[j][2], W, game1, 0);
             jboards = jboards + BOARDS;
	  }
          player = switchPlayer(game1, player, 0);
        }
        while (player != 0);

        //determin who wins the match
        countDifference = EvaluateDifference(B, game1);  
        if (countDifference>0) iwins++;
        if (countDifference<0) jwins++;
        free(game1);

        player = B;
        do {
          if (player == B) {
             BOARDS = 0;
             nextMove((fpc)GAME_TYPE[j][2], B, game2, 0);
             jboards = jboards + BOARDS;
	  }
          else {
             BOARDS = 0;
             nextMove((fpc)GAME_TYPE[i][2], W, game2, 0);
             iboards = iboards + BOARDS;
          }
          player = switchPlayer(game2, player, 0);
        }
        while (player != 0);       
        countDifference = EvaluateDifference(W, game2);  /* determine winner */
        if (countDifference>0) iwins++;
        if (countDifference<0) jwins++;
        free(game2);
      }



      printf("\n Simulating:       %s vs %s \n\n %s win=%d boards=%ld || %s win=%d boards=%ld\n\n----------------------------------------------------\n",
              GAME_TYPE[i][0], GAME_TYPE[j][0],
              GAME_TYPE[i][0], iwins, iboards, 
              GAME_TYPE[j][0], jwins, jboards);

              

      j++;
    }     
    i++;
  }

}          


//Method to display initial user interaction
void userInterface (void) {

int i; //counter
int p1; //player 1
int p2; // player 2
int flag; //flag to determine if its valid
int (* player1)(int, int *); 
int (* player2)(int, int *);
char * stringName;

printf("--------------------------------------- \n\nPlayer 1 will be assigned to Black chips\nEnter number to chose type of player \n\n--------------------------------------- \n\n");
i=0; //counter 
printf("Player 1:\n---------\n"); 
  //while its not null, get all the player options from the GAME_TYPE array 
  while (GAME_TYPE[i][0] != NULL) { 
     stringName = GAME_TYPE[i][1]; // stringName will grab the the first string instance of the array. 'human' in this case
     printf("(%d) %s\n", i, stringName); //prints the number user must enter to select option. followed by the option in parentethese 
     i++; //goes to the next row in the GAME_TYPE array
  }
  printf("Selection: ");
  scanf("%d", &p1); //scans users answer, stores it in memory address of p1 --> player 1

  //Repeat the process for player 2
  printf("\nPlayer 2 will be assigned to White chips\n\n--------------------------------------- \n\n");
  i=0;
  printf("Player 2:\n---------\n");
  while (GAME_TYPE[i][0] != NULL) {
     stringName=GAME_TYPE[i][1]; 
     printf("%d (%s)\n", i, stringName);
     i++;
  }
  printf("Selection: ");
  scanf("%d", &p2); //scans users answer, stores it in memory address of p2 --> player 2

  player1 = GAME_TYPE[p1][2]; // the 3rd spot in the array holds the type of player
  player2 = GAME_TYPE[p2][2];

  if (player1 == humanPlayer || player2 == humanPlayer){
    flag = 1;
  } 
  else{
    printf("       \n");
    printf("Neither player is human");
    flag = 0;
  }

  coordinateGame(player1, player2, flag); //begin the game

}

int main () {


userInterface();
fflush(stdin);   
// simulateMatch();  // Doesnt work properly



}




//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT CREATES THE USER INTERFACE --> userInterface()
//display what chip is being assigned to who
//prompt user to enter choice
//select from human or computer 
//pull data from an array that hold game type informarion 


//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT CREATES THE BOARD OF A FRESH GAME --> freshBoard()
//forloop that assigns empty spaces to 0
//outer spaces to 3
//4 center pieces to black and white chips. 1 and 2 

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT MAKES A COPY OF THE BOARD --> copyBoard()
//malloc space 
//ittrate through board and copy it into new board 

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT DISPLAYS THE BOARD --> fix/update display()
//rows and columns 
//print the numbers on the outside of the board
//forloop that prints the board

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT RETURNS THE NAME OF THE PIECE --> getChip()
//takes the chip as a parameter, returns the name of it 

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD TTHAT KEEPS TRACK OF SCORE, # OF PIECES ON THE BOARD --> getScore()
//takes player and board parameter 
//for loop to iterate through the all spots on the board 

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT SWITCHES CHARACTERS --> getRival() 
//switch statement 
//take the palyer as a parameter 
//return the opposite player 
//if player == 1, return 2
//if player is black, return white 


/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//                     Methods for valid plays 


//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT CHECKS IF PLAY INPUT IS IN THE SCOPE OF THE BOARD -->isPlayValid()
//take the players move as a parameter 
//send it through if statement to check of its in the board 
//return 1 if valid; 0 if not valid

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT CHECKS IF A PLAY IS LEGAL --> isPlayLegal()
//this method is going to check is the move the player is trying to make will cause them a point 
//use if statents 

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT CONSIDERS THE FLIP THAT THE PALYER IS TRYING TO MAKE --> checkPossibleFlip()

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT CHECKS AVAILABILITY FOR FLIP -->  isLegal()

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT FLIPS THE PIECE --> flipChip()

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT PLACES THE CHIP ON THE BOARD --> placeChipOnBoard()

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT MOVES ON TO THE NEXT PLAYER --> switchPlayer()
//call on the getRival() Function

//------------------------------------------------//
//                  Completed                     //
//------------------------------------------------//
//METHOD THAT CORDINATES FUNCTION BETWEEN 2 PLAYERS --> coordinateGame()
//This method will call on freshBoard() 
//call on function that is going to switch players 
//print the board 


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


//------------------------------------------------//
//                  Not Completed                 //
//------------------------------------------------//
//METHOD CREATES COMPUTER PLAYER --> bot()
//Chose randomly between legal moves 
//Call on bot funtion that checks for legal moves 


//------------------------------------------------//
//                  Not Completed                 //
//------------------------------------------------//
//METHOD THAT CHECKS LEGAL MOVES THE BOT CAN MAKE --> botGetLegalMoves()
// store current legal moves in an array 
//itterate through the board
//call on isPlayLegal() 
//store if it is legal 
//return the moves that are available 

//------------------------------------------------//
//                  Not Completed                 //
//------------------------------------------------//
//METHOD THAT PRODUCES RANDOM BOARD FOR COMPUTER --> randomizeBoard()
// Ensures computer wont pick the same location for every game 

    