#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

struct IgracStatistika
{
    string ime;
    int pobjede;
    int odigrane_igre;

    IgracStatistika(string n = "", int p = 0, int o = 0) : ime(n), pobjede(p), odigrane_igre(o) {}

    double postotak_pobjeda() const
    {
        return odigrane_igre > 0 ? (double)pobjede / odigrane_igre * 100 : 0;
    }
};

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

int ucitajLeaderboard(IgracStatistika leaderboard[], int maxIgraca)
{
    ifstream file("leaderboard.txt");
    string ime;
    int pobjede, odigrane;
    int brojIgraca = 0;

    while (file >> ime >> pobjede >> odigrane && brojIgraca < maxIgraca)
    {
        leaderboard[brojIgraca] = IgracStatistika(ime, pobjede, odigrane);
        brojIgraca++;
    }
    file.close();
    return brojIgraca;
}

void spremiLeaderboard(IgracStatistika leaderboard[], int brojIgraca)
{
    ofstream file("leaderboard.txt");
    for (int i = 0; i < brojIgraca; i++)
    {
        file << leaderboard[i].ime << " " << leaderboard[i].pobjede << " " << leaderboard[i].odigrane_igre << endl;
    }
    file.close();
}

int azurirajStatistiku(IgracStatistika leaderboard[], int brojIgraca, const string &pobjednik, const string &igrac1, const string &igrac2, int maxIgraca)
{
    bool pronadjen_igrac1 = false, pronadjen_igrac2 = false;

    for (int i = 0; i < brojIgraca; i++)
    {
        if (leaderboard[i].ime == igrac1)
        {
            leaderboard[i].odigrane_igre++;
            if (pobjednik == igrac1)
                leaderboard[i].pobjede++;
            pronadjen_igrac1 = true;
        }
        if (leaderboard[i].ime == igrac2)
        {
            leaderboard[i].odigrane_igre++;
            if (pobjednik == igrac2)
                leaderboard[i].pobjede++;
            pronadjen_igrac2 = true;
        }
    }

    if (!pronadjen_igrac1 && brojIgraca < maxIgraca)
    {
        int pobjede = (pobjednik == igrac1) ? 1 : 0;
        leaderboard[brojIgraca] = IgracStatistika(igrac1, pobjede, 1);
        brojIgraca++;
    }
    if (!pronadjen_igrac2 && brojIgraca < maxIgraca)
    {
        int pobjede = (pobjednik == igrac2) ? 1 : 0;
        leaderboard[brojIgraca] = IgracStatistika(igrac2, pobjede, 1);
        brojIgraca++;
    }

    return brojIgraca;
}

