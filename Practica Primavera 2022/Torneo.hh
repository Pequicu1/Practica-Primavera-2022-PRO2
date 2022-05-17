/** @file Torneo.hh
    @brief Especificación de la clase Torneo.
*/

#ifndef TORNEO_HH
#define TORNEO_HH

#include "Cjt_Jugadores.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

/** @class Torneo
    @brief Representa un Torneo
    */

/**
 * @brief Tupla de Torneo:
 *  - Jugador 1
 *  - Jugador 2
 *  - puntos del partido
 */
struct Partido
{
  Jugador j1;
  Jugador j2;
  string puntos;
};

class Torneo
{

private:
  string identificador;
  int categoria;
  Cjt_Jugadores participantes;
  Cjt_Jugadores participantes_ant;

  vector<Jugador> parts;
  vector<Jugador> parts_ant;
  BinTree<Jugador> Cuadro;

  // iniciar_torneo
  BinTree<Jugador> crear_torneo_i(Jugador ant, const vector<Jugador> &rank, int altura, int altura_act, int x);

  // finalizar_torneo
  BinTree<Partido> leer_resultados_i(const BinTree<Jugador> &A, Jugador &Ganador, const vector<int> &pts, int &nivel, Cjt_Jugadores &General);
  Jugador ganador(Jugador &J1, Jugador &J2, string resultados, int pts);
  static void imprimir_resultados(const BinTree<Partido> &A);

public:
  // -- CONSTRUCTORA --

  /** @brief Creadora por defecto.
      \pre <em>cierto</em>
      \post El resultado es un Torneo vacío.
  */
  Torneo();

  // -- MODIFICADORAS --

  /** @brief Crea el cuadro del torneo del parámetro implícito con los particiapantes introducidos.
        \pre cierto
        \post El atributo Cuadro del P.I ahora es un BinTree de Jugadores que representa el cuadro de emparejamientos incial del Torneo.
    */
  void crear_torneo();

  /**
   * @brief Actualiza el conjunto de jugadores "participantes" del parametro implícit.
   * \pre cierto
   * \post participantes ahora es P.
   * @param P
   */
  void actualiza_participantes(const Cjt_Jugadores &P);

  /**
   * @brief Elimina el jugador del ranking pasado del torneo
   *  \pre P esta inicializado.
   * \post  El vector de Jugadores del ranking anterior es 1 mas pequeño y el jugador P no está.
   * @param P
   */
  void eliminar_jugador(const Jugador &P);

  // -- CONSULTORAS --

  Cjt_Jugadores consultar_parts_ant() const;

  /** @brief Consultora de la categoría del torneo.
      \pre <em>cierto</em>
      \post Retorna es la categoría del parámetro implícito.
  */
  int consultar_categoria() const;

  /** @brief Consultora del nombre del torneo.
        \pre <em>cierto</em>
        \post Retorna es el identificador del parámetro implícito.
    */
  string consultar_nombre() const;

  /**
   * @brief Consultora del vector de Jugadroes que representa el ranking anterior.
   * \pre cierto
   * \post devuelve el vector de Jugadores que representa el ranking anterior.
   * @return vector<Jugador>
   */
  vector<Jugador> consultar_ranking_anterior() const;

  /** @brief Consultora del cuadro de emparejamientos Torneo.
        \pre El parámetro implícito está previamente inicializado.
        \post Retorna es el cuadro de emparejamientos del parámetro implícito.
    */
  BinTree<Jugador> obtener_cuadro() const;

  /**
   * @brief Consultora del cuadro de emparejamientos Torneo.
       \pre El parámetro implícito está previamente inicializado.
       \post Retorna los participantes del torneo.
   * @return Cjt_Jugadores
   */
  Cjt_Jugadores obtener_participantes() const;

  // -- ENTRADA / SALIDA --

  /** @brief Lee un conjunto de jugadores de n participantes.
        \pre 8 <= n <= 2^(K-1)
        \post Retorna un conjunto de jugadores que serán los n participantes del torneo.
    */
  Cjt_Jugadores leer_participantes(int n, const Cjt_Jugadores &Jug);

  /** @brief Lee y analiza los resultados del torneo.
        \pre A es un cuadro de emparejamientos inicializado del torneo. Puntuaciones es el vector de enteros que corresponde a la fila de la Matriz donde se encuentran
        las diferentes categorías con su nivel.
        \post Se ha generado un arbol de "Partido" (Struct) que representa los emparejamiento a lo largo del torneo con sus respectivos gandores para
        cada encuentro.
        En el canal estándard de salida se han escrito todos los jugadores que han conseguido puntos en el torneo. [pos_ranking.nombre puntos]
        Se han actualizado el ranking y los participantes anteriores a los actuales.
    */
  void leer_resultados(const BinTree<Jugador> &A, const vector<int> &Puntuaciones, Cjt_Jugadores &General);

  /** @brief Operación de lectura
     \pre cierto
     \post El parámetro implícito pasa a tener un identificador y una categoría.
 */
  void leer_torneo();

  /** @brief Operación de escritura del cuadro del parámetro implícito.
        \pre <em>cierto</em>
        \post Se han escrito los emparejamientos del cuadro del torneo en el canal estándard de salida.
    */
  static void imprimir_cuadro(const BinTree<Jugador> &A);
};
#endif
