#include "personajeLoriViewFactory.h"

PersonajeLoriViewFactory::PersonajeLoriViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones) : 
PersonajeViewFactory(animaciones) {}


std::unique_ptr<Animacion> PersonajeLoriViewFactory::crear_animacion(std::string const nombre_animacion) {
    
    if(nombre_animacion == CAMINANDO) {
        return std::move(std::make_unique<Animacion_Lori_Caminando>());
    } else if(nombre_animacion == CORRIENDO) {
        return std::move(std::make_unique<Animacion_Lori_Corriendo>());
    } else if(nombre_animacion == QUIETO_CLIENTE) {
        return std::move(std::make_unique<Animacion_Lori_Quieto>());
    } else if(nombre_animacion == SALTANDO) {
        return std::move(std::make_unique<Animacion_Lori_Saltando>());
    } else if(nombre_animacion == DISPARO_QUIETO) {
        return std::move(std::make_unique<Animacion_Lori_Disparo_Quieto>());
    } else if(nombre_animacion == DEJA_DISPARO_QUIETO) {
        return std::move(std::make_unique<Animacion_Lori_Deja_Disparo_Quieto>());
    } else if(nombre_animacion == INTOXICADO_QUIETO) {
        return std::move(std::make_unique<Animacion_Lori_Intoxicado_Quieto>());
    } else if(nombre_animacion == INTOXICADO_CAMINANDO) {
        return std::move(std::make_unique<Animacion_Lori_Intoxicado_Caminando>());
    } else if(nombre_animacion == HERIDO) {
        return std::move(std::make_unique<Animacion_Lori_Herido>());
    } else if(nombre_animacion == MUERTO) {
        return std::move(std::make_unique<Animacion_Lori_Muerte>());
    } else if(nombre_animacion == HABILIDAD) {
        return std::move(std::make_unique<Animacion_Lori_Habilidad>());
    } else if(nombre_animacion == CAYENDO) {
        return std::move(std::make_unique<Animacion_Lori_Cayendo>());
    } else if(nombre_animacion == CAYENDO_HORIZONTAL) {
        return std::move(std::make_unique<Animacion_Lori_Cayendo_Horizontal>());
    } else if(nombre_animacion == SALTANDO_HORIZONTAL){
        return std::move(std::make_unique<Animacion_Lori_Cayendo_Horizontal>());
    } else if(nombre_animacion == DISPARO_SALTANDO){
        return std::move(std::make_unique<Animacion_Lori_Disparo_Saltando>());
    } else if(nombre_animacion == TAMBALEAR){
        return std::move(std::make_unique<Animacion_Lori_Tambalear>());
    }
    

    return std::move(std::make_unique<Animacion_Lori_Quieto>());
}


PersonajeLoriViewFactory::~PersonajeLoriViewFactory() {}