/**
 * @file Jugador.cc
 * @brief Código de la clase Jugador
 * @version 0.1
 * @date 2022-04-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Jugador.hh"

Jugador::Jugador()
{
    puntos = 0;
    torneos_disputados = 0;
    partidos.first = partidos.second = 0;
    sets.first = sets.second = 0;
    juegos.first = juegos.second = 0;
}

void Jugador::leer_jugador()
{
    // Asigna al Jugador un identificador y se incicializa con 0 puntos;

    string name;
    cin >> name;
    id = name;
}

string Jugador::consultar_id() const
{
    return id;
}

int Jugador::consultar_puntos() const
{
    return puntos;
}

int Jugador::consultar_pos_ranking() const
{
    return pos_ranking;
}

void Jugador::modificar_ranking(int n)
{
    pos_ranking = n;
}

pair<int, int> Jugador::consultar_partidos() const
{
    return partidos;
}

pair<int, int> Jugador::consultar_sets() const
{
    return sets;
}

pair<int, int> Jugador::consultar_juegos() const
{
    return juegos;
}

int Jugador::consultar_torneos_disputados() const
{
    return torneos_disputados;
}

void Jugador::modificar_puntos(int n)
{
    puntos = n;
}

void Jugador::mas_torneo()
{
    ++torneos_disputados;
}

void Jugador::modificar_juegos(int n, char c)
{
    if (c == '+')
    {
        juegos.first += n;
    }
    else
        juegos.second += n;
}
void Jugador::modificar_sets(int n, char c)
{
    if (c == '+')
    {
        sets.first += n;
    }
    else
        sets.second += n;
}
void Jugador::modificar_partidos(char c)
{
    if (c == '+')
    {
        ++partidos.first;
    }
    else
        ++partidos.second;
}

void Jugador::escribir_jugador() const
{
    cout << id << " Rk:" << pos_ranking;
    cout << " Ps:" << puntos;
    cout << " Ts:" << torneos_disputados;
    cout << " WM:" << partidos.first;
    cout << " LM:" << partidos.second;
    cout << " WS:" << sets.first;
    cout << " LS:" << sets.second;
    cout << " WG:" << juegos.first;
    cout << " LG:" << juegos.second << endl;
}