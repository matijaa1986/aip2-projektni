#include <iostream>
#include <iomanip>
using namespace std;

void ispisPloce(char ploca[10][10], int ispisBroda)
{
    cout << "  1  2  3  4  5  6  7  8  9  10" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << setw(2) << i + 1;
        for (int j = 0; j < 10; j++)
        {
            if (ploca[i][j] == 'V')
                cout << "~ ";
            else if (ploca[i][j] == 'B' && ispisBroda == 1)
                cout << "B ";
            else if (ploca[i][j] == 'B' && ispisBroda == 0)
                cout << "~ ";
            else if (ploca[i][j] == 'H')
                cout << "O ";
            else if (ploca[i][j] == 'X')
                cout << "X ";
        }
        cout << endl;
    }
}