#ifndef FABRICA_OBJETOS_H_
#define FABRICA_OBJETOS_H_

#include <memory>
#include "objeto_zanahoria.h"
#include "objeto_gema.h"
#include "objeto_moneda.h"
#include "objeto_municion.h"

#define CONFIG Configuracion::config()

class FabricaObjetos{
    uint32_t id;
public:
    FabricaObjetos(){
        id = -1;
    }
    std::unique_ptr<Objeto> crear_objeto(uint8_t codigo_objeto, uint32_t posicion_x,uint32_t posicion_y, bool envenenado){
        id++;
        switch(codigo_objeto){
            case ZANAHORIA:
                return std::make_unique<Zanahoria>(id,posicion_x,posicion_y,REAPARICION_ZANAHORIA,ANCHO_ZANAHORIA,ALTO_ZANAHORIA, envenenado);
            case GEMA:
                return std::make_unique<Gema>(id,posicion_x,posicion_y,REAPARICION_GEMA,ANCHO_GEMA,ALTO_GEMA, envenenado);
            case MONEDA:
                return std::make_unique<Moneda>(id,posicion_x,posicion_y,REAPARICION_MONEDA,ANCHO_MONEDA,ALTO_MONEDA, envenenado);
            case BALA_VELOZ:{
                const ConfigBala& config_bala = CONFIG.obtenerBala(codigo_objeto);
                return std::make_unique<Municion>(id,posicion_x,posicion_y,config_bala.tiempo_reaparicion, config_bala.ancho,config_bala.largo, codigo_objeto, config_bala.municion);
            }
            case COHETE_RAPIDO:{
                const ConfigBala& config_bala = CONFIG.obtenerBala(codigo_objeto);
                return std::make_unique<Municion>(id,posicion_x,posicion_y,config_bala.tiempo_reaparicion, config_bala.ancho,config_bala.largo, codigo_objeto, config_bala.municion);
            }
            case COHETE_TOXICO:{
                const ConfigBala& config_bala = CONFIG.obtenerBala(codigo_objeto);
                return std::make_unique<Municion>(id,posicion_x,posicion_y,config_bala.tiempo_reaparicion, config_bala.ancho,config_bala.largo, codigo_objeto, config_bala.municion);
            }
            default:
                return nullptr;
        }
    }
    
};


#endif