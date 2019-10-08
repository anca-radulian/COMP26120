// Program to print a chess board of any given size.
#include<stdio.h>
// Declare the colors of the chess board.
enum colors_chessboard {white, black};

// Initialise the chess board.
void create_chessboard(enum colors_chessboard chess_board[][101], int length, int width)
{
  // Keep track of the square color.
  int is_black = 1;
  for(int index = 0; index < length; index ++)
    for(int index2 = 0; index2 < width; index2 ++)
    {
      if(is_black)
        chess_board[index][index2] = black;
      else
        chess_board[index][index2] = white;
      is_black = !is_black;

    }

}
// Helper function to print the chess boards. Use # for black squares and space
// for white squares.
void print_chessboard(enum colors_chessboard chess_board[][101], int length, int width)
{

  for(int index = 0; index < length; index ++)
  {
    for(int index2 = 0; index2 < width; index2 ++)
    {
      if(chess_board[index][index2] == black)
        printf("#");
      else
        printf(" ");

    }
    printf("\n");
  }
  printf("\n");
}

int main()
{

  // First chess board
  printf("First example\n");
  enum colors_chessboard chess_board1[101][101];
  int length = 7;
  int width = 5;
  create_chessboard(chess_board1, length,width);
  print_chessboard(chess_board1, length, width);

  // Second chess board
  printf("Second example: \n");
  enum colors_chessboard chess_board2[101][101];
  length = 1;
  width = 1;
  create_chessboard(chess_board2, length,width);
  print_chessboard(chess_board2, length, width);

  // Third chess board
  printf("Third example: \n");
  enum colors_chessboard chess_board3[101][101];
  length = 28;
  width = 35;
  create_chessboard(chess_board3, length,width);
  print_chessboard(chess_board3, length, width);

  // Fourth chess board
  printf("Fourth example: \n");
  enum colors_chessboard chess_board4[101][101];
  length = 1;
  width = 12;
  create_chessboard(chess_board4, length,width);
  print_chessboard(chess_board4, length, width);

}
