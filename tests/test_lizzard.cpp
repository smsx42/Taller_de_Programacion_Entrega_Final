#include <gtest/gtest.h>
#include "../src/server_src/enemigo/enemigo_lizzard.h"

struct EnemigoLizzardTest : testing::Test{
    Enemigo * enemigo;

    EnemigoLizzardTest(){
        Configuracion::loadConfig(false);
        enemigo = new Lizzard(001,00,00);
    }

    ~EnemigoLizzardTest(){
        delete enemigo;
    }
};


//TEST PARTICULAR DE LIZZARD


TEST_F(EnemigoLizzardTest, obtenerPersonaje){
    EXPECT_EQ(enemigo->obtener_personaje(), LIZZARD);

}

int main(int argc, char*argv[]){
    
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Enemigo LIZZARD\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}