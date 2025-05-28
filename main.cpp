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
                cout << "🌊 ";
            else if (ploca[i][j] == 'B' && ispisBroda == 1)
                cout << "🚢 ";
            else if (ploca[i][j] == 'B' && ispisBroda == 0)
                cout << "🌊 ";
            else if (ploca[i][j] == 'H')
                cout << "💥 ";
            else if (ploca[i][j] == 'X')
                cout << "❌ ";
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
    cout << "       🚢 Tin Svinjaric i Matija Štublin 💥" << endl;
    cout << "  ____        _   _   _      ____  _     _ " << endl
         << " | __ )  __ _| |_| |_| | ___/ ___|| |__ (_)_ __" << endl
         << " |  _ \\ / _` | __| __| |/ _ \\___ \\| '_ \\| | '_ \\" << endl
         <<   " | |_) | (_| | |_| |_| |  __/___) | | | | | |_) |" << endl
         << " |____/ \\__,_|\\__|\\__|_|\\___|____/|_| |_|_| .__/ " << endl
         << "                                          |_|    " << endl;
    cout << endl;
    int igracNaRedu = 1;
    while (1)
    {
        cout << "Izbornik:" << endl;
        cout << "1. Pravila📖" << endl;
        cout << "2. Igraj🚢" << endl;
        cout << "3. Izlaz🚫" << endl;
        cout << "Unesite vaš izbor:";
        cin >> izbor;
        system("clear");
        if (izbor == 1)
        {
            cout << "Pravila igre:" << endl;
            cout << "1. Igra je za dva igraca." << endl;
            cout << "2. Igrači postavljaju 5 brodova na plocu." << endl;
            cout << "3. Cilj igre je prvi potpiti sve protivničke brodove." << endl;
            cout << endl;
        }
        else if (izbor == 2)
        {
            cout << "💥 POTAPANJE BRODOVA🚢" << endl;
            char ploca1[10][10], ploca2[10][10];
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    ploca1[i][j] = 'V';
                    ploca2[i][j] = 'V';
                }
            }
            string igrac1, igrac2;
            cout << "Unesite ime prvog igraca: ";
            cin.ignore();
            getline(cin, igrac1);

            cout << "Unesite ime drugog igraca: ";
            getline(cin, igrac2);

            cout << endl;
            cout << "Igrac 1 je: " << igrac1 << endl;
            cout << "Igrac 2 je: " << igrac2 << endl;
            cout << endl;
            cout << "Ploca igraca 1(" << igrac1 << "):" << endl;
            ispisPloce(ploca1, 0);
            cout << endl;
            cout << "Ploca igraca 2(" << igrac2 << "):" << endl;
            ispisPloce(ploca2, 0);
            cout << endl;
            int red, stupac, brodovi = 5;
            cout << igrac1 << ", postavi svoje brodove:" << endl;
            for (int i = 0; i < brodovi; i++)
            {
                do
                {
                    cout << "Unesi koordinate na ploci za brod " << i + 1 << ": ";
                    unosenjeKoordinata(&red, &stupac);
                } while (red < 0 || red >= 10 || stupac < 0 || stupac >= 10 || ploca1[red][stupac] == 'B');
                ploca1[red][stupac] = 'B';
            }
            cout << endl;
            system("clear");

            cout << igrac2 << ", postavi svoje brodove:" << endl;
            for (int i = 0; i < brodovi; i++)
            {
                do
                {
                    cout << "Unesi koordinate na ploci za brod " << i + 1 << ": ";
                    unosenjeKoordinata(&red, &stupac);
                } while (red < 0 || red >= 10 || stupac < 0 || stupac >= 10 || ploca2[red][stupac] == 'B');
                ploca2[red][stupac] = 'B';
            }
            cout << endl;
            system("clear");
            int hit1 = 0, hit2 = 0;
            while (hit1 < brodovi && hit2 < brodovi)
            {
                if (igracNaRedu == 1)
                {
                    cout << "Ploca protivnicikog igraca (" << igrac2 << "):" << endl;
                    ispisPloce(ploca2, 0);
                    cout << endl;
                    cout << "Ploca igraca koji je na potezu (" << igrac1 << "):" << endl;
                    ispisPloce(ploca1, 1);
                    cout << endl;

                    do
                    {
                        cout << endl;
                        cout << igrac1 << ", unesi koordinate gdje zelis ispaliti projektil: ";
                        unosenjeKoordinata(&red, &stupac);
                    } while (red < 0 || red >= 10 || stupac < 0 || stupac >= 10);

                    system("clear");

                    if (ploca2[red][stupac] == 'B')
                    {
                        cout << "Pogodak! 🚀" << endl;
                        hit1++;
                        ploca2[red][stupac] = 'H';
                    }
                    else
                    {
                        cout << "Promasaj! ❌" << endl;
                        ploca2[red][stupac] = 'X';
                    }
                    igracNaRedu = 2;
                }
                else if (igracNaRedu == 2)
                {
                    cout << "Ploca protivnicikog igraca (" << igrac1 << "):" << endl;
                    ispisPloce(ploca1, 0);
                    cout << endl;
                    cout << "Ploca igraca koji je na potezu (" << igrac2 << "):" << endl;
                    ispisPloce(ploca2, 1);
                    cout << endl;

                    do
                    {
                        cout << endl;
                        cout << igrac2 << ", unesi koordinate gdje zelis ispaliti projektil: ";
                        unosenjeKoordinata(&red, &stupac);
                    } while (red < 0 || red >= 10 || stupac < 0 || stupac >= 10);

                    system("clear");

                    if (ploca1[red][stupac] == 'B')
                    {
                        cout << "Pogodak! 🚀" << endl;
                        hit2++;
                        ploca1[red][stupac] = 'H';
                    }
                    else
                    {
                        cout << "Promasaj! ❌" << endl;
                        ploca1[red][stupac] = 'X';
                    }

                    if (igracNaRedu == 1)
                        igracNaRedu = 2;
                    else
                        igracNaRedu = 1;
                }
            }
        }
    }
return 0;
}
