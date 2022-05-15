/** @file Torneo.hh
    @brief Especificación de la clase Torneo.
*/

#ifndef TORNEO_HH
#define TORNEO_HH

#include "Cjt_Jugadores.hh"
//#include "Categorias.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

/** @class Torneo
    @brief Representa un Torneo
    */

typedef pair<Jugador, Jugador> Partido;

class Torneo
{

private:
  string identificador;
  Cjt_Jugadores participantes;
  Cjt_Jugadores participantes_ant;
  int categoria;
  BinTree<Jugador> Cuadro;

public:
  // -- CONSTRUCTORA --

  /** @brief Creadora por defecto.
      \pre <em>cierto</em>
      \post El resultado es un Torneo vacío.
  */
  Torneo();

  // -- MODIFICADORAS --

  /** @brief Crea el cuadro del torneo del parámetro implícito con los particiapantes introducidos.
        \pre Participantes es un conjunto de jugadores ya incializado.
        \post Retorna un BinTree de pares de jugadores que representa el cuadro de partidos del torneo.
    */
  void crear_torneo();

  void actualiza_participantes(const Cjt_Jugadores &P);
  void actualiza_participantes_ant(const Cjt_Jugadores &P);

  // -- CONSULTORAS --

  Cjt_Jugadores consultar_parts_ant() const;

  /** @brief Consultora de la categoría del torneo.
      \pre <em>cierto</em>
      \post El resultado es la categoría del parámetro implícito.
  */
  int consultar_categoria() const;

  /** @brief Consultora del nombre del torneo.
        \pre <em>cierto</em>
        \post El resultado es el identificador del parámetro implícito.
    */
  string consultar_nombre() const;

  /** @brief Consultora del cuadro de emparejamientos Torneo.
        \pre El parámetro implícito está previamente inicializado.
        \post El resultado es el cuadro de emparejamientos del parámetro implícito.
    */
  BinTree<Jugador> obtener_cuadro() const;

  /**
   * @brief Consultora del cuadro de emparejamientos Torneo.
       \pre El parámetro implícito está previamente inicializado.
       \post Devuelve los participantes del torneo.
   * @return Cjt_Jugadores
   */
  Cjt_Jugadores obtener_participantes() const;

  // -- ENTRADA / SALIDA --

  /** @brief Lee un conjunto de jugadores de n participantes.
        \pre 8 <= n <= 2^(K-1)
        \post Retorna un conjunto de jugadores que serán los n participantes del torneo.
    */
  Cjt_Jugadores leer_participantes(int n, const Cjt_Jugadores &Jug) const;

  /** @brief Lee los resultados del torneo.
        \pre A es un cuadro de emparejamientos inicializado del torneo.
        \post El cuadro A queda con los resultados introducidos en preorden siguiendo el Árbol binario.
    */
  void leer_resultados(const BinTree<Jugador> &A, const vector<int> &Puntuaciones, Cjt_Jugadores &General);

  Jugador ganador(Jugador &J1, Jugador &J2, string resultados, int pts);

  void eliminar_jugador(const Jugador &P);

  Jugador leer_resultados_i(const BinTree<Jugador> &A, BinTree<Jugador> &C, const vector<int> &pts, int &nivel, Cjt_Jugadores &General);
  /** @brief Operación de lectura
     \pre cierto
     \post El parámetro implícito pasa a tener un identificador y una categoría.
 */
  void
  leer_torneo();

  /** @brief Operación de escritura del cuadro del parámetro implícito.
        \pre <em>cierto</em>
        \post Se han escrito los emparejamientos del cuadro del torneo en el canal estándard de salida.
    */
  void imprimir_cuadro(const BinTree<Jugador> &A) const;

  /** @brief Operación de escritura de los resultados del torneo.
        \pre <em>cierto</em>
        \post Se han escrito los resultados del torneo en el canal de estandárd de salida.
    */
  void imprimir_resultados() const;
};
#endif
