#include "personajeViewFactory.h"

PersonajeViewFactory::PersonajeViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones) : 
animaciones(animaciones) {}

void PersonajeViewFactory::crear_animaciones_personaje() {
    
    this->animaciones.insert(std::make_pair(CAMINANDO, crear_animacion(CAMINANDO)));
    this->animaciones.insert(std::make_pair(CORRIENDO, crear_animacion(CORRIENDO))); 
    this->animaciones.insert(std::make_pair(QUIETO_CLIENTE, crear_animacion(QUIETO_CLIENTE))); 
    this->animaciones.insert(std::make_pair(SALTANDO, crear_animacion(SALTANDO)));  
    this->animaciones.insert(std::make_pair(DISPARO_QUIETO, crear_animacion(DISPARO_QUIETO))); 
    this->animaciones.insert(std::make_pair(DEJA_DISPARO_QUIETO, crear_animacion(DEJA_DISPARO_QUIETO))); 
    this->animaciones.insert(std::make_pair(INTOXICADO_QUIETO, crear_animacion(INTOXICADO_QUIETO)));
    this->animaciones.insert(std::make_pair(INTOXICADO_CAMINANDO, crear_animacion(INTOXICADO_CAMINANDO)));
    this->animaciones.insert(std::make_pair(HERIDO, crear_animacion(HERIDO)));
    this->animaciones.insert(std::make_pair(MUERTO, crear_animacion(MUERTO)));
    this->animaciones.insert(std::make_pair(HABILIDAD, crear_animacion(HABILIDAD)));
    this->animaciones.insert(std::make_pair(CAYENDO, crear_animacion(CAYENDO)));
    this->animaciones.insert(std::make_pair(CAYENDO_HORIZONTAL, crear_animacion(CAYENDO_HORIZONTAL)));
    this->animaciones.insert(std::make_pair(SALTANDO_HORIZONTAL, crear_animacion(SALTANDO_HORIZONTAL)));
    this->animaciones.insert(std::make_pair(DISPARO_SALTANDO, crear_animacion(DISPARO_SALTANDO))); 
    this->animaciones.insert(std::make_pair(TAMBALEAR, crear_animacion(TAMBALEAR))); 

}

void PersonajeViewFactory::crear_texturas(SDL2pp::Renderer *render) {
    
    
    this->animaciones.at(CAMINANDO)->crear_texturas(render);
    this->animaciones.at(CORRIENDO)->crear_texturas(render);
    this->animaciones.at(QUIETO_CLIENTE)->crear_texturas(render);
    this->animaciones.at(SALTANDO)->crear_texturas(render);
    this->animaciones.at(DISPARO_QUIETO)->crear_texturas(render);
    this->animaciones.at(DEJA_DISPARO_QUIETO)->crear_texturas(render);
    this->animaciones.at(INTOXICADO_QUIETO)->crear_texturas(render);
    this->animaciones.at(INTOXICADO_CAMINANDO)->crear_texturas(render);
    this->animaciones.at(HERIDO)->crear_texturas(render);
    this->animaciones.at(MUERTO)->crear_texturas(render);
    this->animaciones.at(HABILIDAD)->crear_texturas(render);
    this->animaciones.at(CAYENDO)->crear_texturas(render);
    this->animaciones.at(CAYENDO_HORIZONTAL)->crear_texturas(render);
    this->animaciones.at(SALTANDO_HORIZONTAL)->crear_texturas(render);
    this->animaciones.at(DISPARO_SALTANDO)->crear_texturas(render);
    this->animaciones.at(TAMBALEAR)->crear_texturas(render);
    

}
 
PersonajeViewFactory::~PersonajeViewFactory() {}