#include "animacion_Spaz_herido.h"

Animacion_Spaz_Herido::Animacion_Spaz_Herido() : Animacion() {}

void Animacion_Spaz_Herido::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_SPAZ_HERIDO, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Spaz_Herido::~Animacion_Spaz_Herido() {}