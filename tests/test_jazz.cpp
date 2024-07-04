#include <gtest/gtest.h>
#include "../src/server_src/personaje/personaje_jazz.h"
#include "../src/common_src/evento.h"


/*PERSONAJE JAZZ HEREDA DE LA CLASE PERSONAJE. AL PERSONAJE SER UNA CLASE ABSTRACTA
NO ES POSIBLE TESTEARLA USANDO GTESTS. PROBAR LOS METODOS PRINCIPALES DE JAZZ
ES LO MISMO QUE PROBAR LOS DE LA CLASE PERSONAJE*/
struct PersonajeJazzTest : testing::Test{
    Personaje * personaje;

    PersonajeJazzTest(){
        Configuracion::loadConfig(false);
        std::vector<SpawnPoint> spawns;
        SpawnPoint spawn;
        spawn.x = 10;
        spawn.y = 10;
        spawns.push_back(spawn);
        personaje = new Jazz(001,spawns);
    }

    ~PersonajeJazzTest(){
        delete personaje;
    }
};


TEST_F(PersonajeJazzTest, IniciaQuieto){
    EXPECT_EQ(personaje->obtener_movimiento(), true);
    EXPECT_EQ(personaje->obtener_corriendo(), false);
    //EXPECT_EQ(personaje->obtener_saltando(), false);
}

TEST_F(PersonajeJazzTest, IniciaSinDisparar){
    EXPECT_EQ(personaje->obtener_disparando(), false);
}

TEST_F(PersonajeJazzTest, IniciaMirandoDerecha){
    EXPECT_EQ(personaje->mirando_izquierda(), false);
}

TEST_F(PersonajeJazzTest, VidaInicial){
    EXPECT_LT(0, personaje->obtener_vida());
    EXPECT_EQ(personaje->esta_muerto(), false);
}

TEST_F(PersonajeJazzTest, IniciaSinUsarHabilidad){
    EXPECT_EQ(personaje->obtener_habilidad(), false);
}

TEST_F(PersonajeJazzTest, IniciaSinVelocidad){
    EXPECT_EQ(personaje->obtener_velocidad(), 0);
    EXPECT_EQ(personaje->obtener_velocidad_y(), 0);
}

TEST_F(PersonajeJazzTest, IniciaInvulnerable){
    EXPECT_EQ(personaje->es_invulnerable(), true);
}

TEST_F(PersonajeJazzTest, CambioVulnerabilidad){
    personaje->volverse_vulnerable();
    EXPECT_EQ(personaje->es_invulnerable(), false);
}

TEST_F(PersonajeJazzTest, AlMoverseNoEstaQuieto){
    std::chrono::duration<double> tiempo_transcurrido(0.5);
    personaje->mover_derecha(tiempo_transcurrido); //Hago un movimiento
    EXPECT_EQ(personaje->obtener_movimiento(), false);
}

TEST_F(PersonajeJazzTest, AlMoverseActualizaSuPosicion){
    std::map<uint32_t, Objeto*> map_objetos;
    std::map<uint32_t, std::unique_ptr<Objeto>> map_objetos_comunes; // Maps necesarios para la llamada a actualizar posicion

    uint32_t pos_x_inicial = personaje->obtener_posicionX();
    uint32_t pos_y_inicial = personaje->obtener_posicionY();

    std::chrono::duration<double> tiempo_transcurrido(1.0);
    personaje->mover_derecha(tiempo_transcurrido); 
    personaje->actualizar_posicion(tiempo_transcurrido,map_objetos,map_objetos_comunes);
    EXPECT_LT(pos_x_inicial, personaje->obtener_posicionX());

}

TEST_F(PersonajeJazzTest, AlMoverseActualizaSuVelocidad){
    uint32_t velocidad_inicial = personaje->obtener_velocidad();
    std::chrono::duration
    <double> tiempo_transcurrido(1.5);
    personaje->mover_derecha(tiempo_transcurrido); //Hago un movimiento
    EXPECT_LT(velocidad_inicial, personaje->obtener_velocidad());
}

TEST_F (PersonajeJazzTest, ComienzaConBalaNormal){
    EXPECT_EQ(personaje->obtener_bala_actual(), BALA_NORMAL);

}

TEST_F(PersonajeJazzTest, DispararActualizaSuEstado){
    std::chrono::duration<double> tiempo_transcurrido(0.5);
    personaje->disparar(tiempo_transcurrido);
    EXPECT_EQ(personaje->obtener_disparando(), true);

}

TEST_F(PersonajeJazzTest, DejarDeDisparar){
    personaje->dejar_disparar();
    EXPECT_EQ(personaje->obtener_disparando(), false);
}

TEST_F(PersonajeJazzTest, AlRecibirDanioBajaLaVida){
    int8_t vida_incial = personaje->obtener_vida();
    personaje->volverse_vulnerable();
    std::chrono::duration<double> tiempo_transcurrido(0.5);
    personaje->recibir_golpe(uint8_t(1), tiempo_transcurrido);
    EXPECT_LT(personaje->obtener_vida(), vida_incial);
}

TEST_F(PersonajeJazzTest, Muerte){
    int8_t vida_incial = personaje->obtener_vida();
    personaje->volverse_vulnerable();
    std::chrono::duration<double> tiempo_transcurrido(0.5);
    personaje->recibir_golpe(uint8_t(vida_incial + uint8_t(1)), tiempo_transcurrido); // le hago un danio mayor a su vida
    EXPECT_EQ(personaje->esta_muerto(), true);
}

TEST_F(PersonajeJazzTest, Revivir){
    uint8_t vida_incial = personaje->obtener_vida();
    std::chrono::duration<double> tiempo_transcurrido(0.5);
    personaje->recibir_golpe(vida_incial + uint8_t(10), tiempo_transcurrido); // le hago un danio mayor a su vida
    personaje->revivir();
    EXPECT_EQ(personaje->esta_muerto(), false);
    EXPECT_EQ(personaje->obtener_vida(), vida_incial); // VEO QUE SU VIDA SEA IGUAL A LA INICIAL
}


TEST_F(PersonajeJazzTest, Curarse){
    uint8_t vida_inicial = personaje->obtener_vida();
    personaje->volverse_vulnerable();
    personaje->recibir_golpe(vida_inicial - 10, std::chrono::duration<double>(0.5));
    personaje->curarse(10);
    EXPECT_EQ(personaje->obtener_vida(), vida_inicial);
}

TEST_F(PersonajeJazzTest, ComienzaSinPuntos){
    EXPECT_EQ(personaje->obtener_puntos(), 0);
}

TEST_F(PersonajeJazzTest, AsignarPuntos){
    uint32_t puntos_iniciales = personaje->obtener_puntos();
    personaje->asignar_puntos(10);
    EXPECT_EQ(personaje->obtener_puntos(), puntos_iniciales + 10);
}
//TEST PARTICULAR DE JAZZ


TEST_F(PersonajeJazzTest, obtenerPersonaje){
    EXPECT_EQ(personaje->obtener_personaje(), JAZZ);
    
}





int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Personaje JAZZ\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}