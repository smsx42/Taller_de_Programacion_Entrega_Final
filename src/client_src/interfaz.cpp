#include "interfaz.h"

static const int ICONO_WIDTH = 30;
static const int ICONO_HEIGHT = 24;
static const int OFFSET_X = 5;
static const int OFFSET_Y = 7;
static const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
static const SDL_Color COLOR_RED = {255, 0, 0, 255};
static const SDL_Color COLOR_GREEN = {0, 255, 0, 255};

Interfaz::Interfaz(SDL2pp::Renderer &render, int ancho, int alto, uint32_t id_jugador):
ancho_ventana(ancho), 
alto_ventana(alto), 
rect(),
sdl_ttf(),
font("../src/client_src/Images/Jazz_Ball_Regular.ttf", 24), 
id_jugador(id_jugador), 
texto(),
tiempo(0),
puntajes()
{
        SDL2pp::Surface vida("../src/client_src/Images/vida.png");
        vida.SetColorKey(true, SDL_MapRGB(vida.Get()->format, 0, 128, 255));
        SDL2pp::Surface tiempo("../src/client_src/Images/tiempo.png");
        tiempo.SetColorKey(true, SDL_MapRGB(tiempo.Get()->format, 0, 128, 255));
        SDL2pp::Surface bala_tipo_3("../src/client_src/Images/bala_tipo_0.png");
        bala_tipo_3.SetColorKey(true, SDL_MapRGB(bala_tipo_3.Get()->format, 44, 102, 150));        
        SDL2pp::Surface bala_tipo_4("../src/client_src/Images/bala_tipo_1.png");
        bala_tipo_4.SetColorKey(true, SDL_MapRGB(bala_tipo_4.Get()->format, 0, 128, 255));
        SDL2pp::Surface bala_tipo_5("../src/client_src/Images/bala_tipo_2.png");
        bala_tipo_5.SetColorKey(true, SDL_MapRGB(bala_tipo_5.Get()->format, 0, 128, 255));
        SDL2pp::Surface bala_tipo_6("../src/client_src/Images/bala_tipo_3.png");
        bala_tipo_6.SetColorKey(true, SDL_MapRGB(bala_tipo_6.Get()->format, 0, 128, 255));
        SDL2pp::Surface fondo_final("../src/client_src/Images/fondo_final.png");
        fondo_final.SetColorKey(true, SDL_MapRGB(fondo_final.Get()->format, 0, 128, 255));

        texturas["tiempo"] = new SDL2pp::Texture(render, tiempo);
        texturas["vida"] = new SDL2pp::Texture(render, vida);
        texturas["bala_tipo_3"] = new SDL2pp::Texture(render, bala_tipo_3);
        texturas["bala_tipo_4"] = new SDL2pp::Texture(render, bala_tipo_4);
        texturas["bala_tipo_5"] = new SDL2pp::Texture(render, bala_tipo_5);
        texturas["bala_tipo_6"] = new SDL2pp::Texture(render, bala_tipo_6);
        texturas["fondo_final"] = new SDL2pp::Texture(render, fondo_final);

}


void Interfaz::definir_puntaje(uint32_t puntaje) {
    this->puntos = puntaje;
}


void Interfaz::definir_tiempo(uint16_t tiempo) {
    this->tiempo = tiempo;
}

void Interfaz::mostrar_texto(SDL2pp::Renderer &render, const std::string &texto, SDL_Color color, int x, int y, int w, int h) {
    SDL2pp::Surface surface_texto = font.RenderText_Solid(texto, color);
    SDL2pp::Texture texto_textura(render, surface_texto);
    render.Copy(texto_textura, SDL2pp::NullOpt, SDL2pp::Rect(x, y, w, h));
}

void Interfaz::mostrar_tabla_puntajes(SDL2pp::Renderer &render) {
    size_t i = 0;
    SDL_Color color = COLOR_WHITE;
    for (const auto &entry : puntajes) {
        uint32_t id = entry.first;
        uint32_t puntaje = entry.second;
        if (id == id_jugador) {
            color = (id == puntajes[0].first) ? COLOR_GREEN : COLOR_RED;
        }
        std::string texto = std::to_string(id) + ": " + std::to_string(puntaje);
        mostrar_texto(render, texto, color, ancho_ventana / 2 - 30, i * 20, 50, 20);
        i++;
        color = COLOR_WHITE;
    }
}

void Interfaz::mostrar_mensaje_final(SDL2pp::Renderer &render) {
    SDL_Color color;
    std::string texto;

    if (id_jugador == puntajes[0].first) {
        color = COLOR_GREEN;
        texto = "FELICIDADES! HAS GANADO";
    } else {
        color = COLOR_RED;
        texto = "LO SIENTO! HAS PERDIDO";
    }
    mostrar_texto(render, texto, color, ancho_ventana / 2 - 150, 320, 300, 30);
}

