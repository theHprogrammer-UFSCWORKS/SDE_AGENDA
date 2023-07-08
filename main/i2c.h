// Nome: i2c.h
// Descrição: Arquivo de cabeçalho da classe I2C, que implementa o protocolo I2C
// Sobre o protocolo I2C:
// O protocolo I2C é um protocolo de comunicação serial síncrono, que utiliza apenas dois fios para a comunicação,
// um para o clock e outro para os dados. O protocolo é bidirecional, ou seja, os dados podem ser enviados e recebidos
// pelo mesmo fio. O protocolo é baseado em um mestre e um ou mais escravos, sendo que o mestre é quem controla o clock
// e inicia a comunicação. O protocolo é baseado em um endereçamento de 7 bits, sendo que o bit mais significativo é
// reservado para indicar se a comunicação é de leitura ou escrita. O protocolo é baseado em um handshake, onde o
// escravo envia um ACK (acknowledge) para indicar que recebeu o dado. O protocolo é baseado em um bit de parada, que
// indica o fim da comunicação. O protocolo é baseado em um bit de repetição, que indica que o mestre deseja continuar
// a comunicação. O protocolo é baseado em um bit de espera, que indica que o escravo não está pronto para receber o
// dado.
//

#ifndef __I2C_SOFTWARE_
#define __I2C_SOFTWARE_

// Inclui as bibliotecas necessárias.
#include <inttypes.h>
#include "driver/gpio.h"

class I2C
{
public:
  /**
   * @brief Configura o pino de dados e o pino de clock.
   * @param pino_dados Pino de dados.
   * @param pino_clk Pino de clock.
   * @return void.
   */
  void configura(gpio_num_t pino_dados, gpio_num_t pino_clk);

  /**
   * @brief Inicia a comunicação I2C.
   * @return void.
   */
  void start(void);

  /**
   * @brief Finaliza a comunicação I2C.
   * @return void.
   */
  void stop(void);

  /**
   * @brief Escreve um byte na comunicação I2C.
   * @param valor_byte Valor do byte a ser escrito.
   * @return uint8_t ACK.
   */
  uint8_t write(uint8_t valor_byte);

  /**
   * @brief Lê um byte da comunicação I2C.
   * @return uint8_t Byte lido.
   */
  uint8_t read(void);

private:
  /**
   * @brief Pino de dados. Será configurado como saída para escrita.
   * @return void.
   */
  void dados_baixo(void);

  /**
   * @brief Pino de dados. Será configurado como entrada para leitura.
   * @return void.
   */
  void dados_alto(void);

  /*
   * @brief Pino de clock. INPUT (1).
   * @return void.
   */
  void clk_alto(void);

  /*
   * @brief Pino de clock. OUTPUT (0).
   * @return void.
   */
  void clk_baixo(void);

  /**
   * @brief Verifica se o o valor do bit é 1 ou 0.
   * Se for 1, retorna o dados_alto, se for 0, retorna dados_baixo.
   * Dessa forma, o pino de dados é configurado como saída para escrita.
   * @param valor_bit Valor do bit a ser escrito.
   * @return void.
   */
  void bit(uint8_t valor_bit);

  /**
   * @brief Lê o valor do bit.
   * @return uint8_t Valor do bit.
   */
  uint8_t le_bit(void);

  /**
   * @brief Envia um ACK para o mestre.
   * @param v Valor do ACK.
   * @return uint8_t ACK.
   */
  uint8_t read_ACK(uint8_t v);
};

#endif