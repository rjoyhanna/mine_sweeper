#ifndef MINE_SWEEPER_H
#define MINE_SWEEPER_H

   typedef struct BOARD_STATE_H {
      int numRows;
      int numCols;
      int numMines;
      int numSpacesLeft;
      char** minesInfo;
      char** boardDisplay;
   } boardState;

   typedef struct MOVE_Struct {
         int row;
         int col;
         int action;
   } move;

   boardState ReadArgs(int numArgs, char* argv[]);

   boardState CreateBoard(boardState newBoard);

   boardState CreateBoardDisplay(boardState newBoard);

   boardState CreateMinesInfo(boardState newBoard);

   boardState CreateSpace(boardState newBoard);

   boardState PlantMines(boardState newBoard);

   boardState InsertNumbers(boardState newBoard);

   bool IsInBoard(int xVal, int yVal, boardState newBoard);

   void DisplayBoard(boardState currentBoard, char** myBoard);

   boardState ActionMark(boardState currentBoard, move currentMove);

   boardState ActionQuestion(boardState currentBoard, move currentMove);

   boardState OpenSpace(boardState currentBoard, move currentMove);

   boardState _RevealSpace(int row, int col, boardState currentBoard);

   boardState RevealSpace(boardState currentBoard, move currentMove);

   void LoseState(boardState currentBoard, move currentMove);

   bool HasWon(boardState currentBoard);

#endif