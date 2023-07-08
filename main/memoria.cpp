// Nome: memoria.cpp
// Descrição: Implementação dos métodos da classe Memoria.

// Inclui as bibliotecas necessárias.
#include <stdio.h>

#include "memoria.h"
#include "i2c.h"
#include "digital.h"
#include "db.h"

Memoria::Memoria(void)
{
	// Instancia um objeto da classe I2C.
	protocolo_I2C = I2C();
}

void Memoria::testa_eeprom_disponivel(void)
{
	// Endereço do dispositivo.
	// O endereço é composto por 7 bits, sendo que o bit menos significativo é o bit R/W.
	uint8_t dev = 0x50 | dispositivoAlvo;

	// Para testar se a EEPROM está disponível, tenta-se escrever um byte no dispositivo.
	for (;;)
	{
		protocolo_I2C.start();
		int ack = protocolo_I2C.write((dev << 1));
		if (ack == 0)
			return;
	}
}

void Memoria::init(uint8_t device)
{
	dispositivoAlvo = device;

	// Configura os pinos de comunicação I2C. O pino 16 é o SDA e o pino 5 é o SCL.
	protocolo_I2C.configura(PIN16, PIN5);
}

void Memoria::escreve(uint16_t end, uint8_t b[], uint16_t tam)
{
	// Endereço do dispositivo.
	uint8_t dev = 0x50 | dispositivoAlvo;

	// Endereço atual.
	uint16_t endAtual = end;

	// Para escrever na EEPROM, é necessário enviar o endereço de memória, o byte a ser escrito e o endereço do dispositivo.
	for (int a = 0; a < tam; a++)
	{
		testa_eeprom_disponivel();
		protocolo_I2C.start();				 // Inicia a comunicação I2C.
		protocolo_I2C.write((dev << 1) | 0); // Envia o endereço do dispositivo e o bit R/W.
		protocolo_I2C.write(endAtual >> 8);	 // Envia o endereço de memória.
		protocolo_I2C.write(endAtual);		 // Envia o endereço de memória.
		protocolo_I2C.write(b[a]);			 // Envia o byte a ser escrito.
		protocolo_I2C.stop();				 // Finaliza a comunicação I2C.
		endAtual++;							 // Incrementa o endereço atual.
	}
}

void Memoria::le(uint16_t end, uint8_t b[], uint16_t tam)
{
	// Endereço do dispositivo.
	uint8_t dev = 0x50 | dispositivoAlvo;

	// Endereço atual.
	uint16_t endAtual = end;

	testa_eeprom_disponivel();

	// Para ler da EEPROM, é necessário enviar o endereço de memória e o endereço do dispositivo.
	for (int a = 0; a < tam; a++)
	{
		protocolo_I2C.start();				 // Inicia a comunicação I2C.
		protocolo_I2C.write((dev << 1) | 0); // Envia o endereço do dispositivo e o bit R/W.
		protocolo_I2C.write(endAtual >> 8);	 // Envia o endereço de memória.
		protocolo_I2C.write(endAtual);		 // Envia o endereço de memória.
		protocolo_I2C.start();				 // Inicia a comunicação I2C.
		protocolo_I2C.write((dev << 1) | 1); // Envia o endereço do dispositivo e o bit R/W.
		b[a] = protocolo_I2C.read();		 // Lê o byte.
		protocolo_I2C.stop();				 // Finaliza a comunicação I2C.
		endAtual++;							 // Incrementa o endereço atual.
	}
}

// Instancia um objeto da classe Memoria.
Memoria MEMORIA = Memoria();
