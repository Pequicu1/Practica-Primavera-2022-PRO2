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
    parts = vector<Jugador>();
    parts_ant = vector<Jugador>();
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

Cjt_Jugadores Torneo::consultar_parts_ant() const
{
    return participantes_ant;
}

Cjt_Jugadores Torneo::leer_participantes(int n, const Cjt_Jugadores &Jugs)
{
    // vector<Jugador> parts;
    Cjt_Jugadores new_participantes;
    vector<Jugador> rank0 = Jugs.obtener_ranking();
    for (int i = 0; i < n; ++i)
    {
        int pos;
        cin >> pos;

        rank0[pos - 1].modificar_puntos(-rank0[pos - 1].consultar_puntos());
        parts.push_back(rank0[pos - 1]);
        new_participantes.anadir_jugador(rank0[pos - 1]);
    }
    (*this).parts = parts;
    return new_participantes;
}

void Torneo::actualiza_participantes(const Cjt_Jugadores &P)
{
    participantes = P;
}

void Torneo::actualiza_participantes_ant(const Cjt_Jugadores &P)
{
    participantes_ant = P;
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
            parts[J2.consultar_pos_ranking() - 1] = J2;

            Ganador = J1;
        }
        else
        {
            J1.modificar_puntos(pts);
            parts[J1.consultar_pos_ranking() - 1] = J1;

            Ganador = J2;
        }
    }
    else
    {

        if (resultados[i] == '1' and resultados[j] == '0')
        {
            J2.modificar_puntos(pts);
            parts[J2.consultar_pos_ranking() - 1] = J2;

            Ganador = J1;
        }
        else if (resultados[i] == '0' and resultados[j] == '1')
        {
            J1.modificar_puntos(pts);
            parts[J1.consultar_pos_ranking() - 1] = J1;

            Ganador = J2;
        }
    }
    return Ganador;
}
BinTree<Partido> Torneo::leer_resultados_i(const BinTree<Jugador> &A, Jugador &Ganador, const vector<int> &pts, int &nivel, Cjt_Jugadores &General)
{
    string puntos;
    cin >> puntos;
    if (puntos == "0")
    {
        --nivel;
        Ganador = A.value();
        BinTree<Partido> a;
        return a;
    }
    else
    {

        Partido match;
        match.puntos = puntos;
        BinTree<Partido> I = leer_resultados_i(A.left(), match.j1, pts, ++nivel, General);
        BinTree<Partido> D = leer_resultados_i(A.right(), match.j2, pts, ++nivel, General);

        --nivel;
        Ganador = ganador(match.j1, match.j2, puntos, pts[nivel]);

        General.modificar_estadisticas(Ganador, match.j1, match.j2, puntos, pts, nivel);
        parts[Ganador.consultar_pos_ranking() - 1] = Ganador;

        BinTree<Partido> res(match, I, D);

        return res;
    }
}

void Torneo::leer_resultados(const BinTree<Jugador> &A, const vector<int> &Puntos, Cjt_Jugadores &General)
{
    int nivel = 1;
    Jugador Ganador;
    BinTree<Partido> res = leer_resultados_i(A, Ganador, Puntos, ++nivel, General);
    imprimir_resultados(res);
    Ganador.modificar_puntos(Puntos[0]);
    parts[Ganador.consultar_pos_ranking() - 1] = Ganador;

    cout << endl;

    for (int i = 0; i < parts.size(); ++i)
    {
        if (parts[i].consultar_puntos() != 0)
        {

            cout << parts[i].consultar_pos_ranking() << '.' << parts[i].consultar_id() << ' ' << parts[i].consultar_puntos() << endl;
        }
    }
    participantes_ant = participantes;
    parts_ant = parts;
}

BinTree<Jugador> Torneo::obtener_cuadro() const
{
    return Cuadro;
}

void Torneo::eliminar_jugador(const Jugador &P)
{
    bool found = false;
    for (int i = 0; not found; ++i)
    {
        if (P.consultar_id() == parts_ant[i].consultar_id())
        {
            participantes_ant.eliminar_jugador(participantes_ant.obtener_ranking()[i]);
            parts_ant[i].modificar_puntos(-parts_ant[i].consultar_puntos());
            found = true;
        }
    }
}

void Torneo::imprimir_resultados(const BinTree<Partido> &A) const
{
    if (not A.empty())
    {
        cout << '(';
        cout << A.value().j1.consultar_pos_ranking() << '.' << A.value().j1.consultar_id() << " vs " << A.value().j2.consultar_pos_ranking() << '.' << A.value().j2.consultar_id() << ' ' << A.value().puntos;
        imprimir_resultados(A.left());
        imprimir_resultados(A.right());
        cout << ')';
    }
}

vector<Jugador> Torneo::consultar_ranking() const
{
    return parts;
}
vector<Jugador> Torneo::consultar_ranking_anterior() const
{
    return parts_ant;
}