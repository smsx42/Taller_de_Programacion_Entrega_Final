#include "estado_muerto.h"
#include "estado_quieto.h"
#include "estado_caminando.h"
#include "estado_corriendo.h"
#include "estado_saltando.h"
#include "estado_herido.h"
#include "estado_especial.h"
#include "estado_cayendo.h"
#include "estado_tambalear.h"

#define CONFIG Configuracion::config()

EstadoMuerto::EstadoMuerto(double tiempo_muerte) : Estado(ESTADO_MUERTO){
    this->tiempo_muerte = tiempo_muerte;
    this->cambiar_estado = false;
}



void EstadoMuerto::manejarEstado(uint8_t codigo_estado, double tiempo){

    if(!cambiar_estado){
        return;
    }

    switch (codigo_estado)
    {
    case ESTADO_CAMINANDO:
        this->personaje->cambiarEstado(new EstadoCaminando());
        break;
    case ESTADO_CORRIENDO:
        this->personaje->cambiarEstado(new EstadoCorriendo());
        break;
    case ESTADO_SALTANDO:
        this->personaje->cambiarEstado(new EstadoSaltando());
        break;
    case ESTADO_HERIDO:
        this->personaje->cambiarEstado(new EstadoHerido(tiempo));
        break;
    case ESTADO_ESPECIAL:
        this->personaje->cambiarEstado(new EstadoEspecial());
        break;
    case ESTADO_CAYENDO:
        this->personaje->cambiarEstado(new EstadoCayendo());
        break;
    case ESTADO_TAMBALEAR:
        this->personaje->cambiarEstado(new EstadoTambalear());
        break;
    
    default:
        break;
    }
}

void EstadoMuerto::actualizar(double tiempo){
    if(tiempo - tiempo_muerte >= CONFIG.getTiempoEstadoMuerto()){
        cambiar_estado = true;
        this->personaje->revivir();
        this->personaje->volverse_invulnerable(tiempo);
        this->personaje->cambiarEstado(new EstadoQuieto());
    }
}
