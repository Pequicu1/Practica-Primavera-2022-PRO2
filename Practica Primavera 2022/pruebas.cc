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

// typedef pair<Jugador, Jugador> Partido;

struct Partido
{
    Jugador J1;
    Jugador J2;
    string puntos;
};

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

Jugador leer_resultados_i(const BinTree<Jugador> &A, BinTree<Partido> &Res)
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
        match.J1 = leer_resultados_i(A.left(), Res);
        match.J2 = leer_resultados_i(A.right(), Res);
        Jugador Ganador = ganador(match.J1, match.J2, puntos);

        // leer_resultados_i(A.left(), Res);
        // leer_resultados_i(A.right(), Res);

        Res = BinTree<Partido>(match);
        return Ganador;
    }
}

void imprimir_resultados(const BinTree<Partido> &Res)
{
    cout << Res.value().J1.ranking << '.' << Res.value().J1.name << " vs " << Res.value().J2.ranking << '.' << Res.value().J2.name << ' ' << Res.value().puntos;
    imprimir_resultados(Res.left());
    imprimir_resultados(Res.right());
}

void leer_resultados(const BinTree<Jugador> &A)
{
    BinTree<Partido> Resultados;
    leer_resultados_i(A, Resultados);
    imprimir_resultados(Resultados);
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
