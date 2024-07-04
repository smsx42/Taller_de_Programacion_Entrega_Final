#include "lobbyProtocolo.h"
#include <sys/socket.h>

static const int MAX_NAME = 256;


LobbyProtocolo::LobbyProtocolo(Socket *skt) 
                : skt(skt){

}

uint8_t LobbyProtocolo::serializar_creacion_partida(uint8_t max_jugadores, std::string mapa){
    bool was_closed = false;
    uint8_t accion = CREAR;
    uint8_t confirmacion;
    skt->sendall(&accion,sizeof(accion),&was_closed);
    skt->sendall(&max_jugadores,sizeof(max_jugadores),&was_closed);
    // Envio mapa
    serializar_mapa(mapa);
    skt->recvall(&confirmacion,sizeof(confirmacion), &was_closed);
    return confirmacion;
}


uint8_t LobbyProtocolo::serializar_unirse_partida(uint32_t codigo_partida, std::string &mapa){
    bool was_closed = false;
    uint8_t accion = UNIRSE;
    uint8_t confirmacion;
    codigo_partida = htonl(codigo_partida);
    skt->sendall(&accion,sizeof(accion),&was_closed);
    skt->sendall(&codigo_partida,sizeof(codigo_partida),&was_closed);
    // Recibo mapa
    mapa = deserializar_mapa();
    skt->recvall(&confirmacion,sizeof(confirmacion), &was_closed);
    
    return confirmacion;
}


static std::vector<uint8_t> stringToUint8Vector(const std::string& str)
{
    std::vector<uint8_t> result;

    for (char ch : str) {
        result.push_back(static_cast<uint8_t>(ch));
    }

    return result;
}

void LobbyProtocolo::serializar_personaje(uint8_t personaje){
    bool was_closed = false;
    skt->sendall(&personaje,sizeof(personaje),&was_closed);
}

void LobbyProtocolo::serializar_mapa(std::string nombre_mapa) {
    std::vector<uint8_t> bytes = stringToUint8Vector(nombre_mapa);
    bytes.push_back(0x00); // Final del nombre
    bool was_closed = false;
    skt->sendall(bytes.data(), bytes.size() * sizeof(uint8_t), &was_closed);
}

static std::string uint8VectorToString(const std::vector<uint8_t>& bytes)
{
    // Utilizar el constructor del string que toma iteradores
    return std::string(bytes.begin(), bytes.end());
}

std::string LobbyProtocolo::deserializar_mapa() {
    bool was_closed = false;
    std::vector<uint8_t> bytes_nombre;
    for(size_t i = 0; i < MAX_NAME; i++) {
        uint8_t byte;
        skt->recvall(&byte, sizeof(uint8_t), &was_closed);
        if (byte == 0x00) {
            break;
        }
        bytes_nombre.push_back(byte);
    }
    return uint8VectorToString(bytes_nombre);
}

std::vector<InfoPartida> LobbyProtocolo::obtener_partidas(){
    bool was_closed = false;
    uint8_t accion = LIST_P;
    std::vector<InfoPartida> info_partidas;
    InfoPartida info_partida;

    skt->sendall(&accion,sizeof(accion),&was_closed);
    uint32_t cantidad_partidas;
    skt->recvall(&cantidad_partidas, sizeof(uint32_t), &was_closed); // Recibir tamaño de partidas
    cantidad_partidas = ntohl(cantidad_partidas); // Convertir a host byte order
    
    
    for(int i = 0; i < cantidad_partidas; i++){

        skt->recvall(&info_partida, sizeof(info_partida), &was_closed);
        info_partida.id_partida = ntohl(info_partida.id_partida);
        info_partida.id_creador = ntohl(info_partida.id_creador);
        info_partidas.emplace_back(info_partida);
    }
    

    return info_partidas;
}

LobbyProtocolo::~LobbyProtocolo(){
    
}

