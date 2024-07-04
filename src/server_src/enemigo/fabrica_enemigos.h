#ifndef FABRICA_ENEMIGOS_H_
#define FABRICA_ENEMIGOS_H_

#include <memory>
#include "enemigo.h"
#include "enemigo_fencer.h"
#include "enemigo_lizzard.h"
#include "enemigo_rat.h"
#include "enemigo_bruja.h"

#define CONFIG Configuracion::config()

class FabricaEnemigos{
    
public:
    FabricaEnemigos(){
        
    }
    std::unique_ptr<Enemigo> crear_enemigo(uint32_t id, uint8_t codigo_enemigo, uint32_t posicion_x,uint32_t posicion_y){
        
        switch(codigo_enemigo){
            case FENCER:
                return std::make_unique<Fencer>(id,posicion_x,posicion_y);
            case LIZZARD:
                return std::make_unique<Lizzard>(id,posicion_x,posicion_y);
            case RAT:
                return std::make_unique<Rat>(id,posicion_x,posicion_y);
            case BRUJA:
                return std::make_unique<Bruja>(id,posicion_x,posicion_y);
            default:
                return nullptr;
        }
    }
    
};


#endif