#include <stdio.h>
#include <string.h>
#define SQUARESIZE 9
#define ROOT 3

int check_square(int board[SQUARESIZE][SQUARESIZE], int s_index,int c_index, int num) {
  //s index meaning square index, c index meaning cell index
  //Check the same square
  num = ((num-1)% SQUARESIZE)+1;
  if (board[s_index][c_index] != 0) {
    return 0;
  }
  for (int i = 0; i < SQUARESIZE; i++) {
    if (i != c_index) {
      //Checks if squares in the box are legal
      if (((board[s_index][i]-1)%SQUARESIZE)+1 == num) {
	return 0;
      }
    }
    if (i != s_index) {
      //Check a row
      int square_row = s_index / ROOT;
      int cell_row = c_index / ROOT;
      for (int s_r = square_row * ROOT; s_r < (square_row * ROOT) + ROOT; s_r++) {
	for (int c_r = cell_row * ROOT; c_r < (cell_row * ROOT) + ROOT; c_r++) {
   	  if (((board[s_r][c_r]-1)%SQUARESIZE)+1 == num) {
	    return 0;
	  }
	}
      }
      //Check a column
      int square_col = s_index % ROOT;
      int cell_col = c_index % ROOT;
      for (int s_c = square_col; s_c < SQUARESIZE; s_c += ROOT) {
	for (int c_c = cell_col; c_c < SQUARESIZE; c_c += ROOT) {
	  if (((board[s_c][c_c]-1)%SQUARESIZE)+1 == num) {
	    return 0;
	  }
	}
      }
    }
  }
  return 1;
}

int backtrack2(int board[SQUARESIZE][SQUARESIZE], int start) {
//basic idea; find the smallest number of possible elements for all squares
  for (int i = start; i < SQUARESIZE * SQUARESIZE; i++) {
    int found = 0;
    printf("--------------------------------\n");
    for (int i2 = 0; i2 < SQUARESIZE; i2++) {
        for (int j2 = 0; j2 < SQUARESIZE; j2++) {
          printf("%d . ",board[i2][j2]);
        }
        printf("\n");
    }
    for (int j = 1; j < SQUARESIZE+1; j++) {
      if (check_square(board,i/SQUARESIZE,i%SQUARESIZE,j)) {
	board[i/SQUARESIZE][i%SQUARESIZE] = j;
	int back = backtrack2(board,i+1);
	if (back) {
	  found = 1;
	  break;
	}
      }
    }

    if (!found) {
      return 0;
    }
  }
  return 1;
}

void print_board(int board[SQUARESIZE][SQUARESIZE]) {
  printf("----------------------------\n");
  for (int i = 0; i < SQUARESIZE; i++) {
    for (int j = 0; j < SQUARESIZE; j++) {
      printf("%d . ",((board[i][j]-1)%SQUARESIZE)+1);
    }
    printf("\n");
  }
}

int backtrack(int board[SQUARESIZE][SQUARESIZE]) {
  //Use numbers over squaresize to indicate set by us
  int solved = 0;
  int impossible = 0;
  int ind = 0;
  int pushed_back = 0;
  while (!solved && !impossible) {
    printf("IND IS %d \n",ind);
    print_board(board);
    if (board[ind/SQUARESIZE][ind%SQUARESIZE] == 0) {
      int set = 0;
      for (int j = SQUARESIZE + 1; j < SQUARESIZE + SQUARESIZE + 1; j++) {
	if (check_square(board,ind/SQUARESIZE,ind%SQUARESIZE,j)) {
	    board[ind/SQUARESIZE][ind%SQUARESIZE] = j;
	    ind += 1;
	    pushed_back = 0;
	    set = 1;
	    if (ind >= SQUARESIZE * SQUARESIZE) {
	      solved = 1;
	    }
	    break;
	  }
	}
      if (!set) {
	if (pushed_back) {
	  board[ind/SQUARESIZE][ind%SQUARESIZE] = 0;
	} else {
	  pushed_back = 1;
	}
	ind-=1;
	
	if (ind < 0) {
	  impossible = 1;
	}
    }
    } else if (board[ind/SQUARESIZE][ind%SQUARESIZE] < SQUARESIZE  + 1) {
      if (!pushed_back) {
	ind += 1;
	if (ind >= SQUARESIZE * SQUARESIZE) {
	  solved = 1;
	}
      } else {
	ind -= 1;
	if (ind < 0) {
	  impossible = 1;
	}
      }
    } else {
      //case where we were already set
    int set = 0;
    int start = board[ind/SQUARESIZE][ind%SQUARESIZE] + 1;
    board[ind/SQUARESIZE][ind%SQUARESIZE] = 0;
    
    for (int j = start; j < SQUARESIZE + SQUARESIZE + 1; j++) {
        if (check_square(board,ind/SQUARESIZE,ind%SQUARESIZE,j)) {
            board[ind/SQUARESIZE][ind%SQUARESIZE] = j;
	    set = 1;
	    ind += 1;
            if (ind >= SQUARESIZE * SQUARESIZE) {
              solved = 1;
            }
            break;
          }
        }
    if (!set){
      if (pushed_back) {
	board[ind/SQUARESIZE][ind%SQUARESIZE] = 0;
      } else {
	pushed_back = 1;
      }
      ind -= 1;
      if (ind < 0) {
	impossible = 1;
      }
    }
    }

  }
  print_board(board);
  if (solved) {
    return 1;
  } else if (impossible) {
    return 0;
  }
  return 2;
}

int main() {
  //printf("hello world\n");
  int board[SQUARESIZE][SQUARESIZE];// = {{0,0,0,0,0,1,0,0,0}};
  memset(board,0,sizeof(board));
  board[0][0] = 3; board[0][3] = 2; board[0][4] = 1; board[0][5] = 7;
  board[1][0] = 7; board[1][3] = 3; board[1][6] = 2; board[1][7] = 4; board[1][8] = 8;
  board[2][0] = 6; board[2][1] = 2; board[2][2] = 9; board[2][3] = 5; board[2][7] = 7;
  board[3][0] = 1; board[3][1] = 7; board[3][3] = 6; board[3][4] = 9; board[3][8] = 5;
  board[4][1] = 3; board[4][4] = 1; board[4][5] = 2; board[4][7] = 9;
  board[5][1] = 8; board[5][2] = 6; board[5][6] = 2; board[5][8] = 4;
  board[6][0] = 9; board[6][2] = 6; board[6][4] = 8; board[6][5] = 3;
  board[7][2] = 4; board[7][3] = 5; board[7][5] = 6;
  board[8][2] = 2; board[8][6] = 7;// board[8][7] = 6; board[8][8] = 5;
  
  printf("%d\n",backtrack(board));
}
