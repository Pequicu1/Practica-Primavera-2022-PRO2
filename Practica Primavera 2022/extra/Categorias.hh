// VER QUE COÑO HACER CON ESTA CLASE PQ IGUAL LA MANDO A TOMAR POR SACO

/** @file Categorias.hh
    @brief Especificación de la clase categoria.
*/

#ifndef CATS_HH
#define CATS_HH

#ifndef NO_DIAGRAM
#include <iostream>
#include <vector>
#endif

using namespace std;

/** @class Categorias
    @brief Representa las diferentes categorias a las que puedan pertenecer los torneos.
    */

class Categorias
{

private:
    /** @brief atributos de cada categoría*/
    struct Categoria
    {
        /** @brief numero característico */
        int num;
        /** @brief identificador de la categoría */
        string id;
        /** @brief niveles de los que dispone la categoría en el torneo */
        vector<int> niveles;
    };

    /** @brief Todas las categorías */

    vector<Categoria> cats;

public:
    // Constructora
    /** @brief Creadora por defecto
        @pre cierto
        @post El resultado son una lista de categorías vacía.
    */
    Categorias();

    void leer_categorias();

    void asignar_puntos(int cat, int nivel, int puntos) const;

    void listar_categorias() const;
};
#endif