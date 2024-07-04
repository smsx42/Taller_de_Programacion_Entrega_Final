#include "estado_caminando.h"
#include "estado_quieto.h"
#include "estado_corriendo.h"
#include "estado_saltando.h"
#include "estado_herido.h"
#include "estado_muerto.h"
#include "estado_especial.h"
#include "estado_cayendo.h"
#include "estado_tambalear.h"

EstadoCorriendo::EstadoCorriendo() : Estado(ESTADO_CORRIENDO){
    
}

void EstadoCorriendo::manejarEstado(uint8_t codigo_estado, double tiempo){

    switch (codigo_estado)
    {
    case ESTADO_QUIETO:
        this->personaje->cambiarEstado(new EstadoQuieto());
        break;
    case ESTADO_CAMINANDO:
        this->personaje->cambiarEstado(new EstadoCaminando());
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
    case ESTADO_TAMBALEAR:
        this->personaje->cambiarEstado(new EstadoTambalear());
        break;
    default:
        break;
    }
}

void EstadoCorriendo::actualizar(double tiempo){
    
}