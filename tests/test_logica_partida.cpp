#include <gtest/gtest.h>
#include "../src/server_src/logicaPartida.h"
#include "../src/common_src/accion.h"


const uint32_t id_bala = 00;
const uint32_t id_jugador = 00;
const uint32_t posx = 0;
const uint32_t posy = 0;

struct LogicaPartidaTest : testing::Test{
    LogicaPartida * logica;


    LogicaPartidaTest(){
        Configuracion::loadConfig(false);
        logica = new LogicaPartida("mapa_beach");
    }

    ~LogicaPartidaTest(){
        delete logica;
    }
};

TEST_F(LogicaPartidaTest, ComienzaSinJugadores){
    EXPECT_EQ(logica->getPersonajesSize(), 0);
}

TEST_F(LogicaPartidaTest, ComienzaConEnemigos){
    EXPECT_GT(logica->getEnemigosSize(), 0);
}

TEST_F(LogicaPartidaTest, ComienzaConObjetosSolidos){
    EXPECT_GT(logica->getObjetosSolidosSize(), 0);
}

TEST_F(LogicaPartidaTest, ComienzaConObjetosComunes){
    EXPECT_GT(logica->getObjetosComunesSize(), 0);
}

TEST_F(LogicaPartidaTest, AgregarJugador){
    Accion accion;
    accion.codigo = CodigoAccion::JAZZ;
    accion.id_jugador = 1;
    logica->agregar_personaje(accion);
    EXPECT_EQ(logica->getPersonajesSize(), 1);
}

TEST_F(LogicaPartidaTest, AgregarJAZZ){
    Accion accion;
    accion.codigo = CodigoAccion::JAZZ;
    accion.id_jugador = 1;
    logica->agregar_personaje(accion);
    EXPECT_EQ(logica->getPersonajesSize(), 1);

}
TEST_F(LogicaPartidaTest, AgregarSPAZ){
    Accion accion;
    accion.codigo = CodigoAccion::SPAZ;
    accion.id_jugador = 1;
    logica->agregar_personaje(accion);
    EXPECT_EQ(logica->getPersonajesSize(), 1);
}

TEST_F(LogicaPartidaTest, AgregarLORI){
    Accion accion;
    accion.codigo = CodigoAccion::LORI;
    accion.id_jugador = 1;
    logica->agregar_personaje(accion);
    EXPECT_EQ(logica->getPersonajesSize(), 1);
}

TEST_F(LogicaPartidaTest, AgregarVariosJugadores){
    Accion accion;
    accion.codigo = CodigoAccion::JAZZ;
    accion.id_jugador = 1;
    logica->agregar_personaje(accion);
    accion.codigo = CodigoAccion::SPAZ;
    accion.id_jugador = 2;
    logica->agregar_personaje(accion);
    EXPECT_EQ(logica->getPersonajesSize(), 2);
}

TEST_F(LogicaPartidaTest, EliminarJugador){
    Accion accion;
    accion.codigo = CodigoAccion::JAZZ;
    accion.id_jugador = 1;
    logica->agregar_personaje(accion);
    logica->abandonar_partida(1);
    EXPECT_EQ(logica->getPersonajesSize(), 0);
}

TEST_F(LogicaPartidaTest, NoSeAgregaDosVeces){
    Accion accion;
    accion.codigo = CodigoAccion::JAZZ;
    accion.id_jugador = 1;
    logica->agregar_personaje(accion);
    logica->agregar_personaje(accion);
    EXPECT_EQ(logica->getPersonajesSize(), 1);
}


int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Logica Partida\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}