#include "estado_caminando.h"
#include "estado_quieto.h"
#include "estado_corriendo.h"
#include "estado_saltando.h"
#include "estado_herido.h"
#include "estado_muerto.h"
#include "estado_especial.h"
#include "estado_cayendo.h"

EstadoCaminando::EstadoCaminando() : Estado(ESTADO_CAMINANDO){}

void EstadoCaminando::manejarEstado(uint8_t codigo_estado, double tiempo){
    switch (codigo_estado)
    {
    case ESTADO_QUIETO:
        this->personaje->cambiarEstado(new EstadoQuieto());
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
    case ESTADO_MUERTO: 
        this->personaje->cambiarEstado(new EstadoMuerto(tiempo));
        break;
    case ESTADO_ESPECIAL:
        this->personaje->cambiarEstado(new EstadoEspecial());
        break;
    case ESTADO_CAYENDO:
        this->personaje->cambiarEstado(new EstadoCayendo());
        break;

    
    default:
        break;
    }
}

void EstadoCaminando::actualizar(double tiempo){
    
}