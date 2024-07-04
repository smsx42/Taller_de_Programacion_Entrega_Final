#include "animacion_Lori_corriendo.h"

Animacion_Lori_Corriendo::Animacion_Lori_Corriendo() : Animacion() {}

void Animacion_Lori_Corriendo::crear_texturas(SDL2pp::Renderer *render) {
    
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_CORRIENDO, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Lori_Corriendo::~Animacion_Lori_Corriendo() {}