// Nome: db.cpp
// Descição: Arquivo de implementação da classe DB

#include <stdio.h>
#include <vector>
#include <string.h>

#include "db.h"
#include "memoria.h"

void DB::createHeader(Header *c)
{
  // Escreve o cabeçalho no endereço 0 da memória.
  MEMORIA.escreve(0, (uint8_t *)c, sizeof(Header));
};

void DB::updateHeader()
{
  /**
   * @param cabecalho_atual Cabeçalho do banco de dados.
   */
  Header cabecalho_atual = readHeader(false);
  cabecalho_atual.size = cabecalho_atual.size + 1;                 // Incrementa o tamanho do banco de dados.
  MEMORIA.escreve(0, (uint8_t *)&cabecalho_atual, sizeof(Header)); // Escreve o cabeçalho no endereço 0 da memória.
};

void DB::deleteHeader()
{
  /**
   * @param cabecalho_atual Cabeçalho do banco de dados.
   */
  Header cabecalho_atual = readHeader(false);
  cabecalho_atual.size = cabecalho_atual.size - 1;                 // Decrementa o tamanho do banco de dados.
  MEMORIA.escreve(0, (uint8_t *)&cabecalho_atual, sizeof(Header)); // Escreve o cabeçalho no endereço 0 da memória.
};

Header DB::readHeader(bool getAll)
{
  /**
   * @param cabecalho_atual Cabeçalho do banco de dados.
   */
  Header cabecalho_atual;
  MEMORIA.le(0, (uint8_t *)&cabecalho_atual, sizeof(Header)); // Lê o cabeçalho no endereço 0 da memória.

  // Se getAll for true, imprime o número de registros ocupados.
  if (getAll)
  {
    printf("Numero de registros atualmente ocupados: %d\n", cabecalho_atual.size);
  }

  // Retorna o cabeçalho.
  return cabecalho_atual;
};

void DB::saveRegister(uint16_t numero_do_registro, Register *R)
{
  /**
   * @param position Posição do registro na memória.
   */
  uint16_t posicao;

  // Se o número do registro for igual ao tamanho máximo do banco de dados, a memória está cheia.
  if (numero_do_registro == globalHeader.maxsize)
  {
    printf("ERRO. MEMORIA CHEIA!!!\n");
  }
  // Se não, escreve o registro na memória e atualiza o cabeçalho.
  // O registro é escrito na posição 4 + (numero_do_registro * tamanho_do_registro).
  else
  {
    posicao = 4 + (numero_do_registro) * sizeof(Register);
    MEMORIA.escreve(posicao, (uint8_t *)R, sizeof(Register));
    updateHeader();
  }
};

void DB::listRegister()
{
  /**
   * @param numero_de_registros Número de registros ocupados.
   */
  Header numero_de_registros = readHeader(true);

  /**
   * @param registro_consultado Registro consultado.
   */
  Register registro_consultado;

  /**
   * @param posicao Posição do registro na memória.
   */
  uint16_t posicao;

  // Imprime todos os registros ocupados.
  for (int i = 0; i < numero_de_registros.size; i++)
  {
    posicao = 4 + (i) * sizeof(Register);                                   // Pega a posição do registro na memória.
    MEMORIA.le(posicao, (uint8_t *)&registro_consultado, sizeof(Register)); // Lê o registro na memória.
    printf("REGISTRO %d :\n Nome: %s\n Endereco: %s\n Telefone:%s\n", i + 1, registro_consultado.name, registro_consultado.address, registro_consultado.phone);
  }
};

void DB::getName(char n[20])
{
  /**
   * @param encontrou Indica se o nome foi encontrado.
   */
  bool encontrou = false;

  /**
   * @param numero_de_registros Número de registros ocupados.
   */
  Header numero_de_registros = readHeader(false);

  /**
   * @param registro_consultado Registro consultado.
   */
  Register registro_consultado;

  /**
   * @param posicao Posição do registro na memória.
   */
  uint16_t posicao;

  // Imprime o registro com o nome consultado.
  for (int i = 0; i < numero_de_registros.size; i++)
  {
    posicao = 4 + (i) * sizeof(Register);                                   // Pega a posição do registro na memória.
    MEMORIA.le(posicao, (uint8_t *)&registro_consultado, sizeof(Register)); // Lê o registro na memória.

    // Se o nome do registro for igual ao nome consultado, imprime o registro.
    if (strcmp(registro_consultado.name, n) == 0)
    {
      printf("REGISTRO %d :\n Nome: %s\n Endereco: %s\n Telefone:%s\n", i + 1, registro_consultado.name, registro_consultado.address, registro_consultado.phone);
      encontrou = true;
    }
  }

  // Se não encontrou o nome, imprime uma mensagem de erro.
  if (!encontrou)
  {
    printf("ERRO!!! Nao existe essa pessoa cadastrada.\n");
  }
};

