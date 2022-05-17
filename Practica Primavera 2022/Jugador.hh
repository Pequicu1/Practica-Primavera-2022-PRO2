/** @file Jugador.hh
    @brief Especificación de la clase Jugador

*/

#ifndef _JUGADOR_HH_
#define _JUGADOR_HH_

#ifndef NO_DIAGRAM
#include <vector>
#include <iostream>
#endif
using namespace std;

/** @class Jugador
    @brief Representa un Jugador.
    */

class Jugador
{

private:
  string id;
  int puntos;
  int pos_ranking;
  int torneos_disputados;
  pair<int, int> partidos;
  pair<int, int> sets;
  pair<int, int> juegos;

public:
  // -- CONSTRUCTORA --

  /** @brief Creadora por defecto.
   *
    \pre <em>cierto</em>
    \post El resultado es un jugador vacío inicializado todo a 0.
*/
  Jugador();

  // -- MODIFICADORAS --

  /** @brief Modificadora del rankging del jugador.
        \pre cierto
        \post El parámetro implícito pasa a estar en la posición <em>n</em> del ranking.
  */
  void modificar_ranking(int n);

  /**
   * @brief Modificadora de los puntos del jugador.
      \pre cierto
      \post El parámetro implícito pasa a tener n puntos.
   * @param n
   */
  void modificar_puntos(int n);

  /**
   * @brief incrementa los torneos jugados;
   * \pre cierto
   * \post el jugador pasa a tener un torneo jugado más.
   */
  void mas_torneo();

  /**
   * @brief Modificadora de los juegos del jugador.
      \pre cierto
      \post El parámetro implícito pasa a tener n juegos ganados: si c fue '+', else: perdidos.
   */
  void modificar_juegos(int n, char c);

  /**
   * @brief Modificadora de los sets del jugador.
      \pre cierto
      \post El parámetro implícito pasa a tener n sets ganados: si c fue '+', else: perdidos.
   */
  void modificar_sets(int n, char c);

  /**
   * @brief Modificadora de los partidos del jugador.
      \pre cierto
      \post se incrementa en 1 los partidos ganados: si c fue '+', else: perdidos por el jugador .
   */
  void modificar_partidos(char c);

  // -- CONSULTORAS --

  /** @brief Consultora del Identificador del jugador;

      \pre El parámetro implícito está incializado
      \post El resultado es el Identificador del parámetro implícito
*/

  string consultar_id() const;

  /** @brief Consultora de la posición en el ranking del jugador;

      \pre El parámetro implícito está incializado
      \post El resultado es la posición en el ranking del parámetro implícito
*/

  int consultar_pos_ranking() const;

  /** @brief Consultora de los puntos del jugador;

      \pre El parámetro implícito está incializado
      \post El resultado son los puntos del parámetro implícito
*/
  int consultar_puntos() const;

  /**
   * @brief Consultora de los partidos ganados (first) y perdidos(second)
   * \pre cierto
   * \post devuelve un par de enteros siendo el primero los partidos ganados y el segundo los perdidos.
   *
   * @return pair<int,int>
   */
  pair<int, int> consultar_partidos() const;

  /**
   * @brief Consultora de los sets ganados (first) y perdidos(second)
   * \pre cierto
   * \post devuelve un par de enteros siendo el primero los sets ganados y el segundo los perdidos.
   *
   * @return pair<int,int>
   */
  pair<int, int> consultar_sets() const;

  /**
   * @brief Consultora de los juegos ganados (first) y perdidos(second)
   * \pre cierto
   * \post devuelve un par de enteros siendo el primero los juegos ganados y el segundo los perdidos.
   *
   * @return pair<int,int>
   */
  pair<int, int> consultar_juegos() const;

  /**
   * @brief consultora de los torneos disputados por el jugador.
   * \pre cert
   * \post devuelve un natural que representa los torneos disputados por el jugador.
   * @return int
   */
  int consultar_torneos_disputados() const;

  // -- ENTRADA / SALIDA --

  /**
   * @brief Operación de lectura del jugador.
   * \pre Cierto
   * \post El parámetro implícito pasa a tener un identificador (el nombre del jugador, el cual será un string)
   *  pero la puntuación inicializada a 0 y se añadirá a la cola del ranking, es decir en ultima posición.
   */

  void leer_jugador();
  /**
   * @brief Operación de escritura del jugador.
   * \pre Cierto
   * \post Se ha escrito el identificador, la puntucaión y la posición en el ranking del parámetro implícito
   * por el canal estándard
   */
  void escribir_jugador() const;
};
#endif
