#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>
#include "mine_sweeperLogic.h"

void GameLoop(boardState currentBoard);
move RequestMove(boardState currentBoard);
boardState MakeMove(boardState currentBoard, move currentMove);
bool IsValidMove (move currentMove, boardState currentBoard);
boardState UpdateBoard (boardState currentBoard, move currentMove);

int main (int argc, char* argv[]) {
   boardState gameBoard = ReadArgs(argc, argv);
   gameBoard = CreateBoard(gameBoard);
   printf("There are %d mines left\n", gameBoard.numMines);
   DisplayBoard(gameBoard, gameBoard.boardDisplay);
   GameLoop(gameBoard);
   return 0;
}

void GameLoop(boardState currentBoard) {
   bool win;
   do {
      move currentMove = RequestMove(currentBoard);
      currentBoard = MakeMove(currentBoard, currentMove);
      win = HasWon(currentBoard);
      if (!win) {
         printf("There are %d mines left\n", currentBoard.numMines);
         DisplayBoard(currentBoard, currentBoard.boardDisplay);
      }
   } while(!win);
   DisplayBoard(currentBoard, currentBoard.minesInfo);
   printf("You Won!!\n");
   exit(0);
}

move RequestMove(boardState currentBoard) {
   move currentMove;
   do {
      printf("Enter row a row between 0-%d and a column between 0-%d: ", currentBoard.numRows - 1, currentBoard.numCols - 1);
      scanf("%d %d", &currentMove.row, &currentMove.col); 
   } while(!IsValidMove(currentMove, currentBoard));

   return currentMove;
}

boardState MakeMove(boardState currentBoard, move currentMove) {
   printf("Enter Action\n");
   if (currentBoard.boardDisplay[currentMove.row][currentMove.col] == '?') {
      printf("0. UnQuestion\n");
      printf("1. Cancel\n");
      printf("Action: ");
      scanf("%d", &currentMove.action);
      if (currentMove.action >= 1 || currentMove.action < 0) GameLoop(currentBoard);
      if (currentMove.action == 0) {
         currentBoard = OpenSpace(currentBoard, currentMove); 
      }
   }
   else if (currentBoard.boardDisplay[currentMove.row][currentMove.col] == '!' ) {
      printf("0. UnMark\n");
      printf("1. Cancel\n");
      printf("Action: ");
      scanf("%d", &currentMove.action);
      if (currentMove.action >= 1 || currentMove.action < 0) GameLoop(currentBoard);
      if (currentMove.action == 0) {
         currentBoard = OpenSpace(currentBoard, currentMove);
      }
   }
   else {
      printf("0. Reveal\n");
      printf("1. Question\n");
      printf("2. Mark\n");
      printf("3. Cancel\n");
      printf("Action: ");
      scanf("%d", &currentMove.action);
      if (currentMove.action >= 3 || currentMove.action < 0) GameLoop(currentBoard);
      currentBoard = UpdateBoard(currentBoard, currentMove);
   }
   return currentBoard;
}

bool IsValidMove (move currentMove, boardState currentBoard) {
   bool isValid = true;
   if (currentMove.row >= currentBoard.numRows || currentMove.row < 0) {
       return false;
   }
   if (currentMove.col >= currentBoard.numCols || currentMove.col < 0) {
       return false;
   }
   if (isdigit(currentBoard.boardDisplay[currentMove.row][currentMove.col])) {
      isValid = false;
      printf("This tile is already revealed.\n");
   }
   return isValid;
}

boardState UpdateBoard (boardState currentBoard, move currentMove) {
   switch (currentMove.action) {
      case 0:
         currentBoard = RevealSpace(currentBoard, currentMove);
         break;
      case 1:
         currentBoard = ActionQuestion(currentBoard, currentMove);
         break;
      case 2:
         currentBoard = ActionMark(currentBoard, currentMove);
         break;
      case 3:
         break;
   }
   return currentBoard;
}