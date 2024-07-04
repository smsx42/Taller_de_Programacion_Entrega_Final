#include <gtest/gtest.h>
#include "../src/server_src/enemigo/enemigo_rat.h"

struct EnemigoRatTest : testing::Test{
    Enemigo * enemigo;

    EnemigoRatTest(){
        Configuracion::loadConfig(false);
        enemigo = new Rat(001,00,00);
    }

    ~EnemigoRatTest(){
        delete enemigo;
    }
};


//TEST PARTICULAR DE RAT


TEST_F(EnemigoRatTest, obtenerPersonaje){
    EXPECT_EQ(enemigo->obtener_personaje(), RAT);

}

int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Enemigo RAT\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}