// Nome: app.cpp
// Descrição: Aplicação para o trabalho final.

#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.h"
#include "memoria.h"
#include <inttypes.h>
#include "db.h"
#include "constants.h"

/**
 * @brief Exibe o menu de opções e retorna a opção escolhida.
 * @return int: opção escolhida
 * 1 - Listar todos os registros
 * 2 - Inserir um novo registro
 * 3 - Buscar um registro pelo nome
 * 4 - Buscar um registro pelo telefone
 * 5 - Excluir um registro pelo telefone
 * 6 - Contar o número de registros
 * 7 - Inicializar o banco de dados
 */
int chooseOption(void);

extern "C" void app_main();

/**
 * @brief Função principal do programa. Implementa o menu de opções.
 * @return void
 */
void app_main()
{
	Memoria memoria_i2c = Memoria();
	DB db = DB();

	memoria_i2c.init(0);

	serial.begin(SERIAL_RATE);

	/**
	 * @brief Variáveis auxiliares para a leitura de dados.
	 * @param name: nome do registro a ser buscado
	 * @param phone: telefone do registro a ser buscado
	 */
	char name[MAX_NAME_LENGTH];
	char phone[MAX_PHONE_LENGTH];

	// Coloca o menu de opções em loop
	while (true)
	{
		/**
		 * @brief Variável para armazenar a opção escolhida pelo usuário.
		 * @param option: opção escolhida
		 */
		int option = chooseOption();

		switch (option)
		{
		// Lista todos os registros
		case OPTION_LIST_ALL:
			db.listRegister();
			break;

		// Insere um novo registro
		case OPTION_INSERT_REGISTER:
		{
			/**
			 * @brief Variáveis auxiliares para a leitura de dados.
			 * @param position: posição do registro a ser inserido
			 * @param newRegister: novo registro a ser inserido
			 */
			Header position;
			Register newRegister;

			position = db.readHeader(false);

			printf(TXT_ENTER_NAME);
			serial.readString((uint8_t *)newRegister.name, MAX_NAME_LENGTH);
			printf(TXT_INFORMATION_SENT, newRegister.name);

			printf(TXT_ENTER_ADDRESS);
			serial.readString((uint8_t *)newRegister.address, MAX_ADDRESS_LENGTH);
			printf(TXT_INFORMATION_SENT, newRegister.address);

			printf(TXT_ENTER_PHONE);
			serial.readString((uint8_t *)newRegister.phone, MAX_PHONE_LENGTH);
			printf(TXT_INFORMATION_SENT, newRegister.phone);

			db.saveRegister(position.size, &newRegister);
			break;
		}

		// Busca um registro pelo nome
		case OPTION_GET_REGISTER_BY_NAME:
			printf(TXT_ENTER_NAME);
			serial.readString((uint8_t *)name, MAX_NAME_LENGTH);
			db.getName(name);
			break;

		// Busca um registro pelo telefone
		case OPTION_GET_REGISTER_BY_PHONE:
			printf(TXT_ENTER_PHONE);
			serial.readString((uint8_t *)phone, MAX_PHONE_LENGTH);
			db.getPhone(phone);
			break;

		// Exclui um registro pelo telefone
		case OPTION_DELETE_REGISTER_BY_PHONE:
			printf(TXT_ENTER_PHONE);
			serial.readString((uint8_t *)phone, MAX_PHONE_LENGTH);
			db.deleteRegister(phone);
			break;

		// Conta o número de registros
		case OPTION_COUNT_REGISTERS:
			db.readHeader(true);
			break;

		// Inicializa o banco de dados
		case OPTION_START_DB:
			globalHeader.maxsize = MAX_MEM_LENGTH - 1;
			globalHeader.size = 0x0;
			db.createHeader(&globalHeader);
			break;

		// Opção inválida
		default:
			printf(TXT_INVALID_OPTION, option);
			break;
		}
	}
}

int chooseOption(void)
{
	printf(TXT_MENU);
	printf(TXT_LIST_ALL, OPTION_LIST_ALL);
	printf(TXT_INSERT_REGISTER, OPTION_INSERT_REGISTER);
	printf(TXT_GET_REGISTER_BY_NAME, OPTION_GET_REGISTER_BY_NAME);
	printf(TXT_GET_REGISTER_BY_PHONE, OPTION_GET_REGISTER_BY_PHONE);
	printf(TXT_DELETE_REGISTER_BY_PHONE, OPTION_DELETE_REGISTER_BY_PHONE);
	printf(TXT_COUNT_REGISTERS, OPTION_COUNT_REGISTERS);
	printf(TXT_START_DB, OPTION_START_DB);
	return serial.readInteger();
}