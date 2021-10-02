#include <iostream> // cin cout
#include <string>
#include <vector>
#include <algorithm> // shuffle
#include <random>    // rand
#include <time.h>    // time reset seed
#include <fstream>   // file

/*

TP: Mot mystère, peut se jouer tout seul ou à plusieure. Pour gagner il faut trouver le mot mélanger.

DO:

-game loop
-multijoueur avec un vector de la struct PLAYER
- 2 mode un ou le mot est choisi aléatoirement dans un fichier et l'autre ou c'est un des joueurs qui choisi


*/

using namespace std;

//structure
struct PLAYER
{
    string name;
    string word;
    int nbre_coup;
    int nbr_pts;
    int playerStatu; // joueur ou pas 0: joueur 1: admin 2: mort
} player_member;

//prototype
void game(int choise, int nbreJoueur, vector<PLAYER> Players);
string getWord();

int main()
{

    cin.clear();
    int play(1);   // savoir Si ils rejouent
    int choise(0); // choix du joueur
    char replay;   // savoir si il veut rejouer
    //Présentation

    cout << "Bienvenue au jeux WORDSHUFFLE !!" << endl
         << endl;

    //TODO: 4: systeme pour rejouer au jeux
    while (play == 1)
    {
        int nbrPlayer;
        vector<PLAYER> Players;

        cout << "Nombre de joueur(s): ";
        cin >> nbrPlayer;
        cin.ignore();

        for (int i(0); i < nbrPlayer; i++)
        {
            string name;
            cout << "Pseudo joueur " << i + 1 << " : ";
            cin >> name;
            Players.push_back(PLAYER());
            Players[i].name = name;
            Players[i].nbre_coup = 10;
            Players[i].playerStatu = 0;
            name.clear();
            cin.ignore();
        }

        cout << "1: solo" << endl
             << "2: Joueur vs Joueur" << endl;
        cin >> choise;
        switch (choise)
        {
        case 1:
            game(1, nbrPlayer, Players);
            break;
        case 2:
            game(2, nbrPlayer, Players);
            break;
        }
        cout << "Replay: (Y/n): ";
        cin >> replay;
        if (replay != 'Y')
        {
            cout << "Au revoir !!" << endl;
            play = 0;
        }
    }

    return 0;
}

void game(int choise, int nbreJoueur, vector<PLAYER> Players)
{
    //1: On demande de saisir un mot
    string wordShuffle; // mot saisi par le joueur 1
    string wordToFind;  // mot non mélanger

    //reset the seed
    srand(time(NULL));

    int nbrCoup(10);
    int play(1);
    int myRandom(rand() % nbreJoueur);
    int nbrPlayerDead(0);

    cout << "MyRandom: " << myRandom << endl;

    if (choise == 2)
    {
        cout << Players[myRandom].name << " donner un mot: ";
        Players[myRandom].playerStatu = 1;
        nbreJoueur -= 1;
        cin >> wordShuffle;
    }
    else
    {
        //function fichier
        wordShuffle = getWord();
    }
    wordToFind = wordShuffle;

    cout << "\033[2J\033[1;1H"; //system("clear"); sans bug

    //2: On mélange le mot
    random_shuffle(wordShuffle.begin(), wordShuffle.end());

    //3: On demande à l'utilisateur quel est le mot mystère
    while (play == 1)
    {
        for (int i(0); i <= nbreJoueur; i++)
        {

            cout << "\033[2J\033[1;1H"; //system("clear"); sans bug

            if (Players[i].playerStatu == 1 || Players[i].playerStatu == 2)
            {
                if (i < nbreJoueur && Players[i].playerStatu != 2 || 1) // test si le joueur suivant peut jouer
                {
                    i++;
                }
                //continue;
            }

            cin.ignore();

            cout << "Au tour de: " << Players[i].name << endl
                 << endl;
            cout << "il te reste: " << Players[i].nbre_coup << " coups" << endl;
            cout << "Quel est le mot: " << wordShuffle << endl
                 << endl;

            cin >> Players[i].word;

            if (Players[i].word == wordToFind)
            {
                cout << "Bravo " << Players[i].name << " à gagner" << endl;
                play = 0;
                break;
            }
            else
            {
                cout << "Ce n'est pas le bom mot !" << endl;
                Players[i].nbre_coup--;
            }
            if (Players[i].nbre_coup == 0)
            {
                cout << Players[i].name << " à perdu !!" << endl;
                Players[i].playerStatu = 2;
                nbrPlayerDead++;
            }
            if (nbrPlayerDead == nbreJoueur)
            {
                cout << Players[myRandom].name << " a gagner BRAVO !!" << endl;
                play = 0;
            }
        }
    }
}

string getWord()
{
    ifstream wordlist("../wordlist.txt");
    if (!wordlist)
    {
        cout << "ERROR open file";
    }
    string unused;
    vector<string> wordToFind;
    int randomLine(0);

    while (getline(wordlist, unused))
    {
        wordToFind.push_back(unused);
    }

    srand(time(NULL));
    randomLine = rand() % wordToFind.size();

    return wordToFind[randomLine];

    return "yo";
}
