#include <gtest/gtest.h>
#include "../src/server_src/enemigo/enemigo_fencer.h"


/*ENEMIGO FENCER HEREDA DE LA CLASE ENEMIGO. AL ENEMIGO SER UNA CLASE ABSTRACTA
NO ES POSIBLE TESTEARLA USANDO GTESTS. PROBAR LOS METODOS PRINCIPALES DE FENCER
ES LO MISMO QUE PROBAR LOS DE LA CLASE ENEMIGO*/
struct EnemigoFencerTest : testing::Test{
    Enemigo * enemigo;

    EnemigoFencerTest(){
        Configuracion::loadConfig(false);
        enemigo = new Fencer(001,00,00);
    }

    ~EnemigoFencerTest(){
        delete enemigo;
    }
};

TEST_F(EnemigoFencerTest, IniciaQuieto){
    EXPECT_EQ(enemigo->obtener_movimiento(), true);
}

TEST_F(EnemigoFencerTest, IniciaVivo){
    EXPECT_EQ(enemigo->esta_vivo(), true);
}

TEST_F(EnemigoFencerTest, DanioMayorACero){
    EXPECT_GE(enemigo->obtener_danio(), 0);
}

TEST_F(EnemigoFencerTest, VidaMayorACero){
    EXPECT_GE(enemigo->obtener_vida(), 0);
}

TEST_F(EnemigoFencerTest, Muerte){
    enemigo->matar();
    EXPECT_EQ(enemigo->esta_vivo(),false);
    EXPECT_GE(0,enemigo->obtener_vida());
}

TEST_F(EnemigoFencerTest, Revivir){
    enemigo->matar();
    enemigo->revivir();
    EXPECT_EQ(enemigo->esta_vivo(),true);
    EXPECT_GE(enemigo->obtener_vida(), 0);
}


//TEST PARTICULAR DE FENCER


TEST_F(EnemigoFencerTest, obtenerPersonaje){
    EXPECT_EQ(enemigo->obtener_personaje(), FENCER);

}

int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Enemigo FENCER\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}