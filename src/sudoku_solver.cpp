#include <iostream>
#include <time.h>
#define CLEARSCREEN "\n\n\n"
using namespace std;

void fillsudoku(int **a);
void printsudoku(int **a);
bool sudokuBacktracking(int **a);
int findNextEmptyCell(int **a);
bool checkRowColumnCell(int **a,int row,int column,int num);

int main() {
    int **a = (int**)calloc(9,sizeof(int*));
    cout << "======== Sudoku Solver ========\n\n";
    for(int i = 0;i < 9;i++)
        a[i] = (int*)calloc(9,sizeof(int));
    fillsudoku(a);
    clock_t start = clock();
    sudokuBacktracking(a);
    clock_t end = clock();
    cout << "Solved Sukodu:\n";
    printsudoku(a);
    double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC;
    cout << "Elapsed time = " << elapsed_time << "s" << endl;
    return 0;
}

int findNextEmptyCell(int **a) {
    bool flag = 0;
    int pos = -1;
    for(int i = 0;i < 9;i++) {
      for(int j = 0;j < 9;j++) {
        if(a[i][j] == 0) {
          flag = 1;
          pos = 10*i+j;
          break;
        }
      }
      if(flag == 1)
          break;
    }
    return pos;
}

bool sudokuBacktracking(int **a) {
    int row = 0,column = 0,pos = -1;
    bool flag01 = 0,flag02 = 0;
    pos = findNextEmptyCell(a);
    if(pos == -1)
      return 1;
    row = pos / 10;
    column = pos % 10;
    for(int num = 1; num < 10; num++) {
      flag01 = checkRowColumnCell(a,row,column,num);
      if(flag01 == 1)
        continue;
      a[row][column] = num;
      // printsudoku(a);
      flag02 = sudokuBacktracking(a);
      if(flag02 == 0)
        continue;
      else if (flag02 == 1)
        return 1;
    }
    a[row][column] = 0;
    return 0;
}

bool checkRowColumnCell(int **a,int row,int column,int num) {  // Flag == 1 if the number is covered, Flag == 0 if the number is not covered
    int cellRow = 0, cellColumn = 0;
    cellRow = (row/3 == 0) ? 0 : (row/3 == 1) ? 3 : 6;
    cellColumn = (column/3 == 0) ? 0 : (column/3 == 1) ? 3 : 6;
    for(int j = 0;j < 9;j++) {                           // Check row
      if(j == column)
        continue;
      else if (a[row][j] == num) {
        return 1;
      }
    }
    for(int i = 0;i < 9;i++) {                           // Check column
      if(i == row)
        continue;
      else if (a[i][column] == num) {
        return 1;
      }
    }
    for(int i = cellRow; i < cellRow + 3; i++) {         // Check cell
        for(int j = cellColumn; j < cellColumn + 3; j++) {
            if((i == row) && (j == column))
                continue;
            else if(a[i][j] == num)
                return 1;
        }
    }
    return 0;
}

void printsudoku(int **a) {
    cout << CLEARSCREEN;
    cout << "+-------+-------+-------+\n";
    for(int i = 0; i < 9; i++) {
        if(((i % 3) == 0) && (i != 0))
            cout << "+-------+-------+-------+\n";
        for(int j = 0; j < 9; j+=3) {
            cout << "| " << (((a[i][j] > 0) && (a[i][j] < 10)) ? ((char)(a[i][j] + 48)) : '.') << ' ' << (((a[i][j+1] > 0) && (a[i][j+1] < 10)) ? ((char)(a[i][j+1] + 48)) : '.') << ' ' <<  (((a[i][j+2] > 0) && (a[i][j+2] < 10)) ? ((char)(a[i][j+2] + 48)) : '.') << ' ';
        }
        cout << "|\n";
    }
    cout << "+-------+-------+-------+\n";
}

void fillsudoku(int **a) {
  int r = 0, c = 0, n = 0, input = 0, temp = 0;
  char ch;
  for( ; ; ) {
      cout << "Enter cell's info: ";
      scanf("%d",&input);
      r = (input / 100) - 1;
      c = ((input % 100) / 10) - 1;
      n = input % 10;
      if((r > 8) || (c > 8))
          break;
      a[r][c] = n;
  }
  for( ; ; ) {
    printsudoku(a);
    cout << "\n\n\nIs that correct? [y/n]\n";
    cin >> ch;
    if(ch == 'y' || c == 'Y')
      break;
    else if(ch == 'n' || c == 'N') {
      for( ; ; ) {
          cout << "Enter cell's position you want to move from: ";
          scanf("%d",&input);
          r = input / 10 - 1;
          c = input % 10 - 1;
          if((r > 8) || (c > 8))
              break;
          temp = a[r][c];
          a[r][c] = 0;
          cout << "Enter cell's position you want to move to: ";
          scanf("%d",&input);
          r = input / 10 - 1;
          c = input % 10 - 1;
          a[r][c] = temp;
      }
    }
  }
}
