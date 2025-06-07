#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string>
#include <string.h>
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

struct SpremenjenoStanje
{
    char ploca1[10][10];
    char ploca2[10][10];
    char ime1[50];
    char ime2[50];
    int hit1;
    int hit2;
    int igracNaRedu;
    int brodovi;
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

bool spremiIgru(char ploca1[10][10], char ploca2[10][10], const string &igrac1, const string &igrac2, int hit1, int hit2, int igracNaRedu, int brodovi)
{
    ofstream file("saved_game.dat", ios::binary);
    if (!file.is_open())
    {
        cout << "Greška pri spremanju igre!" << endl;
        return false;
    }

    SpremenjenoStanje stanje;

    // Kopiranje ploča
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            stanje.ploca1[i][j] = ploca1[i][j];
            stanje.ploca2[i][j] = ploca2[i][j];
        }
    }

    // Kopiranje imena (osiguravamo da su null-terminated)
    strncpy(stanje.ime1, igrac1.c_str(), 49);
    stanje.ime1[49] = '\0';
    strncpy(stanje.ime2, igrac2.c_str(), 49);
    stanje.ime2[49] = '\0';

    stanje.hit1 = hit1;
    stanje.hit2 = hit2;
    stanje.igracNaRedu = igracNaRedu;
    stanje.brodovi = brodovi;

    file.write(reinterpret_cast<const char *>(&stanje), sizeof(SpremenjenoStanje));
    file.close();

    cout << "💾 Igra je uspješno spremljena!" << endl;
    return true;
}

bool ucitajIgru(char ploca1[10][10], char ploca2[10][10], string &igrac1, string &igrac2, int &hit1, int &hit2, int &igracNaRedu, int &brodovi)
{
    ifstream file("saved_game.dat", ios::binary);
    if (!file.is_open())
    {
        cout << "Nema spremljene igre!" << endl;
        return false;
    }

    SpremenjenoStanje stanje;
    file.read(reinterpret_cast<char *>(&stanje), sizeof(SpremenjenoStanje));

    if (file.gcount() != sizeof(SpremenjenoStanje))
    {
        cout << "Greška pri učitavanju igre!" << endl;
        file.close();
        return false;
    }

    // Kopiranje podataka iz strukture
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            ploca1[i][j] = stanje.ploca1[i][j];
            ploca2[i][j] = stanje.ploca2[i][j];
        }
    }

    igrac1 = string(stanje.ime1);
    igrac2 = string(stanje.ime2);
    hit1 = stanje.hit1;
    hit2 = stanje.hit2;
    igracNaRedu = stanje.igracNaRedu;
    brodovi = stanje.brodovi;

    file.close();
    cout << "📂 Igra je uspješno učitana!" << endl;
    return true;
}

