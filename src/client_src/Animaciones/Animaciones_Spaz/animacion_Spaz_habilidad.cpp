#include "animacion_Spaz_habilidad.h"

Animacion_Spaz_Habilidad::Animacion_Spaz_Habilidad() : Animacion() {}

void Animacion_Spaz_Habilidad::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_SPAZ_HABILIDAD, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Spaz_Habilidad::~Animacion_Spaz_Habilidad() {}