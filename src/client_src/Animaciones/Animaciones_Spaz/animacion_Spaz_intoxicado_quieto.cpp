#include "animacion_Spaz_intoxicado_quieto.h"

Animacion_Spaz_Intoxicado_Quieto::Animacion_Spaz_Intoxicado_Quieto() : Animacion() {}

void Animacion_Spaz_Intoxicado_Quieto::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_SPAZ_INTOXICADO_QUIETO, render)));
    this->size_frame = 44.375F;
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
}

Animacion_Spaz_Intoxicado_Quieto::~Animacion_Spaz_Intoxicado_Quieto() {}