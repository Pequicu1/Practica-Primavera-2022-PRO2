/**
 * @file Torneo.cc
 * @brief Código de la clase Torneo
 * @version 0.1
 * @date 2022-04-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Torneo.hh"
#ifndef NO_DIAGRAM
#include <math.h>
#endif

Torneo::Torneo() {}

void Torneo::leer_torneo()
{
    // Asigna al torneo un identificador y una categoría que han sido leidas po el canal de entrada estándar.
    string name;
    int cat;
    cin >> name >> cat;
    identificador = name;
    categoria = cat;
}

int Torneo::consultar_categoria() const
{
    return categoria;
}

string Torneo::consultar_nombre() const
{
    return identificador;
}

Cjt_Jugadores Torneo::leer_participantes(int n, const Cjt_Jugadores &Jugs) const
{
    Cjt_Jugadores new_participantes;
    vector<Jugador> rank0 = Jugs.obtener_ranking();
    for (int i = 0; i < n; ++i)
    {
        int pos;
        cin >> pos;
        new_participantes.anadir_jugador(rank0[pos - 1]);
    }
    return new_participantes;
}

BinTree<Jugador> crear_torneo_i(Jugador ant, const vector<Jugador> &rank, int altura, int altura_act, int x)
{
    if (altura == altura_act)
    {
        BinTree<Jugador> a(ant);
        return a;
    }
    else if (altura - 1 == altura_act and ant.consultar_pos_ranking() <= x)
    {
        BinTree<Jugador> a(ant);
        return a;
    }
    else
    {
        int jug = pow(2, altura_act) + 1 - ant.consultar_pos_ranking();

        BinTree<Jugador> L = crear_torneo_i(ant, rank, altura, altura_act + 1, x);
        BinTree<Jugador> R = crear_torneo_i(rank[jug - 1], rank, altura, altura_act + 1, x);

        BinTree<Jugador> Cuadro(ant, L, R);

        return Cuadro;
    }
}
void Torneo::crear_torneo(const Cjt_Jugadores &jugs)
{
    // altura del cuadro
    int altura = ceil(log2(jugs.numero_jugadores()) + 1);

    int x = pow(2, altura - 1) - jugs.numero_jugadores();

    vector<Jugador> local_rank = jugs.obtener_ranking();
    Cuadro = crear_torneo_i(local_rank[0], local_rank, altura, 1, x);
}

void Torneo::imprimir_cuadro(const BinTree<Jugador> &A) const
{

    if (A.left().empty())
    {
        cout << A.value().consultar_pos_ranking() << '.' << A.value().consultar_id();
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

Jugador ganador(Jugador &J1, Jugador &J2)
{
    /*int p1, p2;
    char coso;
    int sets1 = 0;
    int sets2 = 0;
    cin >> p1 >> coso >> p2;
    if (p1 == 1 and p2 == 0)
    {
        J1.modificar_estadisticas(0, '+');
        J2.modificar_estadisticas(0, '-');
        return J1;
    }
    else if (p1 == 0 and p2 == 1)
    {
        J2.modificar_estadisticas(0, '+');
        J1.modificar_estadisticas(0, '-');
        return J2;
    }*/
    J2 = J2;
    return J1;
}
Jugador leer_resultados_i(const BinTree<Jugador> &A)
{
    int puntos;
    cin >> puntos;
    if (puntos == 0)
    {
        return A.value();
        cout << "holi" << endl;
    }
    else
    {

        string in;
        cin >> in;
        Partido match;
        match.first = leer_resultados_i(A.left());
        match.second = leer_resultados_i(A.right());

        Jugador Ganador = ganador(match.first, match.second);
        cout << match.first.consultar_id() << " vs " << match.second.consultar_id() << endl;
        cout << "resultados : " << in << endl;
        return Ganador;
    }
}

void Torneo::leer_resultados(const BinTree<Jugador> &A)
{
    if (A.empty())
        cout << "ta vacío" << endl;
    leer_resultados_i(A);
}

BinTree<Jugador> Torneo::obtener_cuadro() const
{
    if (Cuadro.empty())
        cout << "ta vacio" << endl;
    return Cuadro;
}