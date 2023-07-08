// Nome: memoria.h
// Descrição: Arquivo de cabeçalho da classe Memoria, que implementa as funções de escrita e leitura da EEPROM.

#ifndef __MEMORIA__
#define __MEMORIA__

// Inclui as bibliotecas necessárias.
#include <inttypes.h>

#include "i2c.h"
#include "db.h"

class Memoria
{
public:
	/**
	 * @brief Construtor da classe Memoria.
	 */
	Memoria(void);

	/**
	 * @brief Inicializa a comunicação com a EEPROM.
	 * @param device Endereço do dispositivo.
	 * @return void.
	 */
	void init(uint8_t device);

	/**
	 * @brief Escreve um byte na EEPROM.
	 * @param end Endereço de memória.
	 * @param b Byte a ser escrito.
	 * @param tam Tamanho do vetor de bytes.
	 * @return void.
	 */
	void escreve(uint16_t end, uint8_t b[], uint16_t tam);

	/**
	 * @brief Lê um byte da EEPROM.
	 * @param end Endereço de memória.
	 * @param b Byte a ser lido.
	 * @param tam Tamanho do vetor de bytes.
	 * @return Byte lido.
	 */
	void le(uint16_t end, uint8_t b[], uint16_t tam);

private:
	/**
	 * @param dispositivoAlvo Endereço do dispositivo.
	 */
	uint8_t dispositivoAlvo;

	/**
	 * @brief Testa se a EEPROM está disponível.
	 * @return void.
	 */
	void testa_eeprom_disponivel(void);

	// Instancia um objeto da classe I2C.
	I2C protocolo_I2C;
};

// Instancia um objeto da classe Memoria.
extern Memoria MEMORIA;
#endif