Register DB::getPhone(char t[14])
{
  /**
   * @param encontrou Indica se o telefone foi encontrado.
   */
  bool encontrou = false;

  /**
   * @param numero_de_registros Número de registros ocupados.
   */
  Header numero_de_registros = readHeader(false);

  /**
   * @param registro_telefone Registro com o telefone consultado.
   */
  Register registro_telefone;

  /**
   * @param registro_consultado Registro consultado.
   */
  Register registro_consultado;

  /**
   * @param posicao Posição do registro na memória.
   */
  uint16_t posicao;

  // Para cada registro ocupado, verifica se o telefone é igual ao telefone consultado.
  for (int i = 0; i < numero_de_registros.size; i++)
  {
    posicao = 4 + (i) * sizeof(Register);                                   // Pega a posição do registro na memória.
    MEMORIA.le(posicao, (uint8_t *)&registro_consultado, sizeof(Register)); // Lê o registro na memória.

    // Se o telefone do registro for igual ao telefone consultado, imprime o registro.
    if (strcmp(registro_consultado.phone, t) == 0)
    {
      encontrou = true;
      registro_telefone = registro_consultado;
      printf("REGISTRO %d :\n Nome: %s\n Endereco: %s\n Telefone:%s\n", i + 1, registro_consultado.name, registro_consultado.address, registro_consultado.phone);
    }
  }

  // Se não encontrou o telefone, imprime uma mensagem de erro.
  if (!encontrou)
  {
    printf("ERRO!!! Nao existe essa pessoa cadastrada.\n");
  }

  // Retorna o registro com o telefone consultado.
  return registro_telefone;
};

void DB::deleteRegister(char t[14])
{
  /**
   * @param removeu Indica se o registro foi removido.
   */
  bool removeu = false;

  /**
   * @param registro_remover Registro a ser removido.
   */
  Register registro_remover;
  registro_remover = getPhone(t);

  /**
   * @param numero_de_registros Número de registros ocupados.
   */
  Header numero_de_registros = readHeader(false);

  /**
   * @param registro_consultado Registro consultado.
   */
  Register registro_consultado;

  /**
   * @param posicao Posição do registro na memória.
   */
  uint16_t posicao;

  // Para cada registro ocupado, verifica se o telefone é igual ao telefone consultado.
  for (int i = 0; i < numero_de_registros.size; i++)
  {
    posicao = 4 + (i) * sizeof(Register);                                   // Pega a posição do registro na memória.
    MEMORIA.le(posicao, (uint8_t *)&registro_consultado, sizeof(Register)); // Lê o registro na memória.

    // Se o telefone do registro for igual ao telefone consultado, remove o registro.
    if (strcmp(registro_consultado.phone, registro_remover.phone) == 0)
    {
      posicao = 4 + (numero_de_registros.size - 1) * sizeof(Register);        // Pega a posição do último registro na memória.
      MEMORIA.le(posicao, (uint8_t *)&registro_consultado, sizeof(Register)); // Lê o último registro na memória.
      saveRegister(i, &registro_consultado);                                  // Salva o último registro na posição do registro a ser removido.
      removeu = true;                                                         // Indica que o registro foi removido.
      deleteHeader();                                                         // Diminui o número de registros ocupados.
      deleteHeader();                                                         // Diminui o número de registros ocupados.
      break;
    }
  }

  // Se não encontrou o telefone, imprime uma mensagem de erro.
  if (!removeu)
  {
    printf("ERRO!!! Nao existe essa pessoa cadastrada.\n");
  }
};

Header globalHeader{0, MAX_MEM_LENGTH - 1};