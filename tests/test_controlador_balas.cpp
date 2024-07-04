#include <gtest/gtest.h>
#include "../src/server_src/bala/controlador_balas.h"
#include "../src/server_src/configuracion.h"

#define CONFIG Configuracion::config()


struct ControladorBalasTest : testing::Test{
    ControladorBalas * controlador; 

    ControladorBalasTest(){
        Configuracion::loadConfig(false);
        controlador = new ControladorBalas();
    }

    ~ControladorBalasTest(){
        delete controlador;
    }
};

TEST_F(ControladorBalasTest, IniciaVacio){
    std::vector<Bala> balas = controlador->obtener_balas();
    EXPECT_EQ(balas.size(), 0);

}

TEST_F(ControladorBalasTest, AgregarBala){
    controlador->agregar_bala(BALA_NORMAL, 0, 0, 0, 0, 1);
    std::vector<Bala> balas = controlador->obtener_balas();
    EXPECT_EQ(balas.size(), 1);
}

TEST_F(ControladorBalasTest, RemoverBala){
    controlador->agregar_bala(BALA_NORMAL, 0, 0, 0, 0, 1);
    controlador->remover_bala(0);
    std::vector<Bala> balas = controlador->obtener_balas();
    EXPECT_EQ(balas.size(), 0);
}

TEST_F(ControladorBalasTest, RemoverBalaInexistente){
    controlador->agregar_bala(BALA_NORMAL, 0, 0, 0, 0, 1);
    controlador->remover_bala(1);
    std::vector<Bala> balas = controlador->obtener_balas();
    EXPECT_EQ(balas.size(), 1);
}
TEST_F(ControladorBalasTest, RemoverBalaVarias){
    controlador->agregar_bala(BALA_NORMAL, 0, 0, 0, 0, 1);
    controlador->agregar_bala(BALA_NORMAL, 0, 0, 0, 0, 1);
    controlador->agregar_bala(BALA_NORMAL, 0, 0, 0, 0, 1);
    controlador->remover_bala(0);
    controlador->remover_bala(1);
    controlador->remover_bala(2);
    std::vector<Bala> balas = controlador->obtener_balas();
    EXPECT_EQ(balas.size(), 0);
}

int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Controlador Bala\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}