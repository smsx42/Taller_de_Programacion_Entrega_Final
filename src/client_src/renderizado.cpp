#include "renderizado.h"
#include <string>
#include <iostream>
#include <exception>
#include <unistd.h>
#include <map>
#include "../src/client_src/Animaciones/animacion.h"

Renderizado::Renderizado(std::map<uint32_t, std::unique_ptr<PersonajeView>> &personajesViews) : 
personajesViews(personajesViews), mapa_balas_pj(), musica(nullptr), contador_musica(0) {}

void Renderizado::inicializar_SDL2pp() {

    this->sdl = std::make_unique<SDL2pp::SDL>(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

}

void Renderizado::recibir_id(uint32_t id_jugador){
    this->id_jugador = id_jugador;
}

void Renderizado::iniciar_mapa(MapaCompleto &&map) {
    this->mapa = std::make_unique<Mapa>(*render, std::move(map));
}

void Renderizado::iniciar_camara(Camara &&cam) {
    this->camara = std::make_unique<Camara>(std::move(cam));
}

void Renderizado::iniciar_interfaz(int w, int h) {
    this->interfaz = std::make_unique<Interfaz>(*render, w, h, id_jugador);
}

bool Renderizado::renderizar(Evento evento) {
    if(evento.tiempo_restante == 0) {
        return false;
    }
    /*
    if(contador_musica == 0) {
        musica = std::make_unique<SDL2pp::Music>(PATH_MUSICA_CASTILLO);
        Mix_VolumeMusic(90);
        this->reproductor_audio->PlayMusic(*musica, -1);
        contador_musica ++;
    }
    */
    // Defino tiempo
    this->interfaz->definir_tiempo(evento.tiempo_restante);
    render->Clear();
    std::vector<uint32_t> jugadoresJugando = {}; // Vector de jugadores jugando actualmente
    for(EventoPersonaje evento : evento.eventos_personaje){
        jugadoresJugando.push_back(evento.id_jugador); // Agrego a los jugadores actuales
        if(personajesViews.find(evento.id_jugador) == personajesViews.end()){
            std::unique_ptr<PersonajeView> personaje;
            switch(evento.id_personaje){
                case JAZZ:
                    personaje = std::make_unique<PersonajeJazzView>(evento, render.get());
                    break;
                case SPAZ:
                    personaje = std::make_unique<PersonajeSpazView>(evento, render.get());
                    break;
                case LORI:
                    personaje = std::make_unique<PersonajeLoriView>(evento, render.get());    
            }
            personaje->definir_vida(evento.vida);
            personaje->definir_puntos(evento.puntos);
            personaje->definir_cantidad_municion(evento.municion);
            personaje->definir_tipo_bala(evento.bala_actual);
            personajesViews[evento.id_jugador] = std::move(personaje);
                
        }else{
            PersonajeView &personaje = *(personajesViews.at(evento.id_jugador));
            personaje.definir_vida(evento.vida);
            personaje.definir_puntos(evento.puntos);
            personaje.definir_cantidad_municion(evento.municion);
            personaje.definir_tipo_bala(evento.bala_actual);
            personaje.actualizar_vista_personaje(evento, FRAME_RATE);
        }
    }
    // Saco a los jugadores que ya no estan jugando, es decir, se desconectaron
    {
        for (auto it = personajesViews.begin(); it != personajesViews.end(); ) {
            // Busco el ID en el vector
            if (std::find(jugadoresJugando.begin(), jugadoresJugando.end(), it->first) == jugadoresJugando.end()) {
                // Si no se encuentra, elimino la entrada del mapa
                it = personajesViews.erase(it);
            } else {
                // Si se encuentra, avanzar al siguiente ID
                ++it;
            }
        }
    }
    

    //Creacion del mapa de enemigos del juego
    for(EventoEnemigo &evento : evento.eventos_enemigos) {
        if(enemigosViews.find(evento.id_enemigo) == enemigosViews.end()) {
            std::unique_ptr<EnemigoView> enemigo;
            switch(evento.id_personaje) {
                case LIZZARD:
                    enemigo = std::make_unique<EnemigoLizzardView>(render.get());
                    break;
                case FENCER:
                    enemigo = std::make_unique<EnemigoFencerView>(render.get());
                    break;
                case RAT:
                    enemigo = std::make_unique<EnemigoRatView>(render.get());
                    break;
                case BRUJA:
                    enemigo = std::make_unique<EnemigoBrujaView>(render.get());
                    break;
                default:
                    break;
            }
            enemigosViews[evento.id_enemigo] = std::move(enemigo);
        } else {
            EnemigoView &enemigo = *(enemigosViews.at(evento.id_enemigo));
            enemigo.actualizar_vista_enemigo(evento, FRAME_RATE);
        }
    }
    
    //Crear de gemas, monedas y zanahorias del juego
    for(auto &evento : evento.eventos_objeto) {
        if(objetosViews.find(evento.id_objeto) == objetosViews.end()) {
            std::unique_ptr<ObjetoView> objeto;
            switch(evento.codigo_objeto) {
                case GEMA:
                    objeto = std::make_unique<ObjetoGemaView>(render.get());
                    break;
                case MONEDA:
                    objeto = std::make_unique<ObjetoMonedaView>(render.get());
                    break;
                case ZANAHORIA:
                    objeto = std::make_unique<ObjetoZanahoriaView>(render.get());
                    break;
                case BALA_VELOZ:
                   objeto = std::make_unique<ObjetoMunicionTipo_1View>(render.get());
                   break;
                case COHETE_RAPIDO:
                    objeto = std::make_unique<ObjetoMunicionTipo_2View>(render.get());
                    break; 
                case COHETE_TOXICO:
                    objeto = std::make_unique<ObjetoMunicionTipo_3View>(render.get());
                    break; 
                default:
                    break;
            }
            objetosViews[evento.id_objeto] = std::move(objeto);
        } else {
            ObjetoView &objeto = *(objetosViews.at(evento.id_objeto));
            objeto.actualizar_vista_objeto(evento, FRAME_RATE);
        }
    }
    
    // Creacion del mapa de balas que tendra los jugadores
    for (const EventoBala &e : evento.eventos_bala) {
        mapa_balas_pj.agregarNuevoMapaBalas(e.id_jugador);
    }
    // Actualiza la camara
    {
        auto it = personajesViews.find(id_jugador);
        if (it == personajesViews.end()) {
            // No hago nada.
        } else {
            // Enfoco la camara al jugador.
            PersonajeView &personajeViewPtr = *(it->second);
            camara->actualizar_posicion(personajeViewPtr.obtener_posicion_x(), personajeViewPtr.obtener_posicion_y());   
        }
    }

    // Agrego la bala
    for (const EventoBala &e : evento.eventos_bala) {
        auto it = personajesViews.find(e.id_jugador);
        PersonajeView &personajeViewPtr = *(it->second);

        // Defino la face de la bala
        std::unique_ptr<BalaView> bala_nueva = std::make_unique<BalaView>(personajeViewPtr.obtener_face(), e.posicion_x, e.posicion_y, e.tipo_bala, render.get());
        mapa_balas_pj.agregarBala(e.id_jugador, e.id_bala, std::move(bala_nueva));
    }

    // Renderizo el fondo y HUD
    {
        render->Clear();
        mapa->dibujar_fondo(*render, *camara);
        mapa->dibujar_entidades(*render, *camara);
    }

    // Renderizo balas y verifico el impacto
    for (const EventoBala &e : evento.eventos_bala) {
        BalaView* bala = mapa_balas_pj.obtenerBala(e.id_jugador, e.id_bala);
        bala->actualizar(e, FRAME_RATE);
        bala->renderizar(*render, camara->obtener_posicion_x(), camara->obtener_posicion_y());
        bala->crear_sonido(*reproductor_audio.get());

        if( (bool)e.impacto) {
            mapa_balas_pj.eliminarBala(e.id_jugador, e.id_bala);
        }
    }
    
    // Renderizo enemigos
    for(auto &enemigo : this->enemigosViews) {

        EnemigoView &e = *(enemigo.second);
        e.renderizar_enemigo(render, camara->obtener_posicion_x(), camara->obtener_posicion_y());

        for (auto &personaje : this->personajesViews) {

            PersonajeView &p = *(personaje.second);
            if(p.obtener_id_jugador() == this->id_jugador){
                e.crear_sonido(*this->reproductor_audio);
            }
        }
	}    

    
    
    // Renderizo objetos
    for(auto &objeto : this->objetosViews) {
        ObjetoView &o = *(objeto.second);
        /*
        if(!o.mostrandose()){
            continue;
        }
        */
        o.renderizar_objeto(render, camara->obtener_posicion_x(), camara->obtener_posicion_y());
        o.reproducir_audio_objeto(reproductor_audio);
    }
 
    for (auto &personaje : this->personajesViews) {

        PersonajeView &p = *(personaje.second);
        p.renderizar_personaje(render, camara->obtener_posicion_x(), camara->obtener_posicion_y(), this->reproductor_audio);
        if(p.obtener_id_jugador() == this->id_jugador) {
            p.crear_sonido(*this->reproductor_audio.get());
        }
        
		
	}

    interfaz->mostrar_hud(*render, personajesViews);
    render->Present();
    return true;
}

void Renderizado::crear_ventana_y_render(const std::string& title, int width, int height) {
    this->window = std::make_unique<SDL2pp::Window>(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    this->render = std::make_unique<SDL2pp::Renderer>(*window, -1, SDL_RENDERER_ACCELERATED);
}

void Renderizado::crear_reproductor_audio() {
    this->reproductor_audio = std::make_unique<SDL2pp::Mixer>(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    int numChannels = 16; 
    Mix_AllocateChannels(numChannels);
}

void Renderizado::mostrar_tablero_final() {
    render->Clear();
    mapa->dibujar_fondo_final(*render);    
    interfaz->mostrar_tabla_final(*render);
    render->Present();
    SDL_Delay(3000); // Muestro la tabla final por 3 segundos
}

Renderizado::~Renderizado() { 

}
