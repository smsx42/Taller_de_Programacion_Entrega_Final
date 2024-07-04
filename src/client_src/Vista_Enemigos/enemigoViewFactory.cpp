#include "enemigoViewFactory.h"

EnemigoViewFactory::EnemigoViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones) : animaciones(animaciones) {}

void EnemigoViewFactory::crear_texturas(SDL2pp::Renderer *render) {
    
    this->animaciones.at(CAMINANDO)->crear_texturas(render);
    this->animaciones.at(DESAPARECER)->crear_texturas(render);

}

std::unique_ptr<Animacion> EnemigoViewFactory::crear_animacion_enemigo(std::string const nombre_enemigo) {

    if(nombre_enemigo == ENEMIGO_LIZZARD) {
        return std::move(std::make_unique<Animacion_Lizzard_Caminando>());
    } else if(nombre_enemigo == ENEMIGO_FENCER) {
        return std::move(std::make_unique<Animacion_Fencer_Caminando>());
    } else if(nombre_enemigo == ENEMIGO_BRUJA){
        return std::move(std::make_unique<Animacion_Bruja_Caminando>());
    } else if(nombre_enemigo == ENEMIGO_RAT) {
        return std::move(std::make_unique<Animacion_Rat_Caminando>());
    }
    
    return std::move(std::make_unique<Animacion_Enemigo_Desaparecer>());

}

EnemigoViewFactory::~EnemigoViewFactory() {}