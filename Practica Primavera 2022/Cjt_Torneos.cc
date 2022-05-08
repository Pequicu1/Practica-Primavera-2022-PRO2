/**
 * @file Cjt_Torneos.cc
 * @brief Código de la clase Cjt_Torneos
 * @version 0.1
 * @date 2022-04-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Cjt_Torneos.hh"

typedef vector<vector<int>> Matriz;

Cjt_Torneos::Cjt_Torneos()
{
    ntorn = 0;
    categorias = vector<string>(0);
    Tabla_de_puntuaciones = Matriz(0, vector<int>(0));
}

void Cjt_Torneos::leer_categorias(int n)
{
    // Lectura de las categorías.
    categorias = vector<string>(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> categorias[i];
    }
}

void Cjt_Torneos::leer_tabla_de_puntuaciones(int c, int k)
{
    // Lectura de las puntuaciones
    Tabla_de_puntuaciones = Matriz(c, vector<int>(k));
    for (int i = 0; i < c; ++i)
    {
        for (int j = 0; j < k; ++j)
        {
            cin >> Tabla_de_puntuaciones[i][j];
        }
    }
}

void Cjt_Torneos::ini_torneos(int n)
{
    // Incializamos los torneos.
    // Circuito = vector<Torneo>(n);
    for (int i = 0; i < n; ++i)
    {
        Torneo T;
        T.leer_torneo();
        // Circuito[i] = T;
        indice_torneos[T.consultar_nombre()] = T;
    }
}

bool Cjt_Torneos::existe_torneo(string id)
{
    map<string, Torneo>::const_iterator it = indice_torneos.find(id);
    return it != indice_torneos.end();
}

void Cjt_Torneos::anadir_Torneo(const Torneo &T)
{
    indice_torneos[T.consultar_nombre()] = T;
}

int Cjt_Torneos::numero_torneos() const
{
    return indice_torneos.size();
}

Torneo Cjt_Torneos::obtener_torneo(string name) const
{
    map<string, Torneo>::const_iterator it = indice_torneos.find(name);
    return it->second;
}

void Cjt_Torneos::eliminar_Torneo(const Torneo &T)
{
    map<string, Torneo>::const_iterator it = indice_torneos.find(T.consultar_nombre());
    indice_torneos.erase(it);

    /*igual no hace falta tener un vector de Torneos jaj salu2
    int pos = Circuito.begin();
    Circuito.erase(Circuito.begin() + pos);
    */
}

void Cjt_Torneos::imprimir_torneos() const
{
    cout << indice_torneos.size() << endl;
    map<string, Torneo>::const_iterator it = indice_torneos.begin();
    while (it != indice_torneos.end())
    {
        cout << it->second.consultar_nombre() << ' ' << categorias[it->second.consultar_categoria() - 1];
        cout << endl;
        ++it;
    }
}

void Cjt_Torneos::listar_categorias() const
{
    cout << categorias.size() << ' ' << Tabla_de_puntuaciones[0].size() << endl;
    for (int i = 0; i < categorias.size(); ++i)
    {
        cout << categorias[i];
        for (int j = 0; j < Tabla_de_puntuaciones[0].size(); ++j)
        {
            cout << ' ' << Tabla_de_puntuaciones[i][j];
        }
        cout << endl;
    }
}