#include "personajeJazzViewFactory.h"

PersonajeJazzViewFactory::PersonajeJazzViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones) : 
PersonajeViewFactory(animaciones) {}


std::unique_ptr<Animacion> PersonajeJazzViewFactory::crear_animacion(std::string const nombre_animacion) {
    
    if(nombre_animacion == CAMINANDO) {
        return std::move(std::make_unique<Animacion_Jazz_Caminando>());
    } else if(nombre_animacion == CORRIENDO) {
        return std::move(std::make_unique<Animacion_Jazz_Corriendo>());
    } else if(nombre_animacion == QUIETO_CLIENTE) {
        return std::move(std::make_unique<Animacion_Jazz_Quieto>());
    } else if(nombre_animacion == SALTANDO) {
        return std::move(std::make_unique<Animacion_Jazz_Saltando>());
    } else if(nombre_animacion == DISPARO_QUIETO) {
        return std::move(std::make_unique<Animacion_Jazz_Disparo_Quieto>());
    } else if(nombre_animacion == DEJA_DISPARO_QUIETO) {
        return std::move(std::make_unique<Animacion_Jazz_Deja_Disparo_Quieto>());
    } else if(nombre_animacion == INTOXICADO_QUIETO) {
        return std::move(std::make_unique<Animacion_Jazz_Intoxicado_Quieto>());
    } else if(nombre_animacion == INTOXICADO_CAMINANDO) {
        return std::move(std::make_unique<Animacion_Jazz_Intoxicado_Caminando>());
    } else if(nombre_animacion == HERIDO) {
        return std::move(std::make_unique<Animacion_Jazz_Herido>());
    } else if(nombre_animacion == MUERTO) {
        return std::move(std::make_unique<Animacion_Jazz_Muerte>());
    } else if(nombre_animacion == HABILIDAD) {
        return std::move(std::make_unique<Animacion_Jazz_Habilidad>());
    } else if(nombre_animacion == CAYENDO) {
        return std::move(std::make_unique<Animacion_Jazz_Cayendo>());
    } else if(nombre_animacion == CAYENDO_HORIZONTAL) {
        return std::move(std::make_unique<Animacion_Jazz_Cayendo_Horizontal>());
    } else if(nombre_animacion == SALTANDO_HORIZONTAL){
        return std::move(std::make_unique<Animacion_Jazz_Cayendo_Horizontal>());
    } else if(nombre_animacion == DISPARO_SALTANDO){
        return std::move(std::make_unique<Animacion_Jazz_Disparo_Saltando>());
    } else if(nombre_animacion == TAMBALEAR){
        return std::move(std::make_unique<Animacion_Jazz_Tambalear>());
    }
    else {
        return std::move(std::make_unique<Animacion_Jazz_Quieto>());
    }
    
}


PersonajeJazzViewFactory::~PersonajeJazzViewFactory() {}