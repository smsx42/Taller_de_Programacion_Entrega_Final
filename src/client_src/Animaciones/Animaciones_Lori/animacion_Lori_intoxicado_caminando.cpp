#include "animacion_Lori_intoxicado_caminando.h"

Animacion_Lori_Intoxicado_Caminando::Animacion_Lori_Intoxicado_Caminando() : Animacion() {}

void Animacion_Lori_Intoxicado_Caminando::crear_texturas(SDL2pp::Renderer *render) {
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_INTOXICADO_CAMINANDO, render)));
    this->size_frame = texturas->GetHeight();
    this->cantidad_frames = texturas->GetWidth() / this->size_frame;

} 

Animacion_Lori_Intoxicado_Caminando::~Animacion_Lori_Intoxicado_Caminando() {}