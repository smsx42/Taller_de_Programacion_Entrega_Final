#include "animacion_Jazz_muerte.h"

Animacion_Jazz_Muerte::Animacion_Jazz_Muerte() : Animacion() {}

void Animacion_Jazz_Muerte::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_JAZZ_MUERTE, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Jazz_Muerte::~Animacion_Jazz_Muerte() {}