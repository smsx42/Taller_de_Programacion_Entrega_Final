#include "animacion_Lori_disparo_quieto.h"

Animacion_Lori_Disparo_Quieto::Animacion_Lori_Disparo_Quieto() : Animacion() {}

void Animacion_Lori_Disparo_Quieto::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_DISPARO_QUIETO, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Lori_Disparo_Quieto::~Animacion_Lori_Disparo_Quieto() {}