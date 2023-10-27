#include <stdlib.h>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;
typedef int* IntArrayPtr;

void Initialize1(int a[][9]);
void Initialize2(int a[][9]);
void Display(int a[][9]);
void Found(int, int, int a[][9]);
bool FillIn(int a[][9]);
bool SolveNum(int n, int a[][9]);
void SolveAll(int a[][9]);
bool IsComplete(int a[][9]);
bool IsContradiction(int a[][9]);
void CopyArray(int a[][9], int b[][9]);
void Guess(int a[][9]);

/*
int main(void) {
  int box[9][9];
  Initialize1(box);
  cout << IsContradiction(box);
  system("PAUSE");
}
*/

int main(void) {
  int box[9][9];
  Initialize1(box);
  char choice;
  cout << "**********************************************************************" << "\n";
  cout << "*                 The End All Kick-Ass Sudoku Solver                 *" << "\n";
  cout << "*                       of All Time (EAKASSAT)                       *" << "\n";
  cout << "**********************************************************************" << "\n";

  while (1) {
    cout << "**********************************************************************" << "\n";
    cout << "*   A - Input values                                                 *" << "\n";
    cout << "*   B - Switch value                                                 *" << "\n";
    cout << "*   C - Display boxes                                                *" << "\n";
    cout << "*   D - Solve for a number                                           *" << "\n";
    cout << "*   E - Solve for all                                                *" << "\n";
    cout << "*   Q - Quit                                                         *" << "\n";
    cout << "**********************************************************************" << "\n";
    cout << "  Enter menu selection : ";
    cin >> choice;
    if (choice=='q' || choice=='Q')
      break;
    else if (choice=='a' || choice=='A') {
      double tempD;
      int tempI;
      cout << "\n" << "Input an integer between 1 and 9, or input a 0 for an unknown value." << "\n";
      for (int j=0; j<9; j++) {
        for (int i=0; i<9; i++) {
          do {
            cout << "Column " << i+1 << ", Row " << j+1 << " : ";
            cin >> tempD;
            tempI = static_cast<int>(tempD);
            if (tempI!=tempD || tempD>9 || tempD<0) {
              cout << "\n" << "Input an integer between 0 and 9!" << "\n";
              tempD = -1;
            }
          } while (tempD==-1);
          box[i][j] = tempI;
        }
      }
      cout << "\n";
    }
    else if (choice=='b' || choice=='B') {
      double tempD;
      int tempI, i, j;
      cout << "\n" << "Input an integer between 1 and 9" << "\n";
      do {
        cout << "Column: ";
        cin >> tempD;
        tempI = static_cast<int>(tempD);
        if (tempI!=tempD || tempD>9 || tempD<1) {
          cout << "\n" << "Input an integer between 1 and 9!" << "\n";
          tempD = -1;
        }
      } while (tempD==-1);
      i = tempI-1;
      do {
        cout << "Row: ";
        cin >> tempD;
        tempI = static_cast<int>(tempD);
        if (tempI!=tempD || tempD>9 || tempD<1) {
          cout << "\n" << "Input an integer between 1 and 9!" << "\n";
          tempD = -1;
        }
      } while (tempD==-1);
      j = tempI-1;

      cout << "\n" << "Input an integer between 1 and 9, or input a 0 for an unknown value." << "\n";
      do {
        cout << "Column " << i+1 << ", Row " << j+1 << " : ";
        cin >> tempD;
        tempI = static_cast<int>(tempD);
        if (tempI!=tempD || tempD>9 || tempD<0) {
          cout << "\n" << "Input an integer between 0 and 9!" << "\n";
          tempD = -1;
        }
      } while (tempD==-1);
      box[i][j] = tempI;
      cout << "\n";
    }
    else if (choice=='c' || choice=='C') {
      Display(box);
    }
    else if (choice=='d' || choice=='D') {
      int temp[9][9];
      Initialize2(temp);
      double tempD;
      int tempI, number;
      cout << "\n" << "Input the number to solve for: ";
      do {
        cin >> tempD;
        tempI = static_cast<int>(tempD);
        if (tempI!=tempD || tempD>9 || tempD<1) {
          cout << "\n" << "Input an integer between 1 and 9!" << "\n";
          tempD = -1;
        }
      } while (tempD==-1);
      number = tempI;
      SolveNum(number, box);
      Display(box);
    }
    else if (choice=='e' || choice=='E') {
      int timeStart = clock();
      Guess(box);
      int timeEnd = clock();
      Display(box);
      double seconds = (timeEnd - timeStart) * 1.0 / CLOCKS_PER_SEC;
      cout << "Time(s): " << seconds << "\n\n";
      if (IsContradiction(box)) {
        cout << "Error: There was a problem!" << "\n" << "\n";
      }
    }
    else
      cout << "\n" << "    Error: Invalid choice.  Please enter A, B, C, D, E, or Q." << "\n" << "\n";
  }
}



void Initialize1(int a[][9]) {

  int temp[9][9] = {
    {8,0,0, 0,0,0, 0,0,0},
    {0,0,3, 6,0,0, 0,0,0},
    {0,7,0, 0,9,0, 2,0,0},

    {0,5,0, 0,0,7, 0,0,0},
    {0,0,0, 0,4,5, 7,0,0},
    {0,0,0, 1,0,0, 0,3,0},

    {0,0,1, 0,0,0, 0,6,8},
    {0,0,8, 5,0,0, 0,1,0},
    {0,9,0, 0,0,0, 4,0,0},
  };

  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      a[i][j] = temp[j][i];
    }
  }
}

