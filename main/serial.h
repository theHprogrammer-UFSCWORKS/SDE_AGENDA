// Nome: serial.h
// Descrição: Biblioteca para comunicação serial.

#ifndef __SERIAL__
#define __SERIAL__

// Inclui as bibliotecas necessárias.
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/uart.h"

class Serial
{
public:
  /**
   * @brief Inicializa a comunicação serial.
   * @param v velocidade de transmissão em baud
   * @return void
   */
  void begin(int v);

  /**
   * @brief Faz a leitura de uma string.
   * @param buf ponteiro para o buffer de dados
   * @param length tamanho do buffer de dados
   * @return int: número de bytes lidos
   */
  void readString(uint8_t *buf, uint32_t length);

  /**
   * @brief Faz a leitura de um caractere.
   * @return int: caractere lido
   */
  int readChar(void);

  /**
   * @brief Faz a leitura de um inteiro.
   * @return int: inteiro lido
   */
  int readInteger(void);
};

// Instancia um objeto da classe Serial.
extern Serial serial;
#endif