import java.util.*;
class SudokuGame {
    
    static public void main (String[] args) {
    SudokuBoard board = new SudokuBoard();
    //board.testCase();
    //board.naiveSolve();
    board.setFromUser();
    //board.print();
    }
}