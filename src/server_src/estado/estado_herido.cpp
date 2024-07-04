#include "estado_herido.h"
#include "estado_quieto.h"
#include "estado_caminando.h"
#include "estado_corriendo.h"
#include "estado_saltando.h"
#include "estado_muerto.h"
#include "estado_especial.h"
#include "estado_cayendo.h"
#include "estado_tambalear.h"

#define CONFIG Configuracion::config()


EstadoHerido::EstadoHerido(double tiempo_impacto) : Estado(ESTADO_HERIDO){
    this->tiempo_impacto = tiempo_impacto;
    this->cambiar_animacion = false;
}



void EstadoHerido::manejarEstado(uint8_t codigo_estado, double tiempo){

    if(codigo_estado == ESTADO_MUERTO){
        this->personaje->cambiarEstado(new EstadoMuerto(tiempo));
        return;
    }


    if(!cambiar_animacion){
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
    case ESTADO_QUIETO:
        this->personaje->cambiarEstado(new EstadoQuieto());
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

void EstadoHerido::actualizar(double tiempo){
    if(tiempo - tiempo_impacto >= CONFIG.getTiempoEstadoHerido()){
        cambiar_animacion = true;
    }
}