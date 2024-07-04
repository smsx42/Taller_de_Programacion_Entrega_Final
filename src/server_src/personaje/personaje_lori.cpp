#include "personaje_lori.h"


#define CONFIG Configuracion::config()

Lori::Lori(uint32_t id_jugador, std::vector<SpawnPoint> spawns): Personaje(id_jugador, spawns) { 
    tiempo_especial = -CONFIG.getEnfriamientoHabilidadLori(); 
    danio_habilidad = CONFIG.getDanioHabilidadLori();
    
}

uint8_t Lori::obtener_personaje() { return LORI; }

void Lori::usar_habilidad(std::chrono::duration<double> tiempo_transcurrido) {
    if (!saltando && !corriendo &&
        (tiempo_transcurrido.count() - tiempo_especial) >= CONFIG.getEnfriamientoHabilidadLori()) {
        velocidad_y = -CONFIG.getVelocidadYHabilidadLori();
        if (direccion_mirando == DERECHA) {
            velocidad_x = CONFIG.getVelocidadXHabilidadLori();
        } else {
            velocidad_x = -CONFIG.getVelocidadXHabilidadLori();
        }
        esta_quieto = false;
        saltando = true;
        en_superficie = false;
        usando_especial = true;
        tiempo_salto = tiempo_transcurrido.count();
        tiempo_especial = tiempo_transcurrido.count();
        this->estado->manejarEstado(ESTADO_ESPECIAL, tiempo_transcurrido.count());
    }
}


void Lori::actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido,
                               std::map<uint32_t, Objeto*>& map_objetos, std::map<uint32_t, std::unique_ptr<Objeto>>& map_objetos_comunes) {
    
    Personaje::actualizar_posicion(tiempo_transcurrido, map_objetos, map_objetos_comunes);
    if (en_superficie && usando_especial) {
        velocidad_x = 0;
        usando_especial = false;
        this->estado->manejarEstado(ESTADO_QUIETO, tiempo_transcurrido.count());
    }
}
