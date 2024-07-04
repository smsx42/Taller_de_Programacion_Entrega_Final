#include "animacion_Spaz_deja_disparo_quieto.h"

Animacion_Spaz_Deja_Disparo_Quieto::Animacion_Spaz_Deja_Disparo_Quieto() : Animacion() {}

void Animacion_Spaz_Deja_Disparo_Quieto::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_SPAZ_DEJA_DISPARO_QUIETO, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Spaz_Deja_Disparo_Quieto::~Animacion_Spaz_Deja_Disparo_Quieto() {}