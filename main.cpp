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
void unosenjeKoordinata(int *red, int *stupac)
{
    cin >> *red >> *stupac;
    (*red)--;
    (*stupac)--;
}
int main()
{
    int izbor;
    cout << "       Tin Svinjaric i Matija Štublin" << endl;
    cout << "  ____        _   _   _      ____  _     _ " << endl
         << " | __ )  __ _| |_| |_| | ___/ ___|| |__ (_)_ __" << endl
         << " |  _ \\ / _` | __| __| |/ _ \\___ \\| '_ \\| | '_ \\" << endl
         <<   " | |_) | (_| | |_| |_| |  __/___) | | | | | |_) |" << endl
         << " |____/ \\__,_|\\__|\\__|_|\\___|____/|_| |_|_| .__/ " << endl
         << "                                          |_|    " << endl;
    cout << endl;
    int igracNaRedu = 1;

    return 0;
}
while (1)
{
    cout << "Izbornik:" << endl;
    cout << "1. Pravila" << endl;
    cout << "2. Igraj" << endl;
    cout << "3. Izlaz" << endl;
    cout << "Unesite vaš izbor:";
    cin >> izbor;
    system("clear");

return 0;
}