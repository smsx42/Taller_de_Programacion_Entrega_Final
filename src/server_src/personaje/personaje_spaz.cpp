#include "personaje_spaz.h"

#define CONFIG Configuracion::config()

Spaz::Spaz(uint32_t id_jugador, std::vector<SpawnPoint> spawns): Personaje(id_jugador, spawns) { 
    tiempo_especial = - CONFIG.getEnfriamientoHabilidadSpaz(); 
    danio_habilidad = CONFIG.getDanioHabilidadSpaz();
    
}

uint8_t Spaz::obtener_personaje() { return SPAZ; }

void Spaz::usar_habilidad(std::chrono::duration<double> tiempo_transcurrido) {
    if (!saltando && !usando_especial &&
        (tiempo_transcurrido.count() - tiempo_especial) >= CONFIG.getEnfriamientoHabilidadSpaz()) {
        esta_quieto = false;
        tiempo_especial = tiempo_transcurrido.count();
        usando_especial = true;
        if (direccion_mirando == DERECHA) {
            velocidad_x = CONFIG.getVelocidadXHabilidadSpaz();
        } else {
            velocidad_x = -CONFIG.getVelocidadXHabilidadSpaz();
        }
        this->estado->manejarEstado(ESTADO_ESPECIAL, tiempo_transcurrido.count());
    }
}

void Spaz::mover_arriba(std::chrono::duration<double> tiempo_transcurrido) {
    if(usando_especial){
        return;
    }
    Personaje::mover_arriba(tiempo_transcurrido);
}

void Spaz::quedarse_quieto() {
    if (!usando_especial) {
        velocidad_x = 0;
        esta_quieto = true;
    }
}

void Spaz::actualizar_posicion(std::chrono::duration<double> tiempo_transcurrido,
                               std::map<uint32_t, Objeto*>& map_objetos, std::map<uint32_t, std::unique_ptr<Objeto>>& map_objetos_comunes) {
    Personaje::actualizar_posicion(tiempo_transcurrido, map_objetos, map_objetos_comunes);
    if (usando_especial) {
        if (tiempo_transcurrido.count() - tiempo_especial > 0.75) { // Tiempo que dura el desplazamiento
            usando_especial = false;
            velocidad_x = 0;
            esta_quieto = true;
        }
    }
}
