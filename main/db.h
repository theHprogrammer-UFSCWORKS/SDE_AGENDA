// Nome: db.h
// Descrição: Arquivo de cabeçalho da classe DB, que implementa as funções de manipulação do banco de dados.

#ifndef __DB__
#define __DB__

// Inclui as bibliotecas necessárias.
#include <inttypes.h>
#include "constants.h"

/*
 * @brief Estrutura do cabeçalho do banco de dados.
 * @param size Tamanho do banco de dados.
 * @param maxsize Tamanho máximo do banco de dados.
 */
typedef struct
{
  uint16_t size;
  uint16_t maxsize;
} Header;

/*
 * @brief Estrutura do registro do banco de dados.
 * @param name Nome do contato.
 * @param address Endereço do contato.
 * @param phone Telefone do contato.
 */
typedef struct
{
  char name[MAX_NAME_LENGTH];
  char address[MAX_ADDRESS_LENGTH];
  char phone[MAX_PHONE_LENGTH];
} Register;

class DB
{
public:
  /**
   * @brief Cria o cabeçalho do banco de dados.
   * @param c Cabeçalho do banco de dados.
   * @return void.
   */
  void createHeader(Header *c);

  /**
   * @brief Atualiza o cabeçalho do banco de dados.
   * @return void.
   */
  void updateHeader();

  /**
   * @brief Deleta o cabeçalho do banco de dados.
   * @return void.
   */
  void deleteHeader();

  /**
   * @brief Lê o cabeçalho do banco de dados.
   * @param getAll Flag para imprimir o registro.
   * @return Cabeçalho do banco de dados.
   */
  Header readHeader(bool getAll);

  /**
   * @brief Salva o registro no banco de dados.
   * @param numero_do_registro Número do registro.
   * @param R Registro.
   * @return void.
   */
  void saveRegister(uint16_t numero_do_registro, Register *R);

  /**
   * @brief Lista os registros do banco de dados.
   * @return void.
   */
  void listRegister();

  /**
   * @brief Compara se o nome do registro é igual ao nome passado e printa o registro.
   * @param n Nome do contato.
   * @return void.
   */
  void getName(char n[20]);

  /**
   * @brief Compara se o telefone do registro é igual ao telefone passado e printa o registro.
   * @param t Telefone do contato.
   * @return void.
   */
  Register getPhone(char t[14]);

  /**
   * @brief Deleta o registro do banco de dados com o telefone passado.
   * @param t Telefone do contato.
   * @return void.
   */
  void deleteRegister(char t[14]);
};

// Header usado para manipular o cabeçalho do banco de dados.
extern Header globalHeader;
#endif