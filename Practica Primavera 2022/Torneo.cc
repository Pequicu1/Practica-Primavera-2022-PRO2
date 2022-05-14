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

Cjt_Jugadores Torneo::obtener_participantes() const
{
    return participantes;
}

Cjt_Jugadores Torneo::leer_participantes(int n, const Cjt_Jugadores &Jugs) const
{
    Cjt_Jugadores new_participantes;
    vector<Jugador> rank0 = Jugs.obtener_ranking();
    for (int i = 0; i < n; ++i)
    {
        Participante P;
        int pos;
        cin >> pos;
        P.name = rank0[pos - 1].consultar_id();
        new_participantes.anadir_jugador(rank0[pos - 1]);
    }
    return new_participantes;
}

void Torneo::actualiza_participantes(const Cjt_Jugadores &P)
{
    participantes = P;
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
void Torneo::crear_torneo()
{
    // altura del cuadro
    int altura = ceil(log2(participantes.numero_jugadores()) + 1);

    int x = pow(2, altura - 1) - participantes.numero_jugadores();

    vector<Jugador> local_rank = participantes.obtener_ranking();
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

Jugador Torneo::ganador(Jugador &J1, Jugador &J2, string resultados, int pts)
{
    cout << J1.consultar_pos_ranking() << '.' << J1.consultar_id() << " vs " << J2.consultar_pos_ranking() << '.' << J2.consultar_id() << ' ' << resultados;

    int i, j;
    i = 0;
    j = 2;

    int sets1, sets2, tot;
    sets1 = sets2 = tot = 0;

    Jugador Ganador;

    if (resultados.length() > 3)
    {
        while (i <= resultados.length())
        {

            if (resultados[i] - '0' > resultados[j] - '0')
            {
                ++sets1;
            }
            else
            {
                ++sets2;
            }
            ++tot;
            i += 4;
            j += 4;
        }
        if (sets1 > sets2)
        {
            J2.modificar_puntos(pts);
            Ganador = J1;
        }
        else
        {
            J1.modificar_puntos(pts);
            Ganador = J2;
        }
    }
    else
    {

        if (resultados[i] == '1' and resultados[j] == '0')
        {
            J2.modificar_puntos(pts);
            Ganador = J1;
        }
        else if (resultados[i] == '0' and resultados[j] == '1')
        {
            J1.modificar_puntos(pts);
            Ganador = J2;
        }
    }
    participantes.modificar_ranking(J1);
    participantes.modificar_ranking(J2);
    return Ganador;
}
Jugador Torneo::leer_resultados_i(const BinTree<Jugador> &A, const vector<int> &pts, int &nivel, Cjt_Jugadores &General)
{
    string puntos;
    cin >> puntos;
    if (puntos == "0")
    {
        --nivel;
        return A.value();
    }
    else
    {

        Partido match;
        match.first = leer_resultados_i(A.left(), pts, ++nivel, General);
        match.second = leer_resultados_i(A.right(), pts, ++nivel, General);
        --nivel;
        cout << '(';
        Jugador Ganador = ganador(match.first, match.second, puntos, pts[nivel]);
        General.modificar_estadisticas(Ganador, match.first, match.second, puntos, pts, nivel);
        participantes.modificar_ranking(Ganador);

        cout << ')';

        return Ganador;
    }
}

void Torneo::leer_resultados(const BinTree<Jugador> &A, const vector<int> &Puntos, Cjt_Jugadores &General)
{
    int nivel = 1;
    Jugador Ganador = leer_resultados_i(A, Puntos, ++nivel, General);
    Ganador.modificar_puntos(Puntos[0]);
    participantes.modificar_ranking(Ganador);
    cout << endl;
    // participantes.imprimir_jugadores();
    //   Jugador P = (*this).participantes.obtener_ranking()[0];
    //   P.escribir_jugador();
    for (int i = 0; i < participantes.obtener_ranking().size(); ++i)
    {
        // cout << participantes.obtener_ranking()[i].consultar_id() << "HA GANADO: " << participantes.obtener_ranking()[i].consultar_puntos() << endl;
        //  participantes.obtener_ranking()[i].mas_torneo();
        //   participantes.modificar_ranking(participantes.obtener_ranking()[i]);
        if (participantes.obtener_ranking()[i].consultar_puntos() != 0)
        {

            cout << participantes.obtener_ranking()[i].consultar_pos_ranking() << '.' << participantes.obtener_ranking()[i].consultar_id() << ' ' << participantes.obtener_ranking()[i].consultar_puntos() << endl;
        }
    }
    // participantes.imprimir_jugadores();
    Partic_ant = Partic_act;
}

BinTree<Jugador> Torneo::obtener_cuadro() const
{
    return Cuadro;
}