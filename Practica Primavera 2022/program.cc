/**
 * @mainpage CIRCUITO DE TORNEOS DE TENIS - [Práctica primavera 2022].

Programa modular que pretende simular lo más parecido posible la gestión y funcionamiento de un circuito de torneos de tenis. Presenta diversas simplificaciones.

*/

/** @file program.cc
    @brief Programa principal para el ejercicio <em>Circuito de torneos de tenis</em>.
*/

// para que el diagrama modular quede bien se han escrito includes redundantes;
// en los ficheros .hh de la documentación de las clases ocurre lo mismo.

#include "Cjt_Jugadores.hh"
#include "Cjt_Torneos.hh"
//#include "Categorias.hh"
#ifndef NO_DIAGRAM
#include "PRO2Excepcio.hh"
#endif

int main()
{
    Cjt_Torneos torns;

    // INICIALIZAMOS LAS CATEGORÍAS
    int c, k;
    cin >> c >> k;
    torns.leer_categorias(c);

    // INCIALIZAMOS cada nivel con su respectiva puntuación para cada categoría.
    torns.leer_tabla_de_puntuaciones(c, k);

    // INCIALIZAMOS LOS TORNEOS
    int ntorn;
    cin >> ntorn;
    torns.ini_torneos(ntorn);

    Cjt_Jugadores jugs;

    // INCIALIZAMOS LOS JUGADORES
    int njugs;
    cin >> njugs;
    jugs.ini_jugadores(njugs);

    string comando;
    cin >> comando;
    while (comando != "fin")
    {
        cout << '#' << comando;

        if (comando == "nuevo_jugador" or comando == "nj")
        {
            Jugador P;
            P.leer_jugador();
            cout << ' ' << P.consultar_id() << endl;
            if (not jugs.existe_jugador(P.consultar_id()))
            {

                jugs.anadir_jugador(P);
                cout << jugs.numero_jugadores() << endl;
            }
            else
                cout << "error: ya existe un jugador con ese nombre" << endl;
        }
        else if (comando == "nuevo_torneo" or comando == "nt")
        {
            Torneo T;
            T.leer_torneo();
            cout << ' ' << T.consultar_nombre() << ' ' << T.consultar_categoria() << endl;
            if (T.consultar_categoria() < 1 or T.consultar_categoria() > c)
                cout << "error: la categoria no existe" << endl;
            else
            {
                if (not torns.existe_torneo(T.consultar_nombre()))
                {
                    torns.anadir_Torneo(T);
                    cout << torns.numero_torneos() << endl;
                }
                else
                    cout << "error: ya existe un torneo con ese nombre" << endl;
            }
        }
        else if (comando == "baja_jugador" or comando == "bj")
        {
            string name;
            cin >> name;

            cout << ' ' << name << endl;

            if (jugs.existe_jugador(name))
            {
                Jugador P = jugs.obtener_jugador(name);
                jugs.eliminar_jugador(P);
                cout << jugs.numero_jugadores() << endl;
            }
            else
                cout << "error: el jugador no existe" << endl;
        }
        else if (comando == "baja_torneo" or comando == "bt")
        {
            string name_torneo;
            cin >> name_torneo;

            cout << ' ' << name_torneo << endl;
            if (torns.existe_torneo(name_torneo))
            {
                Torneo T = torns.obtener_torneo(name_torneo);
                torns.eliminar_Torneo(T);
                cout << torns.numero_torneos() << endl;
            }
            else
                cout << "error: el torneo no existe" << endl;
        }
        // SEGUIR POR AQUIII
        else if (comando == "iniciar_torneo" or comando == "it")
        {
            string id;
            cin >> id;

            cout << ' ' << id << endl;

            Torneo T = torns.obtener_torneo(id);

            int nparticipantes;
            cin >> nparticipantes;
            Cjt_Jugadores Participantes = T.leer_participantes(nparticipantes, jugs);
            T.actualiza_participantes(Participantes);
            T.crear_torneo();

            BinTree<Jugador> Emparejamientos = T.obtener_cuadro();
            T.imprimir_cuadro(Emparejamientos);
            torns.actualizar_torneo(T);
            cout << endl;
        }
        else if (comando == "finalizar_torneo" or comando == "ft")
        {
            string id;
            cin >> id;

            cout << ' ' << id << endl;

            Torneo T = torns.obtener_torneo(id);
            // cout << "QUIERO EL CUADRO DEL TORNEO: " << T.consultar_nombre() << endl;
            T.leer_resultados(T.obtener_cuadro(), torns.obtener_puntuaciones()[T.consultar_categoria() - 1], jugs);
            // T.obtener_participantes().imprimir_jugadores();
            //  jugs.actualizar_indice(T.obtener_participantes());
            //   T.imprimir_resultados();
            //   T.obtener_participantes().listar_ranking();
            //   T.obtener_participantes().imprimir_jugadores();

            // T.obtener_participantes().ordenar_ranking();
            // jugs.actualizar_indice(T.obtener_participantes());
            // jugs.imprimir_jugadores();
            // jugs.imprimir_jugadores();
            jugs.ordenar_ranking();
            jugs.actualizar_ranking();

            // T.obtener_participantes().listar_ranking();
            // jugs.imprimir_jugadores();
        }
        else if (comando == "listar_ranking" or comando == "lr")
        {
            cout << endl;
            jugs.listar_ranking();
        }
        else if (comando == "listar_jugadores" or comando == "lj")
        {
            cout << endl;
            jugs.imprimir_jugadores();
        }
        else if (comando == "consultar_jugador" or comando == "cj")
        {
            string name;
            cin >> name;
            cout << ' ' << name << endl;
            if (jugs.existe_jugador(name))
            {
                Jugador P = jugs.obtener_jugador(name);
                P.escribir_jugador();
            }
            else
                cout << "error: el jugador no existe" << endl;
        }
        else if (comando == "listar_torneos" or comando == "lt")
        {
            cout << endl;
            torns.imprimir_torneos();
        }
        else if (comando == "listar_categorias" or comando == "lc")
        {
            cout << endl;
            torns.listar_categorias();
        }

        cin >> comando;
    }
}
