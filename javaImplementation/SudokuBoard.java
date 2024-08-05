import java.util.*;
class SudokuBoard {
    static int BOX_SIZE=3;
    static int BOARD_SIZE=3;
    int[][] board;
    SudokuBoard() {
        board = new int[BOARD_SIZE*3][BOX_SIZE*BOX_SIZE]; 
        for (int x=0; x<board.length; x++) {
            for(int y=0;y<board[x].length;y++) {
                board[x][y]=0; 
            }
        }
    }
    
    void print() {
        int count = 0;
        StringBuilder line0Str = new StringBuilder("");
        StringBuilder line1Str = new StringBuilder("");
        StringBuilder line2Str = new StringBuilder("");
        for (int box=0; box<board.length; box++) {
            int innerCount = 0;
            for(int boxPos=0;boxPos<board[box].length;boxPos++) {
                if (innerCount/3 == 0) {
                    line0Str.append(board[box][boxPos]);
                    line0Str.append(", ");
                    if (innerCount % 3 == 2) {
                        line0Str.append("   ");
                    }
                } else if (innerCount/3 == 1) {
                    line1Str.append(board[box][boxPos] + ", ");
                    if (innerCount % 3 == 2) {
                        line1Str.append("   ");
                    }
                } else if (innerCount/3 == 2) {
                    line2Str.append(board[box][boxPos] + ", ");
                    if (innerCount % 3 == 2) {
                        line2Str.append("   ");
                    }
                }
                
                innerCount++;
                
            }
            if (count%3 == 2 && count>0) {
                System.out.println(line0Str); System.out.println(line1Str); System.out.println(line2Str);
                System.out.println();
                line0Str = new StringBuilder("");
                line1Str = new StringBuilder("");
                line2Str = new StringBuilder("");
            }
            count++;
        }
    }
    
    void printExclude(int userBox, int userPos) {
        int count = 0;
        StringBuilder line0Str = new StringBuilder("");
        StringBuilder line1Str = new StringBuilder("");
        StringBuilder line2Str = new StringBuilder("");
        for (int box=0; box<board.length; box++) {
            int innerCount = 0;
            for(int boxPos=0;boxPos<board[box].length;boxPos++) {
                if (innerCount/3 == 0) {
                    if (!(box==userBox && boxPos==userPos)) {
                    line0Str.append(board[box][boxPos]);
                    } else {line0Str.append("*");}
                    line0Str.append(", ");
                    if (innerCount % 3 == 2) {
                        line0Str.append("   ");
                    }
                } else if (innerCount/3 == 1) {
                    if (!(box==userBox && boxPos==userPos)) {
                    line1Str.append(board[box][boxPos]);
                    } else {line1Str.append("*");}
                    line1Str.append(", ");
                    if (innerCount % 3 == 2) {
                        line1Str.append("   ");
                    }
                } else if (innerCount/3 == 2) {
                    if (!(box==userBox && boxPos==userPos)) {
                    line2Str.append(board[box][boxPos]);
                    } else {line2Str.append("*");}
                    line2Str.append(", ");
                    if (innerCount % 3 == 2) {
                        line2Str.append("   ");
                    }
                }
                
                innerCount++;
                
            }
            if (count%3 == 2 && count>0) {
                System.out.println(line0Str); System.out.println(line1Str); System.out.println(line2Str);
                System.out.println();
                line0Str = new StringBuilder("");
                line1Str = new StringBuilder("");
                line2Str = new StringBuilder("");
            }
            count++;
        }
    }
    
    boolean checkNum (int num, int box, int boxPos) {
        //Checks if a given number would be valid at a certain box position
        
        //Checks squares in same box
        for (int x = 0; x < 9; x++) {
            if (board[box][x] == num && x!=boxPos) {return false;}
        }
        
        //Checks squares in same column
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (board[(box % 3) + (x*3)][(boxPos % 3) + (y*3)] == num && (x!=box || y!=boxPos)) { return false;}
            }
        }
        
        //Checks squares in same row
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if(board[((box / 3) * 3) + x][((boxPos / 3) * 3) + y] == num && (x!=box || y!=boxPos)) { return false;}
            }
        }
        return true;
    }
    
    void assignVals(int[][] nums) {
        for (int x = 0; x < nums.length; x++) {
            assert nums[x].length == 3;
            board[nums[x][1]][nums[x][2]] = nums[x][0];
        }
    }
    
    void testCase() {
        int[][] vals2Assign = {
        {3,0,0}, {4,0,1}, {5,0,2}, {6,0,3}, {1,0,4}, {7,0,6}, {9,0,7},
        {8,1,4}, {3,1,5}, {4,1,7}, {5,1,8},
        {8,2,2}, {5,2,3}, {4,2,4}, {9,2,5}, {6,2,8},
        {7,3,7}, {1,3,8},
        {1,4,0}, {5,4,1}, {7,4,2}, {6,4,4}, {4,4,5}, {9,4,6},
        {9,5,3}, {4,5,6},
        {9,6,2}, {5,6,4}, {2,6,6}, {6,6,8},
        {2,7,1}, {1,7,4},
        {6,8,0}, {4,8,2}, {3,8,6}
    };
    assignVals(vals2Assign);
    }
    
    static int getIntFromUser() {
        Scanner scanner = new Scanner(System.in);
        while (!scanner.hasNextInt()) { scanner.nextLine(); }
        return scanner.nextInt();
    }
    
    void setFromUser() {
        setFromUser(0,0);
    }
    
    void setFromUser(int currentBox, int currentPos) {
        System.out.println("0 to advance to next square, -1 to go back, -2 to exit, num to set to set a number");
        int user = getIntFromUser();
        if (user>0 && user < 10) {        
        board[currentBox][currentPos]=user;  
        if(currentPos==8) {
                if (currentBox==8) {
                    currentPos = 0;
                    currentBox = 0;
                } else {currentBox++; currentPos=0;}
            } else {currentPos+=1;}
        printExclude(currentBox,currentPos);
        setFromUser(currentBox,currentPos);
        } else if (user==0) {
            if(currentPos==8) {
                if (currentBox==8) {
                    currentPos = 0;
                    currentBox = 0;
                } else {currentBox++; currentPos=0;}
            } else {currentPos++;}
            printExclude(currentBox,currentPos);
            setFromUser(currentBox,currentPos);
        } else if (user > 9) {
            naiveSolve();
            print();
        } else if (user == -1) {
            if (currentPos == 0) {
                if (currentBox == 0) {
                    currentBox = 8; currentPos = 8;
                } else {
                    currentBox--; currentPos = 8;
                }
            } else {currentPos--;}
            printExclude(currentBox,currentPos);
            setFromUser(currentBox,currentPos);
        }
    }
    
    void naiveSolve() {
        boolean solved = true;
        for (int x = 0; x < board.length; x++) {
            for (int y = 0; y < board[x].length; y++) {
                if (board[x][y] == 0) {
                    int possibleVals = 0;
                    for (int z = 1; z <= 9; z++) {
                        if (checkNum(z,x,y)) {
                            if (possibleVals==0) {
                                possibleVals = z;
                            } else {
                                possibleVals = -1;
                            }
                        }
                    }
                    if (possibleVals > 0) {
                        board[x][y] = possibleVals;
                    } else {solved = false;}
                }
            }
        }
        if (!solved) {naiveSolve();}
        
    }
}
    