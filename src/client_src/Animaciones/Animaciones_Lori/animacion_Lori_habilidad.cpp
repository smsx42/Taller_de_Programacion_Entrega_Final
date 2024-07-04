#include "animacion_Lori_habilidad.h"

Animacion_Lori_Habilidad::Animacion_Lori_Habilidad() : Animacion() {}

void Animacion_Lori_Habilidad::crear_texturas(SDL2pp::Renderer *render) {
    this->texturas = std::unique_ptr<SDL2pp::Texture>(new SDL2pp::Texture(this->crear_surface_y_texturas(PATH_LORI_HABILIDAD, render)));
    this->set_size_frames_y_cantida_frames();
}

Animacion_Lori_Habilidad::~Animacion_Lori_Habilidad() {}