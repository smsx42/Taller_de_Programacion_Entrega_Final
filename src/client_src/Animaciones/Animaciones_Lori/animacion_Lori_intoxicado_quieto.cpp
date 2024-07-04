#include "animacion_Lori_intoxicado_quieto.h"

Animacion_Lori_Intoxicado_Quieto::Animacion_Lori_Intoxicado_Quieto() : Animacion() {}

void Animacion_Lori_Intoxicado_Quieto::crear_texturas(SDL2pp::Renderer *render) {
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_INTOXICADO_QUIETO, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;
} 

Animacion_Lori_Intoxicado_Quieto::~Animacion_Lori_Intoxicado_Quieto() {}