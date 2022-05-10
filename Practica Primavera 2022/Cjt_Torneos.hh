/** @file Cjt_Torneos.hh
    @brief Especificación de la clase conjunto de torneos.
*/

#ifndef CONJ_TORNEOS_HH
#define CONJ_TORNEOS_HH

#include "Torneo.hh"
#include "Jugador.hh"

#ifndef NO_DIAGRAM
#include <vector>
#include <map>
#endif

/** @class Cjt_Torneos
    @brief Representa el conjunto de todos los torneos del circuito.
    */

typedef vector<vector<int>> Matriz;
class Cjt_Torneos
{
private:
  map<string, Torneo> indice_torneos;
  Matriz Tabla_de_puntuaciones;
  vector<string> categorias;
  int ntorn;

public:
  // -- CONSTRUCTORA --

  /** @brief Creadora por defecto.
       \pre <em>cierto</em>
       \post El resultado es un conjunto de torneos vacío.
  */
  Cjt_Torneos();

  // -- MODIFICADORAS --

  /** @brief Añade un torneo al conjunto de torneos.
        \pre El parámetro implícito está incializado y T es un torneo previamente creado y que no se encuentra
        en el conjunto de torneos.
        \post El parámetro implícito contiene los torneos originales más T.
    */
  void anadir_Torneo(const Torneo &T);

  /** @brief Elimina un torneo del conjunto de torneos.
        \pre El parámetro implícito está incializado y T es un Torneo existente en el parámetro implícito.
        \post El parámetro implícito contiene los torneos originales menos T.
    */
  void eliminar_Torneo(const Torneo &T);

  /**
   * @brief Modifica el Torneo T deseado
   * \pre P.I inicializado previamente y T existe
   * \post modifica en el map de torneos el torneo deseado.
   * @param T
   */
  void actualizar_torneo(const Torneo &T);

  // -- CONSULTORAS --

  /** @brief Consultora que devuelve el Torneo deseado.
        \pre El torneo T existe en el parámetro implícito.
        \post Retorna el tornado deseado a partir de su identificador.
    */
  Torneo obtener_torneo(string id) const;

  /**
   * @brief Devuelve la tabla de puntuaciones
   * \pre cierto
   * \post devuelve la Matriz que representa la tabla de puntuaciones.
   * @return Matriz
   */
  Matriz obtener_puntuaciones() const;

  /** @brief Consultora que indica si existe el Torneo T en el circuito.
        \pre El parámetro implícito está incializado.
        \post El resultado indica si el torneo existe en el circuito o no.
    */
  bool existe_torneo(string id);

  /** @brief Consultora que indica la cantidad de torneos en el circuito.
        \pre El parámetro implícito está incializado.
        \post Retorna el número de torneos en el circuito.
    */
  int numero_torneos() const;

  // -- ENTRADA / SALIDA --

  /** @brief Obtiene el cuadro de puntuaciones a partir de las categorías y el nivel máximo de las mismas que hayan.
      \pre 1 <= fila <= c && 4 <= columna <= k
      \post Asigna al parámetro implícito una tabla (Matriz) donde estarán las puntuaciones de cada torneo en base a
      la categoría y del nivel en el que el jugador finalice el torneo.
      Cada fila será de una categoría diferente y cada columna de un nivel diferente.
  */
  void leer_tabla_de_puntuaciones(int i, int j);

  /**
   * @brief Inicializa el conjunto de torneos
   * \pre n >= 0
   * \post se inicializan n torneos en el conjunto de torneos.
   * @param n
   */

  void ini_torneos(int n);

  /**
   * @brief  Lee todas las categorías que habrán en el circuito.
   *  \pre n >= 1.
   * \post se leerán n categorías, cada numero con su string identificatiba.
   * @param n
   */
  void leer_categorias(int n);

  /** @brief Escritura del ranking
      \pre cierto
      \post Se escribe por el canal estándard de salida las categorías por orden creciente de identificador.
      Se escribe: el nombre y
      la tabla de puntos por niveles (en orden creciente de nivel) de cada categoría del
      circuito.
  */
  void listar_categorias() const;

  /** @brief Operación de escritura
        \pre cierto
        \post Se han escrito los torneos del circuito  por el canal de salida estándard
    */
  void imprimir_torneos() const;
};
#endif
