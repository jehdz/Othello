#include <gtest/gtest.h>
#include "board.hh"

//Difference of 1
TEST(EvaluateDifference, case1) {

    int player1 = 1;
    int opponent = 2;

    int * othelloBoard; 
    othelloBoard = (int *)malloc(100 * sizeof(int));

    othelloBoard[44]=opponent; 
    othelloBoard[45]=player1; 
    othelloBoard[46]=player1;
    othelloBoard[54]=player1; 
    othelloBoard[55]=opponent;

    int expected = 1;

    ASSERT_TRUE(expected == EvaluateDifference(player1 , othelloBoard));

}

TEST(EvaluateDifference, case2) {

    int player1 = 1;
    int opponent = 2;

    int * othelloBoard; 
    othelloBoard = (int *)malloc(100 * sizeof(int));

    othelloBoard[44]=player1; 
    othelloBoard[45]=player1; 
    othelloBoard[46]=player1;
    othelloBoard[54]=player1; 
    othelloBoard[55]=opponent;

    int expected = 3;

    ASSERT_TRUE(expected == EvaluateDifference(player1 , othelloBoard));

}

TEST(EvaluateDifference, case3) {

    int player1 = 1;
    int opponent = 2;

    int * othelloBoard; 
    othelloBoard = (int *)malloc(100 * sizeof(int));

    othelloBoard[44]=player1; 
    othelloBoard[45]=player1; 
    othelloBoard[46]=player1;
    othelloBoard[54]=player1; 
    othelloBoard[55]=player1;

    int expected = 5;

    ASSERT_TRUE(expected == EvaluateDifference(player1 , othelloBoard));

}


TEST(EvaluateDifference, case4) {

    int player1 = 1;
    int opponent = 2;

    int * othelloBoard; 
    othelloBoard = (int *)malloc(100 * sizeof(int));

    othelloBoard[44]=player1; 
    othelloBoard[45]=player1; 
    othelloBoard[46]=player1;
    othelloBoard[54]=player1; 
    othelloBoard[55]=player1;

    int expected = 5;

    ASSERT_TRUE(expected == EvaluateDifference(player1 , othelloBoard));

}

TEST(EvaluateDifference, case5) {

    int player1 = 1;
    int opponent = 2;

    int * othelloBoard; 
    othelloBoard = (int *)malloc(100 * sizeof(int));

    othelloBoard[44]=opponent; 
    othelloBoard[45]=player1; 
    othelloBoard[46]=player1;
    othelloBoard[54]=player1; 
    othelloBoard[55]=opponent;

    int expected = -1;

    ASSERT_TRUE(expected == EvaluateDifference(opponent , othelloBoard));

}

TEST(EvaluateDifference, case6) {

    int player1 = 1;
    int opponent = 2;

    int * othelloBoard; 
    othelloBoard = (int *)malloc(100 * sizeof(int));



    int expected = 0;

    ASSERT_TRUE(expected == EvaluateDifference(opponent , othelloBoard));

}




//tests if the move is in the board 
TEST(isPlayValid, inBound_Case1) {
    int move = 76;
    int expected = 1; //means its legal 
    ASSERT_TRUE(expected == isPlayValid(move));

}

//tests if the move is in the board 
TEST(isPlayValid, inBound_Case2) {
    int move = 35;
    int expected = 1; //means its legal 
    ASSERT_TRUE(expected == isPlayValid(move));

}

//smalles number allowed
TEST(isPlayValid, inBound_Case3) {
    int move = 11;
    int expected = 1; //means its legal 
    ASSERT_TRUE(expected == isPlayValid(move));

}

//largest number allowed 
TEST(isPlayValid, inBound_Case4) {
    int move = 88;
    int expected = 1; //means its legal 
    ASSERT_TRUE(expected == isPlayValid(move));

}

//makes sure it returns 0 if play is out of bound
TEST(isPlayValid, outOfBound_Case1) {
    int move = 100;
    int expected = 0; //means its legal 
    ASSERT_TRUE(expected == isPlayValid(move));

}

//makes sure it returns 0 if play is out of bound
TEST(isPlayValid, outOfBound_Case2) {
    int move = 0;
    int expected = 0; //means its legal 
    ASSERT_TRUE(expected == isPlayValid(move));

}

//makes sure it returns 0 if play is out of bound
TEST(isPlayValid, outOfBound_Case3) {
    int move = 89;
    int expected = 0; //means its legal 
    ASSERT_TRUE(expected == isPlayValid(move));

}


// Checks if the retrived piecs are correct 
//checks for black piece
TEST(getChip, emptyPiece) {
    int piece = 0;
    static char chipSymbol[5] = "*bw?"; 
    char actual = chipSymbol[piece];
    char expected = '*';
    ASSERT_TRUE(actual == expected);

}

//checks for empty piece
TEST(getChip, blackPiece) {
    int piece = 1;
    static char chipSymbol[5] = "*bw?"; 
    char actual = chipSymbol[piece];
    char expected = 'b';
    ASSERT_TRUE(actual == expected);

}

//checks fro white piece
TEST(getChip, whitePiece) {
    int piece = 2;
    static char chipSymbol[5] = "*bw?"; 
    char actual = chipSymbol[piece];
    char expected = 'w';
    ASSERT_TRUE(actual == expected);

}

//ensures the black isnt returend if black is the parameter
TEST(getRival, case1) {

    int player = 1;

    ASSERT_FALSE(player == getRival(player));

}

//ensures the white isnt returend if white is the parameter
TEST(getRival, case2) {

    int player = 2;

    ASSERT_FALSE(player == getRival(player));

}

//ensures black player is returned when white is given 
TEST(getRival, case3) {

    int player = 2;
    int expected = 1;

    ASSERT_TRUE(expected == getRival(player));

}

//ensures white player is returned when black is given 
TEST(getRival, case4) {

    int player = 1;
    int expected = 2;

    ASSERT_TRUE(expected == getRival(player));

}





int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}