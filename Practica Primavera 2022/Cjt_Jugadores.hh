/** @file Cjt_Jugadores.hh
    @brief Especificación de la clase conjunto de jugadores.
*/

#ifndef CONJ_JUGADORES_HH
#define CONJ_JUGADORES_HH

#include "Jugador.hh"

#ifndef NO_DIAGRAM
#include <vector>
#include <map>
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

    // -- CONSULTORAS --

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
