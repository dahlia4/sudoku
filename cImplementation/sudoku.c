#include <stdio.h>
#include <string.h>
#define SQUARESIZE 9
#define ROOT 3

int check_square(int board[SQUARESIZE][SQUARESIZE], int s_index,int c_index, int num) {
  //s index meaning square index, c index meaning cell index
  //Check the same square
  for (int i = 0; i < SQUARESIZE; i++) {
    if (i != c_index) {
      if (board[s_index][i] == num) {
	return 0;
      }
    }
    if (i != s_index) {
      //Check a row
      for (int r = (c_index / ROOT) * ROOT; r < ROOT + ((c_index / ROOT)*ROOT); r++) {
	    if (board[i][r] == num) {
	      return 0;
	    }
      }
      //Check a column
      for (int c = c_index % ROOT; c < SQUARESIZE; c += ROOT) {
	    if (board[i][c] == num) {
	      return 0;
	    }
      }
    }
  }
  return 1;
}

int* backtrack(int board[SQUARESIZE][SQUARESIZE]) {
//basic idea; find the smallest number of possible elements for all squares
  for (int i = 0; i < SQUARESIZE * SQUARESIZE; i++) {
    for (int j = 0; j < SQUARESIZE; j++) {
      if (check_square(board,i/SQUARESIZE,i%SQUARESIZE,j)) {
	//Something here
	printf("hi");
      }
    }
  }
}

int main() {
  //printf("hello world\n");
  int board[SQUARESIZE][SQUARESIZE];// = {{0,0,0,0,0,1,0,0,0}};
  memset(board,0,sizeof(board));
  board[2][4] = 1;
  printf("%d\n",check_square(board,0,5,1));
}
