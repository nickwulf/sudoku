======
Sudoku
======

Solves standard 9x9 Sudoku puzzles.

How To Use
-----------
Follow the programs prompts. Your main options are:
* A - Input a completly new unsolved puzzle
* B - Edit a single square of the puzzle
* C - Display the current puzzle
* D - Use the solver's basic rules to solve a specific number as much as possible (without guessing)
* E - Use basic rules (and guessing when necessary) to solve the whole puzzle
* Q - Quit

Alternatively, instead of entering the puzzle square-by-square every time you run the executable, it may be more convenient to directly edit the initially loaded puzzle by modifying it directly in the code, found in the ``Initialize1`` function.

Create The Executable
-----------
To run the makefile, you'll need g++, which you can easily get by installing MinGW.

Once you have g++ working, just run the makefile to create the Windows executable
