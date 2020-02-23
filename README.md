# Sudoku Solver

Description:
A handy sudoku solving program



Installation instructions:
1. mkdir build
2. cd build
3. cmake ..
4. make
5. ./sudoku



How to use:

Enter cell's info format is row,column,value without the commas.
E.g. if you want to put number 6 in (1,3) position then you type 136 and hit enter
When you are done putting all the values from the given sudoku, just type any (4+)-digit number e.g. 1369, 42017
The program will understand that the input is invalid and will proceed to print a pictographic view of the given sudoku
If there was a mistake in your typing and you want to move a value to another cell then type 'n' when asked if the sudoku entered is correct.
