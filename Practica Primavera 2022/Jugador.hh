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

public:
  // -- CONSTRUCTORA --

  /** @brief Creadora por defecto.
   *
    \pre <em>cierto</em>
    \post El resultado es un jugador vacío.
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
   * @brief Modificadora de las estadísticas del jugador.
   * \pre cierto
      \post Se incrementa o decrementa los sets, juegos o partidos.
   * @param estat
   */
  void modificar_estadisticas(int stat, char c);

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
   * @brief consultora de los partidos jugados por el jugador.
   * \pre cert
   * \post devuelve un natural que representa los partidos jugados por el jugador.
   * @return int
   */
  int consultar_partidos_jugados() const;

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

private:
  string id;
  int puntos;
  int pos_ranking;
  int partidos_jugados;
  int torneos_disputados;
  pair<int, int> partidos;
  pair<int, int> sets;
  pair<int, int> juegos;
};
#endif
