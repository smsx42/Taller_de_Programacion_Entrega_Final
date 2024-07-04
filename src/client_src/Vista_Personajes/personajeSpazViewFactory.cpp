#include "personajeSpazViewFactory.h"

PersonajeSpazViewFactory::PersonajeSpazViewFactory(std::map<std::string, std::unique_ptr<Animacion>> &animaciones) : 
PersonajeViewFactory(animaciones) {}


std::unique_ptr<Animacion> PersonajeSpazViewFactory::crear_animacion(std::string const nombre_animacion) {
    
    if(nombre_animacion == CAMINANDO) {
        return std::move(std::make_unique<Animacion_Spaz_Caminando>());
    } else if(nombre_animacion == CORRIENDO) {
        return std::move(std::make_unique<Animacion_Spaz_Corriendo>());
    } else if(nombre_animacion == QUIETO_CLIENTE) {
        return std::move(std::make_unique<Animacion_Spaz_Quieto>());
    } else if(nombre_animacion == SALTANDO) {
        return std::move(std::make_unique<Animacion_Spaz_Saltando>());
    } else if(nombre_animacion == DISPARO_QUIETO) {
        return std::move(std::make_unique<Animacion_Spaz_Disparo_Quieto>());
    } else if(nombre_animacion == DEJA_DISPARO_QUIETO) {
        return std::move(std::make_unique<Animacion_Spaz_Deja_Disparo_Quieto>());
    } else if(nombre_animacion == INTOXICADO_QUIETO) {
        return std::move(std::make_unique<Animacion_Spaz_Intoxicado_Quieto>());
    } else if(nombre_animacion == INTOXICADO_CAMINANDO) {
        return std::move(std::make_unique<Animacion_Spaz_Intoxicado_Caminando>());
    } else if(nombre_animacion == HERIDO) {
        return std::move(std::make_unique<Animacion_Spaz_Herido>());
    } else if(nombre_animacion == MUERTO) {
        return std::move(std::make_unique<Animacion_Spaz_Muerte>());
    } else if(nombre_animacion == HABILIDAD) {
        return std::move(std::make_unique<Animacion_Spaz_Habilidad>());
    } else if(nombre_animacion == CAYENDO) {
        return std::move(std::make_unique<Animacion_Spaz_Cayendo>());
    } else if(nombre_animacion == CAYENDO_HORIZONTAL) {
        return std::move(std::make_unique<Animacion_Spaz_Cayendo_Horizontal>());
    } else if(nombre_animacion == SALTANDO_HORIZONTAL){
        return std::move(std::make_unique<Animacion_Spaz_Saltando_Horizontal>());
    } else if(nombre_animacion == DISPARO_SALTANDO){
        return std::move(std::make_unique<Animacion_Spaz_Disparo_Saltando>());
    } else if(nombre_animacion == TAMBALEAR){
        return std::move(std::make_unique<Animacion_Spaz_Tambalear>());
    }
    
    return std::move(std::make_unique<Animacion_Spaz_Quieto>());
}


PersonajeSpazViewFactory::~PersonajeSpazViewFactory() {}