void Initialize2(int a[][9]) {
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      a[i][j] = 0;
    }
  }
}

void Display(int a[][9]) {
  cout << "\n";
  for (int j=0; j<9; j++) {
    if (j%3 == 0) cout << " *******************************" << "\n";
    cout << " ";
    for (int i=0; i<9; i++) {
      if (i%3 == 0) cout << "*";
      if (a[i][j]!=0) cout << " " << a[i][j] << " ";
      else cout << "   ";
    }
    cout << "*" << "\n";
  }
  cout << " *******************************" << "\n" << "\n";
}

void Found(int x, int y, int a[][9]) {
  for (int j=0; j<9; j++) {
    for (int i=0; i<9; i++) {
      if ((i==x || j==y) && !(i==x && j==y) && a[i][j]!=2) a[i][j] = 1;
    }
  }
  for (int j=y-y%3; j<3+y-y%3; j++) {
    for (int i=x-x%3; i<3+x-x%3; i++) {
      if ((i!=x || j!=y) && a[i][j]!=2) a[i][j] = 1;
    }
  }
}

bool FillIn(int a[][9]) {
  bool change = false;
  for (int n=0; n<3; n++) {
    for (int m=0; m<3; m++) {
      int needFill=0;
      for (int j=n*3; j<n*3+3; j++) {
        for (int i=m*3; i<m*3+3; i++) {
          if (a[i][j]==0) needFill++;
          if (a[i][j]==2) needFill=10;
        }
      }
      if (needFill==1) {
        for (int j=n*3; j<n*3+3; j++) {
          for (int i=m*3; i<m*3+3; i++) {
            if (a[i][j]==0) a[i][j]=2;
            change = true;
          }
        }
      }
    }
  }
  for (int i=0; i<9; i++) {
    int needFill=0;
    for (int j=0; j<9; j++) {
      if (a[i][j]==0) needFill++;
      if (a[i][j]==2) needFill=10;
    }
    if (needFill==1) {
      for (int j=0; j<9; j++) {
        if (a[i][j]==0) a[i][j]=2;
        change = true;
      }
    }
  }
  for (int j=0; j<9; j++) {
    int needFill=0;
    for (int i=0; i<9; i++) {
      if (a[i][j]==0) needFill++;
      if (a[i][j]==2) needFill=10;
    }
    if (needFill==1) {
      for (int i=0; i<9; i++) {
        if (a[i][j]==0) a[i][j]=2;
        change = true;
      }
    }
  }
  return change;
}

bool SolveNum(int number, int box[][9]) {
  int temp[9][9];
  Initialize2(temp);
  bool change1=false, change2=false;
  for (int j=0; j<9; j++) {
    for (int i=0; i<9; i++) {
      if (box[i][j]!=0) temp[i][j] = 1;
      if (box[i][j]==number) {
        temp[i][j] = 2;
      }
    }
  }
  do {
    for (int j=0; j<9; j++) {
      for (int i=0; i<9; i++) {
        if (temp[i][j]==2) Found(i,j,temp);
      }
    }
    change2 = FillIn(temp);
    if (change2) change1=true;
  } while(change2==true);
  for (int j=0; j<9; j++) {
    for (int i=0; i<9; i++) {
      if (temp[i][j]==2) box[i][j]=number;
    }
  }
  return change1;
}

void SolveAll(int box[][9]) {
  bool restart;
  do {
    restart = false;
    for (int i=1; i<10; i++) {
      if (SolveNum(i, box)) restart = true;
    }
  } while (restart);
}

bool IsComplete(int box[][9]) {
  bool completion = true;
  for (int j=0; j<9; j++) {
    for (int i=0; i<9; i++) {
      if (box[i][j]==0) completion = false;
    }
  }
  return completion;
}

bool IsContradiction(int box[][9]) {
  bool contradiction = false;
  for (int j=0; j<9; j++) {
    for (int i=0; i<9; i++) {
      if (box[i][j]!=0) {
        for (int n=j-j%3; n<j-j%3+2; n++) {
          for (int m=i-i%3; m<i-i%3+2; m++) {
            if (box[m][n] == box[i][j] && !(i==m && j==n)) contradiction = true;
          }
        }
        for (int n=0; n<9; n++) {
          if (box[i][n] == box[i][j] && j!=n) contradiction = true;
        }
        for (int m=0; m<9; m++) {
          if (box[m][j] == box[i][j] && i!=m) contradiction = true;
        }
      }
    }
  }
  return contradiction;
}

void Copy(int a[][9], int b[][9]) {
  for (int j=0; j<9; j++) {
    for (int i=0; i<9; i++) {
      a[i][j] = b[i][j];
    }
  }
}

void Guess(int box[][9]) {
  SolveAll(box);
  if (!IsComplete(box) && !IsContradiction(box)) {
    int x=10, y=10, num=9;
      for (int j=8; j>=0; j--) {
      for (int i=8; i>=0; i--) {
        if (box[i][j]==0) {
          x=i;
          y=j;
        }
      }
    }
    if (x!=10) {
      int temp[9][9];
      Copy(temp, box);
      do {
        box[x][y] = num;
        if (!IsContradiction(box)) Guess(box);
        if (!IsComplete(box) || IsContradiction(box)) Copy(box, temp);
        num--;
      } while (num>0 && !IsComplete(box));
    }
  }
}






