#include "animacion_Jazz_intoxicado_caminando.h"

Animacion_Jazz_Intoxicado_Caminando::Animacion_Jazz_Intoxicado_Caminando() : Animacion() {}

void Animacion_Jazz_Intoxicado_Caminando::crear_texturas(SDL2pp::Renderer *render) {
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_JAZZ_INTOXICADO_CAMINANDO, render)));
    this->set_size_frames_y_cantida_frames();

} 

Animacion_Jazz_Intoxicado_Caminando::~Animacion_Jazz_Intoxicado_Caminando() {}