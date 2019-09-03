#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "mine_sweeperLogic.h"


boardState ReadArgs(int numArgs, char* argv[]) {
   boardState newBoard;
   if (numArgs == 4) {
      srand((int)time(0));
   }
   else if (numArgs == 5) {
      int seed = atoi(argv[4]);
      srand(seed);
   }
   else  if (numArgs < 4) {
      printf("Not enough arguments. Usage:\n./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
      exit(0);
   }
   else {
      printf("Too many arguments. Usage:\n./mine_sweeper.out num_rows num_cols num_mines [seed])\n");
      exit(0);     
   }
   newBoard.numRows = atoi(argv[1]);
   newBoard.numCols = atoi(argv[2]);
   newBoard.numMines = atoi(argv[3]);
   return newBoard;
}

boardState CreateBoard(boardState newBoard) {
   newBoard = CreateBoardDisplay(newBoard);
   newBoard = CreateMinesInfo(newBoard);
   newBoard.numSpacesLeft = newBoard.numRows * newBoard.numCols;
   return newBoard;
}

//Creates board and returns a char array pointer
boardState CreateBoardDisplay(boardState newBoard) {
   // initializes the board to hold the proper number of rows
   newBoard.boardDisplay = (char**)malloc(newBoard.numRows * sizeof(char*));

   // for each row, allocates memory for the proper number of columns
   for (int i = 0; i < newBoard.numRows; i++) {
      newBoard.boardDisplay[i] = (char*)malloc(newBoard.numCols * sizeof(char));
   }

   // initializes each space on the board to an asterisk
   for (int row = 0; row < newBoard.numRows; row++){
      for (int col = 0; col < newBoard.numCols; col++) {
         newBoard.boardDisplay[row][col] = '#';
      }
   }

   return newBoard;
}

boardState CreateMinesInfo(boardState newBoard) {
   newBoard = CreateSpace(newBoard);
   newBoard = PlantMines(newBoard);
   newBoard = InsertNumbers(newBoard);
   return newBoard;
}

boardState CreateSpace(boardState newBoard) {
   // initializes the board to hold the proper number of rows
   newBoard.minesInfo = (char**)malloc(newBoard.numRows * sizeof(char*));

   // for each row, allocates memory for the proper number of columns
   for (int i = 0; i < newBoard.numRows; i++) {
      newBoard.minesInfo[i] = (char*)malloc(newBoard.numCols * sizeof(char));
   }

   // initializes each space on the board to an asterisk
   for (int row = 0; row < newBoard.numRows; row++){
      for (int col = 0; col < newBoard.numCols; col++) {
         newBoard.minesInfo[row][col] = '0';
      }
   }

   return newBoard;
}

boardState PlantMines(boardState newBoard) {
   for (int i = 0; i < newBoard.numMines; i++) {
      int xVal, yVal;
      do {
         xVal =(rand() % newBoard.numRows);
         yVal =(rand() % newBoard.numCols);
      } while (newBoard.minesInfo[xVal][yVal] != '0');
      newBoard.minesInfo[xVal][yVal] = '*';
      printf("Placing mine at %d, %d\n", xVal, yVal);
   }
   return newBoard;
}

boardState InsertNumbers(boardState newBoard) {
   for (int i = 0; i < newBoard.numRows; i++) {
      for (int j = 0; j < newBoard.numCols; j++) {

         int minesCounter = 0;
         if (newBoard.minesInfo[i][j] == '0') {

            if (IsInBoard(i-1, j-1, newBoard)) {
               if (newBoard.minesInfo[i-1][j-1] == '*') {
                  minesCounter++;
               }
            }
            if (IsInBoard(i-1, j, newBoard)) {
               if (newBoard.minesInfo[i-1][j] == '*') {
                  minesCounter++;
               }
            }
            if (IsInBoard(i-1, j+1, newBoard)) {
               if (newBoard.minesInfo[i-1][j+1] == '*') {
                  minesCounter++;
               }
            }
            if (IsInBoard(i, j-1, newBoard)) {
               if (newBoard.minesInfo[i][j-1] == '*') {
                  minesCounter++;
               }
            }
            if (IsInBoard(i, j+1, newBoard)) {
               if (newBoard.minesInfo[i][j+1] == '*') {
                  minesCounter++;
               }
            }
            if (IsInBoard(i+1, j-1, newBoard)) {
               if (newBoard.minesInfo[i+1][j-1] == '*') {
                  minesCounter++;
               }
            }
            if (IsInBoard(i+1, j, newBoard)) {
               if (newBoard.minesInfo[i+1][j] == '*') {
                  minesCounter++;
               }
            }
            if (IsInBoard(i+1, j+1, newBoard)) {
               if (newBoard.minesInfo[i+1][j+1] == '*') {
                  minesCounter++;
               }
            }

            newBoard.minesInfo[i][j] = (minesCounter + '0'); //converts int to char and stores it
         }
      }
   }
   return newBoard;
}

bool IsInBoard(int xVal, int yVal, boardState newBoard) {
   if (!(xVal >= 0 && xVal < newBoard.numRows)) {
      return false;
   }
   if (!(yVal >= 0 && yVal < newBoard.numCols)) {
      return false;
   }
   return true;
}

//Display the current board
void DisplayBoard(boardState currentBoard, char** myBoard) {

   // prints rows starting from the top down
   for (int row = 0; row < currentBoard.numRows; row++) {
      printf("%d ", currentBoard.numRows - 1 - row);
      for (int col = 0; col < currentBoard.numCols; col++) {
         printf("%c ", myBoard[currentBoard.numRows - 1 - row][col]);
      }
      printf("\n");
   }
   printf("  "); //aligns the column numbers

   // prints the column numbers
   for (int col = 0; col < currentBoard.numCols; col++) {
      printf("%d ", col);
   }
   printf("\n");
}

boardState ActionMark(boardState currentBoard, move currentMove) {
   currentBoard.boardDisplay[currentMove.row][currentMove.col] = '!';
   currentBoard.numMines--;
   currentBoard.numSpacesLeft--;
   return currentBoard;
}

boardState ActionQuestion(boardState currentBoard, move currentMove) {
   currentBoard.boardDisplay[currentMove.row][currentMove.col] = '?';
   return currentBoard;
}

boardState OpenSpace(boardState currentBoard, move currentMove) {
   if (currentBoard.boardDisplay[currentMove.row][currentMove.col] == '!') {
      currentBoard.numMines++;
      currentBoard.numSpacesLeft++;
   }
   currentBoard.boardDisplay[currentMove.row][currentMove.col] = '#';
   return currentBoard;
}

boardState _RevealSpace(int row, int col, boardState currentBoard) {
   move currentMove;
   // currentBoard.boardDisplay[row][col] = currentBoard.minesInfo[row][col];
   // currentBoard.numSpacesLeft--;
   //if (currentBoard.minesInfo[row][col] == '0') {
      currentMove.row = row;
      currentMove.col = col;
      currentMove.action = 0;
      currentBoard = RevealSpace(currentBoard, currentMove);
   //} 
   return currentBoard;
}

boardState CheckSpace (int row, int col, boardState currentBoard) {
   if (IsInBoard(row, col, currentBoard)) {
      if (currentBoard.boardDisplay[row][col] == '#') {
         currentBoard = _RevealSpace(row, col, currentBoard);
      }
   }
   return currentBoard;
}

boardState RevealSpace(boardState currentBoard, move currentMove) {
   //printf("currentMove: %d, %d, %d\n", currentMove.row, currentMove.col, currentMove.action);
   if (currentBoard.minesInfo[currentMove.row][currentMove.col] == '*') {
      LoseState(currentBoard, currentMove);
   }
   if (currentBoard.minesInfo[currentMove.row][currentMove.col] == '0') {
      currentBoard.boardDisplay[currentMove.row][currentMove.col] = currentBoard.minesInfo[currentMove.row][currentMove.col];
      currentBoard.numSpacesLeft--;
      int i = currentMove.row;
      int j = currentMove.col;
      currentBoard = CheckSpace(i-1, j-1, currentBoard);
      currentBoard = CheckSpace(i-1, j, currentBoard);
      currentBoard = CheckSpace(i-1, j+1, currentBoard);
      currentBoard = CheckSpace(i, j-1, currentBoard);
      currentBoard = CheckSpace(i, j+1, currentBoard);
      currentBoard = CheckSpace(i+1, j-1, currentBoard);
      currentBoard = CheckSpace(i+1, j, currentBoard);
      currentBoard = CheckSpace(i+1, j+1, currentBoard);
   }
   else {
      currentBoard.boardDisplay[currentMove.row][currentMove.col] = currentBoard.minesInfo[currentMove.row][currentMove.col];
      currentBoard.numSpacesLeft--;
   }
   return currentBoard;
}

void LoseState(boardState currentBoard, move currentMove) {
   DisplayBoard(currentBoard, currentBoard.minesInfo);
   printf("You Lost :(\n");
   exit(0);
}

bool HasWon(boardState currentBoard) {
   if (currentBoard.numSpacesLeft == 0 && currentBoard.numMines == 0) {
      return true;
   }
   return false;
}
