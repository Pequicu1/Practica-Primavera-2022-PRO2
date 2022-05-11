/**
 * @file Cjt_Jugadores.cc
 * @brief Código de la clase Cjt_Jugadores
 * @version 0.1
 * @date 2022-04-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Cjt_Jugadores.hh"

Cjt_Jugadores::Cjt_Jugadores()
{
    njug = 0;
    ranking = vector<Jugador>(njug);
}

void Cjt_Jugadores::ini_jugadores(int n)
{
    ranking = vector<Jugador>(n);
    for (int i = 0; i < n; ++i)
    {
        Jugador P;
        P.leer_jugador();
        P.modificar_ranking(i + 1);
        ranking[i] = P;

        indice_jugadores[P.consultar_id()] = P;
    }
}

bool Cjt_Jugadores::existe_jugador(string name)
{
    map<string, Jugador>::const_iterator it = indice_jugadores.find(name);
    return it != indice_jugadores.end();
}

void Cjt_Jugadores::anadir_jugador(Jugador &P)
{
    P.modificar_ranking(ranking.size() + 1);
    ranking.push_back(P);
    indice_jugadores[P.consultar_id()] = P;
}

int Cjt_Jugadores::numero_jugadores() const
{
    return ranking.size();
}

Jugador Cjt_Jugadores::obtener_jugador(string name) const
{
    map<string, Jugador>::const_iterator it = indice_jugadores.find(name);
    return it->second;
}

vector<Jugador> Cjt_Jugadores::obtener_ranking() const
{
    return ranking;
}

void Cjt_Jugadores::eliminar_jugador(const Jugador &P)
{

    // Lo borro del indice (map)
    map<string, Jugador>::const_iterator it = indice_jugadores.find(P.consultar_id());
    indice_jugadores.erase(it);

    // Lo borro del ranking (vector)
    // sort(ranking.begin(), ranking.end());
    int pos = P.consultar_pos_ranking() - 1;
    //  Cuando se elimina un jugador los que estaban detrás de él suben 1 posición el ranking
    for (int i = pos; i < ranking.size() - 1; ++i)
    {
        ranking[i] = ranking[i + 1];
        ranking[i].modificar_ranking(i + 1);
        indice_jugadores[ranking[i].consultar_id()] = ranking[i];
    }
    ranking.pop_back();
}

void Cjt_Jugadores::modificar_ranking(const Jugador &P)
{
    ranking[P.consultar_pos_ranking() - 1] = P;
}

void Cjt_Jugadores::actualizar_indice(const Cjt_Jugadores &Plys)
{
    vector<Jugador> jug = Plys.obtener_ranking();
    for (int i = 0; i < jug.size(); ++i)
    {
        indice_jugadores[jug[i].consultar_id()] = jug[i];
    }
}

void Cjt_Jugadores::listar_ranking()
{
    // maybe ordenar aqui el ranking again.
    for (int i = 0; i < ranking.size(); ++i)
    {
        cout << ranking[i].consultar_pos_ranking() << ' ' << ranking[i].consultar_id() << ' ' << ranking[i].consultar_puntos() << endl;
    }
}

bool comp(const Jugador &j1, const Jugador &j2)
{
    if (j1.consultar_puntos() == j2.consultar_puntos())
    {
        return j1.consultar_pos_ranking() < j2.consultar_pos_ranking();
    }
    else
        return j1.consultar_puntos() > j2.consultar_puntos();
}

void Cjt_Jugadores::ordenar_ranking()
{
    sort(ranking.begin(), ranking.end(), comp);
    for (int i = 0; i < ranking.size(); ++i)
    {
        ranking[i].modificar_ranking(i + 1);
    }
}

void Cjt_Jugadores::imprimir_jugadores() const
{
    cout << indice_jugadores.size() << endl;
    map<string, Jugador>::const_iterator it = indice_jugadores.begin();
    while (it != indice_jugadores.end())
    {
        it->second.escribir_jugador();
        ++it;
    }
}