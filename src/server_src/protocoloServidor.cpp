#include "protocoloServidor.h"

#include <map>
#include <utility>

#include "sys/socket.h"

static const int MAX_NAME = 256;

ProtocoloServidor::ProtocoloServidor(Socket skt): skt_jugador(std::move(skt)) {}

uint8_t ProtocoloServidor::leer_jugadores(bool& was_closed) {
    uint8_t max_jugadores;
    skt_jugador.recvall(&max_jugadores, sizeof(max_jugadores), &was_closed);
    return max_jugadores;
}

static std::vector<uint8_t> stringToUint8Vector(const std::string& str)
{
    std::vector<uint8_t> result;

    for (char ch : str) {
        result.push_back(static_cast<uint8_t>(ch));
    }

    return result;
}

void ProtocoloServidor::enviar_mapa(std::string nombre_mapa, bool& was_closed) {
    std::vector<uint8_t> bytes = stringToUint8Vector(nombre_mapa);
    bytes.push_back(0x00); // Final del nombre
    skt_jugador.sendall(bytes.data(), bytes.size() * sizeof(uint8_t), &was_closed);
}


uint32_t ProtocoloServidor::leer_id_partida(bool& was_closed) {
    uint32_t id_partida;
    skt_jugador.recvall(&id_partida, sizeof(id_partida), &was_closed);
    id_partida = ntohl(id_partida);
    return id_partida;
}

static std::string uint8VectorToString(const std::vector<uint8_t>& bytes)
{
    // Utilizar el constructor del string que toma iteradores
    return std::string(bytes.begin(), bytes.end());
}

std::string ProtocoloServidor::leer_mapa(bool& was_closed) {
    std::vector<uint8_t> bytes_nombre;
    for(size_t i = 0; i < MAX_NAME; i++) {
        uint8_t byte;
        skt_jugador.recvall(&byte, sizeof(uint8_t), &was_closed);
        if (was_closed) {
            throw std::runtime_error("Se perdió la conexion con el cliente");
        }
        if (byte == 0x00) {
            break;
        }
        bytes_nombre.push_back(byte);
    }
    return uint8VectorToString(bytes_nombre);
};


uint8_t ProtocoloServidor::obtener_accion(bool& was_closed) {
    uint8_t codigo;
    skt_jugador.recvall(&codigo, sizeof(codigo), &was_closed);

    if (was_closed) {
        throw std::runtime_error("Se perdió la conexion con el cliente");
    }

    return codigo;
}


void ProtocoloServidor::enviar_confirmacion(uint8_t codigo, bool& was_closed) {
    skt_jugador.sendall(&codigo, sizeof(codigo), &was_closed);
}

void ProtocoloServidor::enviar_id_jugador(uint32_t id, bool& was_closed) {
    id = htonl(id);
    skt_jugador.sendall(&id, sizeof(id), &was_closed);
}