void Interfaz::mostrar_tabla_final(SDL2pp::Renderer &render) {
    mostrar_tabla_puntajes(render);
    mostrar_mensaje_final(render);
}

void Interfaz::mostrar_vida(SDL2pp::Renderer &render, PersonajeView &personajeViewPtr) {
    uint8_t vida = personajeViewPtr.obtener_vida();
    std::string texto = std::to_string(vida);
    rect.x = 0;
    rect.y = alto_ventana - ICONO_HEIGHT;
    rect.w = ICONO_WIDTH;
    rect.h = ICONO_HEIGHT;
    render.Copy(*texturas["vida"], SDL2pp::NullOpt, rect);
    mostrar_texto(render, texto, COLOR_WHITE, ICONO_WIDTH + OFFSET_X, alto_ventana - rect.h, ICONO_WIDTH + 10, ICONO_HEIGHT);

}

void Interfaz::mostrar_tiempo(SDL2pp::Renderer &render) {
    std::string texto = std::to_string(tiempo);
    SDL_Color color = COLOR_WHITE;

    if (tiempo <= 30) {
        color = COLOR_RED;
    }

    rect.x = ancho_ventana / 2.0 - ICONO_WIDTH - 10;
    rect.y = OFFSET_Y;
    rect.w = ICONO_WIDTH + OFFSET_X;
    rect.h = ICONO_HEIGHT + OFFSET_X;
    render.Copy(*texturas["tiempo"], SDL2pp::NullOpt, rect);
    mostrar_texto(render, texto, color, ancho_ventana / 2, 10, 40, 20);
}

void Interfaz::mostrar_puntaje_jugador(SDL2pp::Renderer &render, PersonajeView &personajeViewPtr) {
    std::string texto = "x" + std::to_string(personajeViewPtr.obtener_puntos());
    mostrar_texto(render, texto, COLOR_WHITE, 0, 0, 50, 20);
}

void Interfaz::mostrar_top_puntajes(SDL2pp::Renderer &render, std::map<uint32_t, std::unique_ptr<PersonajeView>> &personajesViews) {
    puntajes.clear();

    for (const auto &entry : personajesViews) {
        uint32_t id = entry.first;
        uint32_t puntaje = entry.second->obtener_puntos();
        puntajes.emplace_back(id, puntaje);
    }

    std::sort(puntajes.begin(), puntajes.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });

    std::string texto = "ID: PTS";
    mostrar_texto(render, texto, COLOR_WHITE, ancho_ventana - 70, 0, 50, 20);

    size_t i = 1;
    for (const auto &entry : puntajes) {
        if (i >= 4) return;

        uint32_t id = entry.first;
        uint32_t puntaje = entry.second;

        SDL_Color color = (entry.first == id_jugador) ? COLOR_GREEN : COLOR_WHITE;
        texto = std::to_string(id) + ": " + std::to_string(puntaje);
        mostrar_texto(render, texto, color, ancho_ventana - 70, i * 20, 50, 20);

        i++;
    }
}

void Interfaz::mostrar_municiones(SDL2pp::Renderer &render, PersonajeView &personajeViewPtr) {
    std::string texto = (personajeViewPtr.obtener_cantidad_municion() == -1) ? "INF" : std::to_string(personajeViewPtr.obtener_cantidad_municion());
    mostrar_texto(render, texto, COLOR_WHITE, ancho_ventana - 60, alto_ventana - ICONO_HEIGHT, ICONO_WIDTH + 10, ICONO_HEIGHT);
}

void Interfaz::mostrar_tipo_bala(SDL2pp::Renderer &render, PersonajeView &personajeViewPtr) {
    std::string tipo_bala = "bala_tipo_" + std::to_string(personajeViewPtr.obtener_tipo_bala());
    rect.x = ancho_ventana - ICONO_WIDTH - 70;
    rect.y = alto_ventana - ICONO_HEIGHT;
    rect.w = ICONO_WIDTH;
    rect.h = ICONO_HEIGHT;
    render.Copy(*texturas[tipo_bala], SDL2pp::NullOpt, SDL2pp::Rect(rect.x, rect.y, rect.w, rect.h));
}

void Interfaz::mostrar_hud(SDL2pp::Renderer &render, std::map<uint32_t, std::unique_ptr<PersonajeView>> &personajesViews) {
    auto it = personajesViews.find(id_jugador);
    if (it == personajesViews.end()) {
        return;
    }
    PersonajeView &personajeViewPtr = *(it->second);

    mostrar_vida(render, personajeViewPtr);
    mostrar_tiempo(render);
    mostrar_puntaje_jugador(render, personajeViewPtr);
    mostrar_top_puntajes(render, personajesViews);
    mostrar_municiones(render, personajeViewPtr);
    mostrar_tipo_bala(render, personajeViewPtr);
}

Interfaz::~Interfaz() {
    for (auto& pair : texturas) {
        delete pair.second;
    }
}