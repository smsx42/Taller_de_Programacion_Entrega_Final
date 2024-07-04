#include <gtest/gtest.h>
#include "../src/server_src/enemigo/enemigo_bruja.h"

struct EnemigoBrujaTest : testing::Test{
    Enemigo * enemigo;

    EnemigoBrujaTest(){
        Configuracion::loadConfig(false);
        enemigo = new Bruja(001,00,00);
    }

    ~EnemigoBrujaTest(){
        delete enemigo;
    }
};


//TEST PARTICULAR DE BRUJA


TEST_F(EnemigoBrujaTest, obtenerPersonaje){
    EXPECT_EQ(enemigo->obtener_personaje(), BRUJA);

}

int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Enemigo BRUJA\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}