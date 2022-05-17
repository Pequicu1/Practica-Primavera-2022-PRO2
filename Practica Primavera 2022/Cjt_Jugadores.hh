/** @file Cjt_Jugadores.hh
    @brief Especificación de la clase Cjt_Jugadores.
*/

#ifndef CONJ_JUGADORES_HH
#define CONJ_JUGADORES_HH

#include "Jugador.hh"

#ifndef NO_DIAGRAM
#include <vector>
#include <map>
#include <algorithm>
#endif

/** @class Cjt_Jugadores
    @brief Representa el conjunto de todos los jugadores en el torneo.
    */

class Cjt_Jugadores
{

private:
    map<string, Jugador> indice_jugadores;
    vector<Jugador> ranking;
    int njug = ranking.size();

    static bool comp(const Jugador &j1, const Jugador &j2);

public:
    // -- CONSTRUCTORA --

    /** @brief Creadora por defecto.

        Se ejecuta automáticamente al declarar un conjunto de jugadores.
        \pre <em>cierto</em>
        \post El resultado es un conjunto de jugadores vacío.
    */

    Cjt_Jugadores();

    // -- MODIFICADORAS --

    /** @brief Añade un jugador al circuito.
        \pre jug es un jugador previamente inicializado.
        \post El parámetro implícito pasa a contener los jugadores originales más el nuevo jugador.
    */
    void anadir_jugador(Jugador &jug);

    /** @brief Elimina un jugador del circuito.
        \pre jug es un jugador previamente inicializado.
        \post El parámetro implícito pasa a contener los jugadores originales menos jug.
    */
    void eliminar_jugador(const Jugador &jug);

    /**
     * @brief modifica las estadisticas de los jugadores del ranking
     * \pre cierto
     * \post se modifica el jugador objetivo en el ranking
     */
    void modificar_ranking(const Jugador &P);

    /**
     * @brief modifica las estadísticas del J1 y J2 en base del gandor y los puntos que hayan obtenidos, sets y partido.
     * \pre hay un Ganador que se ha calculado previamente.
     * \post Las características del J1 y J2 se han modificado.
     * @param Ganador
     * @param J1
     * @param J2
     * @param resultados
     * @param puntos
     * @param nivel
     */
    void modificar_estadisticas(Jugador &Ganador, Jugador &J1, Jugador &J2, string resultados, const vector<int> &puntos, int nivel);

    /**
     * @brief Se restan a los jugadores del P.I los puntos que tienen aquellos que pertenecen al vector de entrada.
     * \pre jugs no está vacío
     * \post Los jugadores del P.I ahora tienen los puntos que tenían menos los que constaban en jugs.
     * @param jugs
     */
    void restar_puntos(const vector<Jugador> &jugs);

    /**
     * @brief Ordena reordena el ranking de jugadores en funcion de sus puntos;
     * \pre cierto
     * \post El ranking del PI esta ordenado decrecientemente en funcion de los puntos de los jugadores. I en caso de empate, ordenado creciente en funcion de la posición
     * anterior en el ranking.
     */
    void ordenar_ranking();

    // -- CONSULTORAS --

    /**
     * @brief Consultora del indice de jugadores del P.I. (mapa)
     * \pre cierto
     * \post Retorna el mapa de Jugadores que representa el índice de los jugadores del conjunto.
     * @return map<string, Jugador>
     */
    map<string, Jugador> consultar_indice() const;

    /** @brief Consultora que indica si existe el jugador P en el circuito.
        \pre El parámetro implícito está incializado.
        \post El resultado indica si el jugador existe en el circuito o no
    */
    bool existe_jugador(string name);

    /** @brief Consultora que devuelve el Jugador deseado.
        \pre El juagdor P existe en el parámetro implícito.
        \post Retorna el jugador deseado a partir de su identificador.
    */
    Jugador obtener_jugador(string id) const;

    /** @brief Consultora que devuelve el ranking en forma de vector de jugadores del p.i.
        \pre P.I. inicializado
        \post Retorna un vector de jugadores que representa el ranking.
    */
    vector<Jugador> obtener_ranking() const;

    /** @brief Consultora que indica la cantidad de jugadores en el circuito.
        \pre El parámetro implícito está incializado.
        \post Retorna el número de jugadores en el circuito.
    */
    int numero_jugadores() const;

    // -- ENTRADA / SALIDA --

    /**
     * @brief inicializa el conjunto de jugadores
     * \pre n >= 0
     * \post se inicializan n jugadores en el conjunto de jugadores, quedarán ordenados en base al orden de
     *  inicializavión de cada uno.
     * @param n
     */
    void ini_jugadores(int n);

    /** @brief Escritura del ranking
        \pre cierto
        \post Se escribe por el canal estándard de salida el ranking de los jugadores por orden creciente de ranking actual.
        Se escribirán: la posición, el nombre y los puntos de cada jugador del circuito.
    */
    void listar_ranking();

    /** @brief Operación de escritura
          \pre cierto
          \post Se han escrito los jugadores del circuito  por el canal de salida estándard
      */
    void imprimir_jugadores() const;
};
#endif
