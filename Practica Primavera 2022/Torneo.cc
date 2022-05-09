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

Torneo::Torneo()
{
    Cuadro = BinTree<Jugador>();
}

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

Jugador ganador(Jugador &J1, Jugador &J2, string puntos)
{
    cout << J1.consultar_pos_ranking() << '.' << J1.consultar_id() << " vs " << J2.consultar_pos_ranking() << '.' << J2.consultar_id() << ' ' << puntos;
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
        // cout << match.first.ranking << '.' << match.first.name << " vs ";
        match.second = leer_resultados_i(A.right());
        // cout << match.second.ranking << '.' << match.second.name << ' ' << puntos;
        Jugador Ganador = ganador(match.first, match.second, puntos);
        cout << '(';
        cout << ')';

        // cout << "resultados: " << puntos << endl;
        // cout << "Pasa: " << Ganador.name << endl;
        //  cout << "resultados : " << in << endl;
        return Ganador;
    }
}

void Torneo::leer_resultados(const BinTree<Jugador> &A)
{
    leer_resultados_i(A);
}

BinTree<Jugador> Torneo::obtener_cuadro() const
{
    return Cuadro;
}