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

Jugador ganador(Jugador &J1, Jugador &J2, string puntos)
{
    int i, j;
    i = 0;
    j = 2;

    int sets1, sets2;
    sets1 = sets2 = 0;

    // sumar partidos jugados;
    while (i <= puntos.length())
    {
        if (puntos[i] == '1' and puntos[j] == '0')
        {
            // J1 ++ partido ganado
            // J2 ++ partido perdido
            return J1;
        }
        else if (puntos[i] == '0' and puntos[j] == '1')
            // J2 ++ partido ganado
            // J1 ++ partido perdido
            return J2;

        // sumar juegos;
        if (puntos[i] > puntos[j])
        {
            ++sets1;
        }
        else
            ++sets2;

        i += 4;
        j += 4;
    }

    if (sets1 > sets2)
        return J1;
    else
        return J2;
}

Jugador leer_resultados_i(const BinTree<Jugador> &A)
{
    string puntos;
    cin >> puntos;
    if (puntos == "0")
    {
        return A.value();
    }
    else
    {

        Partido match;
        match.first = leer_resultados_i(A.left());
        match.second = leer_resultados_i(A.right());

        Jugador Ganador = ganador(match.first, match.second, puntos);
        cout << match.first.ranking << '.' << match.first.name << " vs " << match.second.ranking << '.' << match.second.name << endl;
        cout << "resultados: " << puntos << endl;
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
