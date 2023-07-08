// Nome: digital.cpp
// Descrição: Arquivo de implementação da classe Digital, que implementa as funções digitais do ESP8266.

// Inclui bibliotecas necessárias.
#include "constants.h"
#include "digital.h"
#include <stdio.h>

int Digital::digitalRead(gpio_num_t pino)
{
  // Retorna o valor lido do pino.
  return gpio_get_level(pino);
}

void Digital::pinMode(gpio_num_t pino, int config)
{
  // Configura o pino como entrada ou saída.
  unsigned char c = config & 1;

  // Se for entrada, configura o pino como entrada. Se não, configura como saída.
  if (c == INPUT)
    gpio_set_direction(pino, GPIO_MODE_INPUT);
  else
    gpio_set_direction(pino, GPIO_MODE_OUTPUT);

  // Se for pullup, configura o pino como pullup.
  if (config & 2)
  {
    // Configura o pino como pullup. Ou seja, se não houver nada conectado ao pino, o valor lido será 1.
    gpio_set_pull_mode(pino, GPIO_PULLUP_ONLY);
  }
}

void Digital::digitalWrite(gpio_num_t pino, int valor)
{
  // Escreve o valor no pino.
  gpio_set_level(pino, valor);
}

// Instancia um objeto da classe Digital.
Digital digital = Digital();
