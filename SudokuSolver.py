import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;
import javafx.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;

public class SudokuSolver extends Application implements EventHandler<ActionEvent>{
   Stage window;
   
   public static void main(String[] args){
      launch(args);
   }
   
   Button solveButton;
   TextField[][] fields;
   public void start(Stage primaryStage) throws Exception{
      window = primaryStage;
      window.setTitle("Sudoku Solver");
      
      GridPane grid = new GridPane();
      grid.setPadding(new Insets(10, 10, 10, 10));
      grid.setVgap(3);
      grid.setHgap(3);
            
         
      fields = new TextField[9][9];
      for(int i = 0; i<9; i++){
         for(int k = 0; k<9; k++){
            fields[i][k] = new TextField();
            fields[i][k].setMaxWidth(30);
            GridPane.setConstraints(fields[i][k], k, i);
            grid.getChildren().addAll(fields[i][k]);
         }
      }   
      solveButton = new Button("Solve");
      GridPane.setConstraints(solveButton, 20, 20);
      solveButton.setOnAction(this);
      
      grid.getChildren().addAll(solveButton);
            
      Scene scene = new Scene(grid, 420, 420);
      window.setScene(scene);
      
      
      
      window.show();
   }
   public void handle(ActionEvent e){
      int[][] board = new int[9][9];
      if (e.getSource() == solveButton){
         for (int row = 0; row < 9; row++){
            for (int col = 0; col < 9; col++){
               if (fields[row][col].getCharacters().toString().equals("")){
                  board[row][col] = 0;
                  continue;
               }
               board[row][col] = Integer.parseInt(fields[row][col].getCharacters().toString());
            }
         }
         int[][] sol = solve(board);
         window.close();
         GridPane grid = new GridPane();
         Scene scene2 = new Scene(grid);
         window.setScene(scene2);
         for(int i = 0; i<9; i++){
            for(int k = 0; k<9; k++){
               fields[i][k] = new TextField(String.valueOf(board[i][k]));
               fields[i][k].setMaxWidth(25);
               GridPane.setConstraints(fields[i][k], k, i);
               grid.getChildren().addAll(fields[i][k]);
            }
         }
         window.show();
      }
      
   }
   
   public static int[][] solve(int[][] board){
		ArrayList<ArrayList<Integer>> master = new ArrayList<ArrayList<Integer>>();
		for (int row=0; row<9; row++) {
			for (int col=0; col<9; col++) {
				if (board[row][col] != 0) {
					ArrayList<Integer> l = new ArrayList<Integer>();
					l.add(row);
					l.add(col);
					master.add(l);
				}
			}
		}
		
		
		if (solveUtil(board, 0, 0, master)) {
			printboard(board);
			return board;

		}
		
		
		return board;
	}
	
	public static void printboard(int[][] board) {
		for(int row=0; row<9; row++){
			for(int col=0; col<9; col++) {
				System.out.print(board[row][col] +" ");
			}
			System.out.println();
		}
		
	}
	
	public static boolean solveUtil(int[][] board, int row, int col, ArrayList<ArrayList<Integer>> master) {
		if(row==9) {
			return true;
		}
		
		ArrayList<Integer> nextIndex = new ArrayList<Integer>();
		if(col<8) {
			nextIndex.add(row);
			nextIndex.add(col+1);
		}else {
			nextIndex.add(row+1);
			nextIndex.add(0);
		}
		
		if (board[row][col] != 0) {
			if(col<8) {
				if (solveUtil(board, row, col+1, master)) {
					return true;
				}else if(!master.contains(nextIndex)){
					board[row][col+1] = 0;
				}
			}else {
				if (solveUtil(board, row+1, 0, master)) {
					return true;
				}else if(!master.contains(nextIndex)){
					board[row+1][0] = 0;
				}
			}
		}else {
		
		
			for (int k=1; k<10; k++){
				if (check(board, k, row, col)) {
					board[row][col] = k;
					if(col<8) {
						if (solveUtil(board, row, col+1, master)) {
							return true;
						}else if(!master.contains(nextIndex)){
							board[row][col+1] = 0;
						}
					}else {
						if (solveUtil(board, row+1, 0, master)) {
							return true;
						}else if(!master.contains(nextIndex)){
							board[row+1][0] = 0;
						}
					}
				}
			}
		}
		return false;
	}
		
	
	public static boolean checkRowCol(int[][] board, int i, int row, int col) {
		for(int b=0; b<9; b++) {
			if(board[row][b] == i) {
				return false;
			}
		}
		for(int a=0; a<9; a++) {
			if(board[a][col] == i) {
				return false;
			}
		}
		
		return true;
	}
	
	public static boolean checkBox(int[][] board, int i, int row, int col) {
		if(row<3) {
			if(col<3) {
				for(int a=0; a<3; a++) {
					for(int b=0; b<3; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
			}else if(col<6) {
				for(int a=0; a<3; a++) {
					for(int b=3; b<6; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
				
			}else {
				for(int a=0; a<3; a++) {
					for(int b=6; b<9; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
			}
		}else if(row<6) {
			if(col<3) {
				for(int a=3; a<6; a++) {
					for(int b=0; b<3; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
			}else if(col<6) {
				for(int a=3; a<6; a++) {
					for(int b=3; b<6; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
			}else {
				for(int a=3; a<6; a++) {
					for(int b=6; b<9; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
			}
		}else {
			if(col<3) {
				for(int a=6; a<9; a++) {
					for(int b=0; b<3; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
			}else if(col<6) {
				for(int a=6; a<9; a++) {
					for(int b=3; b<6; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
			}else {
				for(int a=6; a<9; a++) {
					for(int b=6; b<9; b++) {
						if(board[a][b] == i) {
							return false;
						}
					}
				}
			}
		}
		
		return true;
	}
	
	public static boolean check(int[][] board, int i, int row, int col) {
		if(checkRowCol(board, i, row, col) && checkBox(board, i, row, col)) {
			return true;
		}else {
			return false;
		}
	}
}