void pokreniIgru(bool ucitanaIgra = false, char ploca1[10][10] = nullptr, char ploca2[10][10] = nullptr,
                 string igrac1 = "", string igrac2 = "", int hit1 = 0, int hit2 = 0, int igracNaRedu = 1, int brodovi = 5)
{
    char lokalnaPloca1[10][10], lokalnaPloca2[10][10];
    string lokalniIgrac1, lokalniIgrac2;
    int lokalniHit1, lokalniHit2, lokalniIgracNaRedu, lokalniBrodovi;

    if (ucitanaIgra)
    {
        // Kopiraj učitane podatke
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                lokalnaPloca1[i][j] = ploca1[i][j];
                lokalnaPloca2[i][j] = ploca2[i][j];
            }
        }
        lokalniIgrac1 = igrac1;
        lokalniIgrac2 = igrac2;
        lokalniHit1 = hit1;
        lokalniHit2 = hit2;
        lokalniIgracNaRedu = igracNaRedu;
        lokalniBrodovi = brodovi;
    }
    else
    {
        // Nova igra
        cout << "💥 POTAPANJE BRODOVA🚢" << endl;

        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                lokalnaPloca1[i][j] = 'V';
                lokalnaPloca2[i][j] = 'V';
            }
        }

        cout << "Unesite ime prvog igraca: ";
        cin.ignore();
        getline(cin, lokalniIgrac1);

        cout << "Unesite ime drugog igraca: ";
        getline(cin, lokalniIgrac2);

        cout << endl;
        cout << "Igrac 1 je: " << lokalniIgrac1 << endl;
        cout << "Igrac 2 je: " << lokalniIgrac2 << endl;
        cout << endl;

        int red, stupac;
        lokalniBrodovi = 5;

        cout << lokalniIgrac1 << ", postavi svoje brodove:" << endl;
        for (int i = 0; i < lokalniBrodovi; i++)
        {
            do
            {
                cout << "Unesi koordinate na ploci za brod " << i + 1 << ": ";
                unosenjeKoordinata(&red, &stupac);
            } while (red < 0 || red >= 10 || stupac < 0 || stupac >= 10 || lokalnaPloca1[red][stupac] == 'B');
            lokalnaPloca1[red][stupac] = 'B';
        }
        cout << endl;
        system("clear");

        cout << lokalniIgrac2 << ", postavi svoje brodove:" << endl;
        for (int i = 0; i < lokalniBrodovi; i++)
        {
            do
            {
                cout << "Unesi koordinate na ploci za brod " << i + 1 << ": ";
                unosenjeKoordinata(&red, &stupac);
            } while (red < 0 || red >= 10 || stupac < 0 || stupac >= 10 || lokalnaPloca2[red][stupac] == 'B');
            lokalnaPloca2[red][stupac] = 'B';
        }
        cout << endl;
        system("clear");

        lokalniHit1 = 0;
        lokalniHit2 = 0;
        lokalniIgracNaRedu = 1;
    }

    // Glavna petlja igre
    int red, stupac;
    while (lokalniHit1 < lokalniBrodovi && lokalniHit2 < lokalniBrodovi)
    {
        if (lokalniIgracNaRedu == 1)
        {
            cout << "Ploca protivnicikog igraca (" << lokalniIgrac2 << "):" << endl;
            ispisPloce(lokalnaPloca2, 0);
            cout << endl;
            cout << "Ploca igraca koji je na potezu (" << lokalniIgrac1 << "):" << endl;
            ispisPloce(lokalnaPloca1, 1);
            cout << endl;

            cout << "Opcije: 1-Igraj potez  2-Spremi igru" << endl;
            int opcija;
            cin >> opcija;

            if (opcija == 2)
            {
                spremiIgru(lokalnaPloca1, lokalnaPloca2, lokalniIgrac1, lokalniIgrac2, lokalniHit1, lokalniHit2, lokalniIgracNaRedu, lokalniBrodovi);
                return;
            }

            do
            {
                cout << endl;
                cout << lokalniIgrac1 << ", unesi koordinate gdje zelis ispaliti projektil: ";
                unosenjeKoordinata(&red, &stupac);
            } while (red < 0 || red >= 10 || stupac < 0 || stupac >= 10);

            system("clear");

            if (lokalnaPloca2[red][stupac] == 'B')
            {
                cout << "Pogodak! 🚀" << endl
                     << endl;
                lokalniHit1++;
                lokalnaPloca2[red][stupac] = 'H';
            }
            else
            {
                cout << "Promasaj! ❌" << endl
                     << endl;
                lokalnaPloca2[red][stupac] = 'X';
            }
            lokalniIgracNaRedu = 2;
        }
        else if (lokalniIgracNaRedu == 2)
        {
            cout << "Ploca protivnicikog igraca (" << lokalniIgrac1 << "):" << endl;
            ispisPloce(lokalnaPloca1, 0);
            cout << endl;
            cout << "Ploca igraca koji je na potezu (" << lokalniIgrac2 << "):" << endl;
            ispisPloce(lokalnaPloca2, 1);
            cout << endl;

            cout << "Opcije: 1-Igraj potez  2-Spremi igru" << endl;
            int opcija;
            cin >> opcija;

            if (opcija == 2)
            {
                spremiIgru(lokalnaPloca1, lokalnaPloca2, lokalniIgrac1, lokalniIgrac2, lokalniHit1, lokalniHit2, lokalniIgracNaRedu, lokalniBrodovi);
                return;
            }

            do
            {
                cout << endl;
                cout << lokalniIgrac2 << ", unesi koordinate gdje zelis ispaliti projektil: ";
                unosenjeKoordinata(&red, &stupac);
            } while (red < 0 || red >= 10 || stupac < 0 || stupac >= 10);

            system("clear");

            if (lokalnaPloca1[red][stupac] == 'B')
            {
                cout << "Pogodak! 🚀" << endl;
                cout << endl;
                lokalniHit2++;
                lokalnaPloca1[red][stupac] = 'H';
            }
            else
            {
                cout << "Promasaj! ❌" << endl;
                lokalnaPloca1[red][stupac] = 'X';
            }
            lokalniIgracNaRedu = 1;
        }
    }

    // Završetak igre
    string pobjednik;
    if (lokalniHit1 == lokalniBrodovi)
    {
        cout << "🏆 Pobjednik je " << lokalniIgrac1 << "! 🏆" << endl
             << endl;
        pobjednik = lokalniIgrac1;
    }
    else
    {
        cout << "🏆 Pobjednik je " << lokalniIgrac2 << "! 🏆" << endl
             << endl;
        pobjednik = lokalniIgrac2;
    }

    const int MAX_IGRACA = 100;
    IgracStatistika leaderboard[MAX_IGRACA];
    int brojIgraca = ucitajLeaderboard(leaderboard, MAX_IGRACA);
    brojIgraca = azurirajStatistiku(leaderboard, brojIgraca, pobjednik, lokalniIgrac1, lokalniIgrac2, MAX_IGRACA);
    spremiLeaderboard(leaderboard, brojIgraca);

    cout << "Statistike su ažurirane! 📊" << endl;

    // Obriši spremljenu igru nakon završetka
    remove("saved_game.dat");
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

    while (1)
    {
        cout << "Izbornik:" << endl;
        cout << "1. Pravila📖" << endl;
        cout << "2. Nova igra🚢" << endl;
        cout << "3. Učitaj igru📂" << endl;
        cout << "4. Leaderboard🏆" << endl;
        cout << "5. Izlaz🚫" << endl << endl;
        cout << "Unesite vaš izbor:";
        cin >> izbor;
        system("clear");

        if (izbor == 1)
        {
            cout << "Pravila igre:" << endl;
            cout << "1. Igra je za dva igraca." << endl;
            cout << "2. Igrači postavljaju 5 brodova na plocu." << endl;
            cout << "3. Cilj igre je prvi potpiti sve protivničke brodove." << endl;
            cout << "4. Tijekom igre možete spremiti igru opcijom 2." << endl;
            cout << endl;
        }
        else if (izbor == 2)
        {
            pokreniIgru();
        }
        else if (izbor == 3)
        {
            char ploca1[10][10], ploca2[10][10];
            string igrac1, igrac2;
            int hit1, hit2, igracNaRedu, brodovi;

            if (ucitajIgru(ploca1, ploca2, igrac1, igrac2, hit1, hit2, igracNaRedu, brodovi))
            {
                pokreniIgru(true, ploca1, ploca2, igrac1, igrac2, hit1, hit2, igracNaRedu, brodovi);
            }
        }
        else if (izbor == 4)
        {
            prikaziLeaderboard();
        }
        else if (izbor == 5)
        {
            cout << "    _    _            _         _   _         _____                      _  " << endl
                 << "   | |  | |          | |       | \\ | |       |_   _|                    (_) " << endl
                 << "   | |__| |_   ____ _| | __ _  |  \\| |  ___    | |  ___ ___ __ _ -__  - _   _ " << endl
                 << "   |  __  \\ \\ / / ` | |/ ` | | . ` |/   `_ |   | |/ _` | '__/ `_ | '_ \\|  | |  | |" << endl
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