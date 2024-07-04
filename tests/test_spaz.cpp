#include <gtest/gtest.h>
#include "../src/server_src/personaje/personaje_spaz.h"



struct PersonajeSpazTest : testing::Test{
    Personaje * personaje;

    PersonajeSpazTest(){
        
        std::vector<SpawnPoint> spawns;
        Configuracion::loadConfig(false);
        SpawnPoint spawn;
        spawn.x = 10;
        spawn.y = 10;
        spawns.push_back(spawn);
        personaje = new Spaz(001, spawns);
    }

    ~PersonajeSpazTest(){
        delete personaje;
    }
};


//TEST PARTICULAR DE SPAZ


TEST_F(PersonajeSpazTest, obtenerPersonaje){
    EXPECT_EQ(personaje->obtener_personaje(), SPAZ);
    
}




int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Personaje SPAZ\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}