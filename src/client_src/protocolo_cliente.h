#ifndef PROTOCOLO_CLIENTE_H
#define PROTOCOLO_CLIENTE_H

#include <string>
#include "../common_src/socket.h"
#include "../common_src/accion.h"
#include "../common_src/evento.h"

/**
 * TDA ProtocoloCliente.
 *
 * Su funcion es enviar/recibir acciones/eventos del servidor.
 */
class ProtocoloCliente {
private:
    Socket& skt;     // Socket por el cual se comunicaran el cliente/servidor

public:

    void recibir_entidad(uint32_t cantidad_piezas, MapaEntidades& map);

    void recibir_posiciones(uint32_t cantidad_tipo, std::vector<Position>& posiciones, bool& was_closed);

    std::string determinar_tipo(uint8_t tipo);
    /**
     * Construyo el protocolo en funcion del socket al cual quieren
     * comunicarse.
     *
     * @param skt Referencia al socket donde se comunicaran tanto cliente como servidor.
     */
    explicit ProtocoloCliente(Socket& skt);

    //Evento deserializar(uint8_t byte);


    /**
     * Serializa y envia la accion del juego al servidor.
     *
     * @param accion Referencia de la accion a enviar.
     * @return false en caso de no poder enviar, true caso contrario.
     */
    bool enviar_accion_juego(uint8_t accion_juego);

    /**
     * Deserializa y recibe el evento del servidor.
     *
     * @param evento Referencia del evento a msg.
     * @return false en caso de no poder recibir, true caso contrario.
     */
    bool recibir_evento(Evento &evento);

    MapaEntidades recibir_mapa();

    /**
     * Desabilito las copias
     */
    ProtocoloCliente(const ProtocoloCliente&) = delete;
    ProtocoloCliente& operator=(const ProtocoloCliente&) = delete;

    /**
     * Permito el movimiento de objetos
     */
    ProtocoloCliente(ProtocoloCliente&&) = default;
    ProtocoloCliente& operator=(ProtocoloCliente&&) = default;
};

#endif