void ProtocoloServidor::enviar_evento(bool& was_closed, Evento evento) {
    uint8_t cant_personajes = (uint8_t)evento.eventos_personaje.size();
    skt_jugador.sendall(&cant_personajes, sizeof(cant_personajes), &was_closed);

    uint16_t tiempo = (uint16_t)evento.tiempo_restante;
    uint16_t tiempo_convertido = htons(tiempo);
    skt_jugador.sendall(&tiempo_convertido, sizeof(uint16_t), &was_closed);

    for (EventoPersonaje p: evento.eventos_personaje) {
        p.id_jugador = htonl(p.id_jugador);
        p.posicion_x = htonl(p.posicion_x);
        p.posicion_y = htonl(p.posicion_y);
        p.puntos = htonl(p.puntos);
        p.municion = htonl(p.municion);
        skt_jugador.sendall(&p, sizeof(p), &was_closed);
        if (was_closed) {
            throw std::runtime_error("Error, se cerro la conexion con el servidor");
        }
    }


    uint32_t cant_balas = (uint32_t)evento.eventos_bala.size();
    cant_balas = htonl(cant_balas);
    skt_jugador.sendall(&cant_balas, sizeof(cant_balas), &was_closed);

    for (EventoBala b: evento.eventos_bala) {
        b.id_jugador = htonl(b.id_jugador);
        b.id_bala = htonl(b.id_bala);
        b.posicion_x = htonl(b.posicion_x);
        b.posicion_y = htonl(b.posicion_y);
        skt_jugador.sendall(&b, sizeof(b), &was_closed);
        if (was_closed) {
            throw std::runtime_error("Error, se cerro la conexion con el servidor");
        }
    }


    uint32_t cant_objetos = (uint32_t)evento.eventos_objeto.size();
    cant_objetos = htonl(cant_objetos);
    skt_jugador.sendall(&cant_objetos, sizeof(cant_objetos), &was_closed);

    for (EventoObjeto o: evento.eventos_objeto) {
        o.id_objeto = htonl(o.id_objeto);
        o.posicion_x = htonl(o.posicion_x);
        o.posicion_y = htonl(o.posicion_y);
        skt_jugador.sendall(&o, sizeof(o), &was_closed);
        if (was_closed) {
            throw std::runtime_error("Error, se cerro la conexion con el servidor");
        }
    }

    uint32_t cant_enemigos = (uint32_t)evento.eventos_enemigos.size();
    cant_enemigos = htonl(cant_enemigos);
    skt_jugador.sendall(&cant_enemigos, sizeof(uint32_t), &was_closed);

    for (EventoEnemigo e: evento.eventos_enemigos) {
        e.id_enemigo = htonl(e.id_enemigo);
        e.posicion_x = htonl(e.posicion_x);
        e.posicion_y = htonl(e.posicion_y);
        skt_jugador.sendall(&e, sizeof(e), &was_closed);
        if (was_closed) {
            throw std::runtime_error("Error, se cerro la conexion con el servidor");
        }
    }
}

void ProtocoloServidor::enviar_tipo_entidad(const std::string& entity_type, bool& was_closed) {
    uint8_t entity_code;
    if (entity_type == "piso") {
        entity_code = PISO;
    } else if (entity_type == "pared") {
        entity_code = PARED;
    } else {
        return;  // Si el tipo de entidad no es reconocido, no hacer nada
    }
    skt_jugador.sendall(&entity_code, sizeof(entity_code), &was_closed);
}

void ProtocoloServidor::enviar_posiciones_entidad(const std::vector<Position>& positions,
                                                  bool& was_closed) {
    uint32_t largo = positions.size();
    largo = htonl(largo);
    skt_jugador.sendall(&largo, sizeof(largo), &was_closed);

    for (const auto& pos: positions) {
        skt_jugador.sendall(&pos, sizeof(pos), &was_closed);
    }
}

void ProtocoloServidor::enviar_lista_partidas(MonitorPartidas& monitor_partidas, bool& was_closed) {

    InfoPartida info_partida;
    const std::map<uint32_t, Partida*>* partidas = monitor_partidas.obtener_partidas();
    uint32_t cantidad_partidas =
            htonl(static_cast<uint32_t>(partidas->size()));  // Convertir a network byte order
    skt_jugador.sendall(&cantidad_partidas, sizeof(uint32_t),
                        &was_closed);  // Enviar tamaño de partidas


    for (auto it = partidas->begin(); it != partidas->end(); ++it) {

        info_partida.id_partida = htonl(it->first);
        info_partida.id_creador = htonl(it->second->creador());
        info_partida.jugadores = it->second->jugadores();
        info_partida.max_jugadores = it->second->max();
        skt_jugador.sendall(&info_partida, sizeof(info_partida), &was_closed);
    }
}

void ProtocoloServidor::close() {
    skt_jugador.shutdown(SHUT_RDWR);
    skt_jugador.close();
}

ProtocoloServidor::~ProtocoloServidor() {}
