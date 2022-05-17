/**
 @mainpage CIRCUITO DE TORNEOS DE TENIS - [Práctica primavera 2022].
 Programa modular que pretende simular lo más parecido posible la gestión y funcionamiento de un circuito de torneos de tenis. Presenta diversas simplificaciones.
 Se utilizan las clases: <em>Jugador</em>, <em>Cjt_Jugadores</em>, <em>Torneo</em> y <em>Cjt_Torneos</em>.

    Este programa sigue lo siguiente:
    - Primero de todo se inicializan las categorias, con sus puntos, seguidamente los torneos del Circuito con una categoria asignada a cada uno y finalmente los jugadores que participan en este circuito.
    - A conticuión entran una serie de comandos que modificaran el circuito a medida de cada iteracion dependiendo de la orden proporcionada.

    Los posibles comandos que el programa acepta son los siguientes:
        - nuevo_jugador o nj: añade a un  nuevo jugador al circuito. Empezará el último en el ranking con 0 puntos.
        - nuevo_torneo o nt: añade a un nuevo torneo al circuito.
        - baja_jugador o bj: elimina un jugador del circuito.
        - baja_torneo o bt: elimina un torneo del circuito. Restando los puntos que habían ganado a aquellos que habian participado en la última edición.
        - iniciar_torneo o it: Inicia el torneo deseado creando un cuadro de emparejamientos incial.
        - finalizar_torneo o ft: finaliza el torneo deseado, lee un arbol de resultados y computa un arbol de partidos de donde se calcularán los puntos y otras estadísticas ganados o perdidos por los jugadores.
        - listar_ranking o lr: imprime los jugadores por orden decreciente de ranking junto con sus puntos.
        - listar_jugadores o lj: imprime todos los jugadores por orden alfabético junto con todas las estadísticas del mismo.
        - listar_torneos o lt: imprime los todos los torneos del circuito.
        - listar_categorias o lc: imprime todas las categorias del circuito junto con los puntos por cada nivel.
        - fin: finaliza el programa.

*/

/** @file program.cc
    @brief Programa principal para el ejercicio <em>Circuito de torneos de tenis</em>.
*/

#include "Cjt_Jugadores.hh"
#include "Cjt_Torneos.hh"

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
                torns.eliminar_jugador(P);
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
                if (T.consultar_ranking_anterior().size() != 0)
                {
                    jugs.restar_puntos(T.consultar_ranking_anterior());
                    jugs.ordenar_ranking();
                }
                cout << torns.numero_torneos() << endl;
            }
            else
                cout << "error: el torneo no existe" << endl;
        }
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
            jugs.restar_puntos(T.consultar_ranking_anterior());
            T.leer_resultados(T.obtener_cuadro(), torns.obtener_puntuaciones()[T.consultar_categoria() - 1], jugs);
            torns.actualizar_torneo(T);
            jugs.ordenar_ranking();
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