void sortirajLeaderboard(IgracStatistika leaderboard[], int brojIgraca)
{
    for (int i = 0; i < brojIgraca - 1; i++)
    {
        for (int j = 0; j < brojIgraca - i - 1; j++)
        {
            bool treba_zamjena = false;

            if (leaderboard[j].pobjede < leaderboard[j + 1].pobjede)
            {
                treba_zamjena = true;
            }
            else if (leaderboard[j].pobjede == leaderboard[j + 1].pobjede)
            {
                if (leaderboard[j].postotak_pobjeda() < leaderboard[j + 1].postotak_pobjeda())
                {
                    treba_zamjena = true;
                }
            }

            if (treba_zamjena)
            {
                IgracStatistika temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}

void prikaziLeaderboard()
{
    const int MAX_IGRACA = 100;
    IgracStatistika leaderboard[MAX_IGRACA];
    int brojIgraca = ucitajLeaderboard(leaderboard, MAX_IGRACA);

    if (brojIgraca == 0)
    {
        cout << "🏆 LEADERBOARD 🏆" << endl;
        cout << "Nema još odigranih igara!" << endl;
        return;
    }

    sortirajLeaderboard(leaderboard, brojIgraca);

    cout << "🏆 LEADERBOARD 🏆" << endl;
    cout << "==============================================" << endl;
    cout << left << setw(15) << "IGRAČ" << setw(10) << "POBJEDE"
         << setw(12) << "ODIGRANE" << "POSTOTAK" << endl;
    cout << "==============================================" << endl;

    for (int i = 0; i < brojIgraca; i++)
    {
        cout << left << setw(15) << leaderboard[i].ime
             << setw(10) << leaderboard[i].pobjede
             << setw(12) << leaderboard[i].odigrane_igre
             << fixed << setprecision(1) << leaderboard[i].postotak_pobjeda() << "%" << endl;
    }
    cout << "==============================================" << endl;
}

int main()
{
    int izbor;
    cout << "       🚢 Tin Svinjaric i Matija Štublin 💥" << endl;
    cout << "  ____        _   _   _      ____  _     _ " << endl
         << " | __ )  __ _| |_| |_| | ___/ ___|| |__ (_)_ __" << endl
         << " |  _ \\ / _` | __| __| |/ _ \\___ \\| '_ \\| | '_ \\" << endl
         << " | |_) | (_| | |_| |_| |  __/___) | | | | | |_) |" << endl
         << " |____/ \\__,_|\\__|\\__|_|\\___|____/|_| |_|_| .__/ " << endl
         << "                                          |_|    " << endl;
    cout << endl;
    int igracNaRedu = 1;

    while (1)
    {
        cout << "Izbornik:" << endl;
        cout << "1. Pravila📖" << endl;
        cout << "2. Igraj🚢" << endl;
        cout << "3. Leaderboard🏆" << endl;
        cout << "4. Izlaz🚫" << endl;
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
                        cout << "Pogodak! 🚀" << endl
                             << endl;
                        hit1++;
                        ploca2[red][stupac] = 'H';
                    }
                    else
                    {
                        cout << "Promasaj! ❌" << endl
                             << endl;
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
                        cout << endl;
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

            string pobjednik;
            if (hit1 == 5)
            {
                cout << "🏆 Pobjednik je " << igrac1 << "! 🏆" << endl
                     << endl;
                pobjednik = igrac1;
            }
            else
            {
                cout << "🏆 Pobjednik je " << igrac2 << "! 🏆" << endl
                     << endl;
                pobjednik = igrac2;
            }

            const int MAX_IGRACA = 100;
            IgracStatistika leaderboard[MAX_IGRACA];
            int brojIgraca = ucitajLeaderboard(leaderboard, MAX_IGRACA);
            brojIgraca = azurirajStatistiku(leaderboard, brojIgraca, pobjednik, igrac1, igrac2, MAX_IGRACA);
            spremiLeaderboard(leaderboard, brojIgraca);

            cout << "Statistike su ažurirane! 📊" << endl;
        }
        else if (izbor == 3)
        {
            prikaziLeaderboard();
        }
        else if (izbor == 4)
        {
            cout << "    _    _            _         _    _        _____                      _  " << endl
                 << "   | |  | |          | |       | \\ | |       |_   _|                    (_) " << endl
                 << "   | |__| |_   ____ _| | __ _  |  \\| | ___     | |  ___ ___ __ _ -__  - _  _ " << endl
                 << "   |  __  \\ \\ / / ` | |/ ` | | . ` |/ `_ |     | |/ _` | '__/ `_ | '_ \\| | |  | |" << endl
                 << "   | |  | |\\ v / (_| | | (_| | | |\\  | (_| |  _| | ||_(_| | | | (_| | | | | |_| | " << endl
                 << "   |_|  |_| \\_/ \\__,_|_|\\__,_| |_| \\_|\\__,_| |_____\\__, |_|  \\__,_|_| |_| |\\__,_|" << endl
                 << "                                                    __/ |              _/ |      " << endl
                 << "                                                   |___/              |__/       " << endl;
            break;
        }
        else
        {
            cout << "Krivi unos. " << endl;
        }
        cout << endl
             << endl
             << endl;
    }
    return 0;
}