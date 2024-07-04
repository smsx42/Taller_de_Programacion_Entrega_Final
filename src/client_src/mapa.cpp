#include "mapa.h"

std::string extraerNombre(const std::string& path) {
    // Encuentra la posición de la última barra '/'
    size_t posSlash = path.find_last_of('/');
    // Encuentra la posición del último punto '.'
    size_t posDot = path.find_last_of('.');

    // Si no se encuentra '/' o '.', devuelve una cadena vacía
    if (posSlash == std::string::npos || posDot == std::string::npos || posDot <= posSlash) {
        return "";
    }

    // Extrae la parte entre '/' y '.'
    return path.substr(posSlash + 1, posDot - posSlash - 1);
}

Mapa::Mapa(SDL2pp::Renderer &render, MapaCompleto &&map): 
mapa(std::move(map)), src(), dest(), ancho_ventana(render.GetOutputWidth()), alto_ventana(render.GetOutputHeight())
{
    std::string tematica_fondo = extraerNombre(mapa.fondo);
    SDL2pp::Surface fondo(mapa.fondo);
    texturas[tematica_fondo] = new SDL2pp::Texture(render, fondo); // El mapa si o si debe tener un fondo?
    SDL2pp::Surface fondo_final("../src/client_src/Images/fondo_final.png");
    texturas["fondo_final"] = new SDL2pp::Texture(render, fondo_final);

    for(const auto& pos : mapa.entidades["miscelaneo"]) {
        std::string nombre_entidad = extraerNombre(pos.imagen);
        auto it = texturas.find(nombre_entidad);
        if (it != texturas.end()) {
            continue;
        } else {
            SDL2pp::Surface surface(pos.imagen);
            texturas[nombre_entidad] = new SDL2pp::Texture(render, surface);
        }
    }

    for(const auto& pos : mapa.entidades["solids"]) {
        std::string nombre_entidad = extraerNombre(pos.imagen);
        auto it = texturas.find(nombre_entidad);
        if (it != texturas.end()) {
            continue;
        } else {
            SDL2pp::Surface surface(pos.imagen);
            texturas[nombre_entidad] = new SDL2pp::Texture(render, surface);
        }
    }

    for(const auto& pos : mapa.entidades["triangulo_derecho"]) {
        std::string nombre_entidad = extraerNombre(pos.imagen);
        auto it = texturas.find(nombre_entidad);
        if (it != texturas.end()) {
            continue;
        } else {
            SDL2pp::Surface surface(pos.imagen);
            texturas[nombre_entidad] = new SDL2pp::Texture(render, surface);
        }
    }

    for(const auto& pos : mapa.entidades["triangulo_izquierdo"]) {
        std::string nombre_entidad = extraerNombre(pos.imagen);
        auto it = texturas.find(nombre_entidad);
        if (it != texturas.end()) {
            continue;
        } else {
            SDL2pp::Surface surface(pos.imagen);
            texturas[nombre_entidad] = new SDL2pp::Texture(render, surface);
        }
    }

};

void Mapa::dibujar_fondo(SDL2pp::Renderer &render, Camara &camara) {
    src.x = 0;
    src.y = 0;
    src.w = ancho_ventana;
    src.h = alto_ventana;

    dest.x = 0;
    dest.y = 0;
    dest.w = ancho_ventana;
    dest.h = alto_ventana;
    render.Copy(*texturas[extraerNombre(mapa.fondo)], src, dest);
}

void Mapa::dibujar_fondo_final(SDL2pp::Renderer &render) {
    src.x = 0;
    src.y = 0;
    src.w = ancho_ventana;
    src.h = alto_ventana;

    dest.x = 0;
    dest.y = 0;
    dest.w = ancho_ventana;
    dest.h = alto_ventana;
    render.Copy(*texturas["fondo_final"], src, dest);
}

void Mapa::dibujar_entidades(SDL2pp::Renderer &render, Camara &camara) {
    for (const auto& pos : mapa.entidades["miscelaneo"]) {
        src.w = pos.width;
        src.h = pos.height;
        dest.x = pos.x - camara.obtener_posicion_x();
        dest.y = pos.y - camara.obtener_posicion_y();
        dest.w = pos.width;
        dest.h = pos.height;
        std::string nombre_entidad = extraerNombre(pos.imagen);
        render.Copy(*texturas[nombre_entidad], src, dest);
    }
    
    for (const auto& pos : mapa.entidades["solids"]) {
        src.w = pos.width;
        src.h = pos.height;
        dest.x = pos.x - camara.obtener_posicion_x();
        dest.y = pos.y - camara.obtener_posicion_y();
        dest.w = pos.width;
        dest.h = pos.height;
        std::string nombre_entidad = extraerNombre(pos.imagen);
        render.Copy(*texturas[nombre_entidad], src, dest);
    }

    for (const auto& pos : mapa.entidades["triangulo_derecho"]) {
        src.w = pos.width;
        src.h = pos.height;
        dest.x = pos.x - camara.obtener_posicion_x();
        dest.y = pos.y - camara.obtener_posicion_y();
        dest.w = pos.width;
        dest.h = pos.height;
        std::string nombre_entidad = extraerNombre(pos.imagen);
        render.Copy(*texturas[nombre_entidad], src, dest);
    }

    for (const auto& pos : mapa.entidades["triangulo_izquierdo"]) {
        src.w = pos.width;
        src.h = pos.height;
        dest.x = pos.x - camara.obtener_posicion_x();
        dest.y = pos.y - camara.obtener_posicion_y();
        dest.w = pos.width;
        dest.h = pos.height;
        std::string nombre_entidad = extraerNombre(pos.imagen);
        render.Copy(*texturas[nombre_entidad], src, dest);
    }

}

Mapa::~Mapa() {
    for (auto it = texturas.begin(); it != texturas.end(); ++it) {
        delete it->second; 
    }
}
