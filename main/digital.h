// Nome: digital.h
// Descrição: Arquivo de cabeçalho da classe Digital, que implementa as funções digitais do ESP8266.

#ifndef __DIGITAL__
#define __DIGITAL__

// Inclui bibliotecas necessárias.
#include "driver/gpio.h"

class Digital
{
public:
  /**
   * @brief Lê o valor de um pino digital.
   * @param pino Pino a ser lido.
   * @return Valor lido.
   */
  int digitalRead(gpio_num_t pino);

  /**
   * @brief Escreve um valor em um pino digital.
   * @param pino Pino a ser escrito.
   * @param valor Valor a ser escrito.
   * @return void.
   */
  void digitalWrite(gpio_num_t pino, int valor);

  /**
   * @brief Configura um pino digital.
   * @param pino Pino a ser configurado.
   * @param config Configuração do pino. (INPUT = 1 ou OUTPUT = 0 ou PULLUP = 2)
   * @return void.
   */
  void pinMode(gpio_num_t pino, int config);
};

// Instancia um objeto da classe Digital.
extern Digital digital;
#endif