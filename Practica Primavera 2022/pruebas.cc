#include <iostream>
#include "BinTree.hh"
#include <vector>
#include <math.h>
using namespace std;

struct Jugador
{
    int ranking;
    string name;
};

typedef pair<Jugador, Jugador> Partido;

struct Cjt_Jugadores
{
    vector<Jugador> players;
};

struct Torneo
{
    BinTree<Jugador> Cuadro;
};

BinTree<Jugador> crear_torneo_i(Jugador ant, const vector<Jugador> &rank, int altura, int altura_act, int x)
{
    if (altura == altura_act)
    {
        BinTree<Jugador> a(ant);
        return a;
    }
    else if (altura - 1 == altura_act and ant.ranking <= x)
    {
        BinTree<Jugador> a(ant);
        return a;
    }
    else
    {
        int jug = pow(2, altura_act) + 1 - ant.ranking;

        BinTree<Jugador> L = crear_torneo_i(ant, rank, altura, altura_act + 1, x);
        BinTree<Jugador> R = crear_torneo_i(rank[jug - 1], rank, altura, altura_act + 1, x);

        BinTree<Jugador> Cuadro(ant, L, R);

        return Cuadro;
    }
}
void crear_torneo(const Cjt_Jugadores &jugs, Torneo &T)
{
    // altura del cuadro
    int altura = ceil(log2(jugs.players.size()) + 1);

    int x = pow(2, altura - 1) - jugs.players.size();
    T.Cuadro = crear_torneo_i(jugs.players[0], jugs.players, altura, 1, x);
}

void imprimir_cuadro(const BinTree<Jugador> &A)
{

    if (A.left().empty())
    {
        cout << A.value().ranking << '.' << A.value().name;
    }
    else
    {
        cout << '(';
        imprimir_cuadro(A.left());
        cout << ' ';
        imprimir_cuadro(A.right());
        cout << ')';
    }
}

Jugador ganador(Jugador &J1, Jugador &J2, string in)
{
    char p1, p2;
    // char coso;
    //  int sets1 = 0;
    //  int sets2 = 0;
    //  cin >> p1 >> coso >> p2;
    p1 = in[0];
    p2 = in[2];
    if (p1 == '1' and p2 == '0')
    {
        // J1.modificar_estadisticas(0, '+');
        // J2.modificar_estadisticas(0, '-');
        return J1;
    }
    else if (p1 == '0' and p2 == '1')
    {
        // J2.modificar_estadisticas(0, '+');
        // J1.modificar_estadisticas(0, '-');
        return J2;
    }
    else
        // J2 = J2;
        return J1;
}

Jugador leer_resultados_i(const BinTree<Jugador> &A)
{
    char puntos;
    cin >> puntos;
    if (puntos == '0')
    {
        return A.value();
    }
    else
    {
        // vector<vector<char>> games;

        string in;
        // bool key = true;
        cin >> in;
        /*vector<char> game;
        game.push_back(puntos);
        int i = 1;
        while (key)
        {
            if (in == ',')
            {
                games.push_back(game);
                game.clear();
            }
            else
                game.push_back(in);

            if (games.size() >= 2)
            {
                if (games[0][0] > games[0][1] and games[1][0] > games[1][1])
                    key = false;
            }
            else
                cin >> in;
            ++i;
        }

        cout << '{';
        for (int i = 0; i < games.size(); ++i)
        {
            cout << '[';
            for (int j = 0; j < game.size(); ++j)
            {
                cout << games[i][j] << ',';
            }
            cout << "],";
        }
        cout << '}' << endl;*/

        Partido match;
        match.first = leer_resultados_i(A.left());
        match.second = leer_resultados_i(A.right());

        Jugador Ganador = ganador(match.first, match.second, in);
        cout << match.first.ranking << '.' << match.first.name << " vs " << match.second.ranking << '.' << match.second.name << endl;
        cout << "resultados: " << puntos << in << endl;
        cout << "Pasa: " << Ganador.name << endl;
        // cout << "resultados : " << in << endl;
        return Ganador;
    }
}

void leer_resultados(const BinTree<Jugador> &A)
{
    if (A.empty())
        cout << "ta vacío" << endl;
    leer_resultados_i(A);
}

int main()
{
    int n;
    cin >> n;
    Cjt_Jugadores jugs;
    for (int i = 0; i < n; ++i)
    {
        Jugador P;
        cin >> P.name;
        P.ranking = jugs.players.size() + 1;
        jugs.players.push_back(P);
    }
    Torneo T;
    crear_torneo(jugs, T);
    imprimir_cuadro(T.Cuadro);
    cout << endl;
    leer_resultados(T.Cuadro);
}
