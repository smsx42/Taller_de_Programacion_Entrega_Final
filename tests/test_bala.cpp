#include <gtest/gtest.h>
#include "../src/server_src/bala/bala.h"
#include "../src/server_src/configuracion.h"

#define CONFIG Configuracion::config()

const uint32_t id_bala = 00;
const uint32_t id_jugador = 00;
const uint32_t posx = 0;
const uint32_t posy = 0;


struct BalaTest : testing::Test{
    Bala * bala;
    const ConfigBala* config_bala;
   

    BalaTest(){
            Configuracion::loadConfig(false);
            config_bala = &CONFIG.obtenerBala(BALA_NORMAL);

        bala = new Bala(BALA_NORMAL, posx,posy,id_jugador,id_bala,config_bala->velocidad_del_proyectil,
            config_bala->danio,config_bala->tiempo_entre_disparo,config_bala->rango_explosion,
            config_bala->municion,config_bala->ancho, config_bala->largo);
    }

    ~BalaTest(){
        delete bala;
    }
};

TEST_F(BalaTest, PosicionesCorrectas){
    EXPECT_EQ(bala->obtener_posicionX(), posx);
    EXPECT_EQ(bala->obtener_posicionY(), posy);
}

TEST_F(BalaTest, IdBala){
    EXPECT_EQ(bala->obtener_id_bala(), id_bala);
}

TEST_F(BalaTest, IdJugador){
    EXPECT_EQ(bala->obtener_id_jugador(), id_jugador);
}

TEST_F(BalaTest, CodigoBala){
    EXPECT_EQ(bala->obtener_codigo(), BALA_NORMAL);
}

TEST_F(BalaTest, Ancho){
    EXPECT_EQ(bala->obtener_ancho(), config_bala->ancho);
}

TEST_F(BalaTest, Largo){
    EXPECT_EQ(bala->obtener_largo(), config_bala->largo);
}

TEST_F(BalaTest, Danio){
    EXPECT_EQ(bala->obtener_danio(), config_bala->danio);
}

TEST_F(BalaTest, ImpactoInicial){
    EXPECT_EQ(bala->obtener_impacto(), false);
}

TEST_F(BalaTest, Impacto){
    bala->impactar();
    EXPECT_EQ(bala->obtener_impacto(), true);
}


int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Bala\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
