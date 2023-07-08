// Nome: i2c.cpp
// Descrição: Arquivo de implementação da classe I2C, que implementa o protocolo I2C

#include "i2c.h"
#include "digital.h"
#include <stdio.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "digital.h"
#include "delay.h"
#include "constants.h"

gpio_num_t PIN_DADOS;
gpio_num_t PIN_CLK;

void I2C::dados_baixo(void)
{
  digital.pinMode(PIN_DADOS, OUTPUT);   // configura como saída.
  digital.digitalWrite(PIN_DADOS, LOW); // escreve o valor do bit (0).
}

void I2C::dados_alto(void)
{
  digital.pinMode(PIN_DADOS, INPUT); // configura como entrada.
}

// Define o pino de clock como entrada
void I2C::clk_alto(void)
{
  digital.pinMode(PIN_CLK, INPUT); // configura como entrada.
}

void I2C::clk_baixo(void)
{
  digital.pinMode(PIN_CLK, OUTPUT);   // configura como saída.
  digital.digitalWrite(PIN_CLK, LOW); // escreve o valor do bit (0).
}

void I2C::configura(gpio_num_t pino_dados, gpio_num_t pino_clk)
{

  /**
   * @param pino_dados Pino de dados.
   * @param pino_clk Pino de clock.
   */
  PIN_DADOS = pino_dados;
  PIN_CLK = pino_clk;

  // Configura os pinos de dados e de clock.
  clk_alto();
  dados_alto();
  delay_ms(1);
}

void I2C::start(void)
{
  clk_alto();
  delay_us(10);
  dados_alto();
  delay_us(10);
  dados_baixo();
  delay_us(10);
  clk_baixo();
  delay_us(10);
}

void I2C::bit(uint8_t valor_bit)
{
  // Se o valor do bit for 1, escreve 1 no pino de dados.
  if (valor_bit)
  {
    dados_alto();
  }
  // Se o valor do bit for 0, escreve 0 no pino de dados.
  else
  {
    dados_baixo();
  }
  delay_us(10);
  clk_alto();
  delay_us(10);
  clk_baixo();
  dados_alto();
}

uint8_t I2C::le_bit(void)
{
  /**
   * @param valor Valor do bit lido.
   */
  uint8_t valor;

  dados_alto();
  delay_us(10);
  clk_alto();
  valor = digital.digitalRead(PIN_DADOS);
  delay_us(10);
  clk_baixo();
  return valor;
}

uint8_t I2C::write(uint8_t valor_byte)
{
  /**
   * @param a Valor de ACK.
   * @param x Valor de x.
   */
  uint8_t a, x;

  // Para cada bit do byte, escreve o bit no pino de dados.
  for (x = 0; x < 8; x++)
  {
    bit(1 & (valor_byte >> (7 - x)));
  }

  // Lê o ACK.
  a = le_bit();
  delay_us(10);

  // Retorna o valor do ACK.
  return a;
}

uint8_t I2C::read(void)
{
  /**
   * @param valor Valor do byte lido.
   * @param x Valor de x.
   */
  uint8_t valor = 0, x;

  // Para cada bit do byte, lê o bit no pino de dados.
  for (x = 0; x < 8; x++)
  {
    valor = (valor << 1) | le_bit();
  }

  // Retorna o valor do byte lido.
  return valor;
}

uint8_t I2C::read_ACK(uint8_t v)
{
  /**
   * @param valor Valor do byte lido.
   * @param x Valor de x.
   */
  uint8_t valor = 0, x;

  // Para cada bit do byte, o valor do bit lido é deslocado para a esquerda e o bit é lido.
  for (x = 0; x < 8; x++)
  {
    valor = (valor << 1) | le_bit();
  }

  // Escreve o valor do ACK.
  bit(v);

  // Retorna o valor do byte lido.
  return valor;
}

void I2C::stop(void)
{
  dados_baixo();
  delay_us(5);
  clk_baixo();
  delay_us(5);
  clk_alto();
  delay_us(5);
  dados_alto();
  delay_us(5);
}
