// O arquivo constants.h contém constantes que são usadas em todo o projeto.

// Proteção contra inclusões múltiplas.
#ifndef __CONSTANTS__
#define __CONSTANTS__

#define SERIAL_RATE 74880 // Define a taxa de transmissão serial.

// Define o comprimento máximo do nome, endereço, telefone e memória do registro.
#define MAX_NAME_LENGTH 20
#define MAX_ADDRESS_LENGTH 30
#define MAX_PHONE_LENGTH 14
#define MAX_MEM_LENGTH 1024

// Define o menu principal e as opções do menu.
#define TXT_MENU "\n*******MENU*******\n"
#define TXT_LIST_ALL "[%d] - Lista todos os registros\n"
#define TXT_INSERT_REGISTER "[%d] - Inserir registro\n"
#define TXT_GET_REGISTER_BY_NAME "[%d] - pesquisa registro por nome\n"
#define TXT_GET_REGISTER_BY_PHONE "[%d] - pesquisa registro por telefone\n"
#define TXT_DELETE_REGISTER_BY_PHONE "[%d] - remove registro baseado no telefone\n"
#define TXT_COUNT_REGISTERS "[%d] - mostra a quantidade de registros atualmente armazenados\n"
#define TXT_START_DB "[%d] - Inicializa o banco de dados (todas as informacoes armazenadas serao perdidas)\n"

// Define as mensagens que pedem informações do usuário.
#define TXT_ENTER_NAME "Entre com o nome: \n"
#define TXT_ENTER_ADDRESS "Entre com o endereco: \n"
#define TXT_ENTER_PHONE "Entre com o telefone: \n"

// Define a mensagem que informa o envio de informações.
#define TXT_INFORMATION_SENT "Valor lido: %s\n"

// Define a mensagem de opção inválida.
#define TXT_INVALID_OPTION "[%d] - Opcao invalida. Retornando ao menu.\n"

// Define as opções do menu em forma de string.
#define OPTION_LIST_ALL 1
#define OPTION_INSERT_REGISTER 2
#define OPTION_GET_REGISTER_BY_NAME 3
#define OPTION_GET_REGISTER_BY_PHONE 4
#define OPTION_DELETE_REGISTER_BY_PHONE 5
#define OPTION_COUNT_REGISTERS 6
#define OPTION_START_DB 7

// Define entradas e saídas.
#define INPUT 1
#define OUTPUT 0
#define PULLUP 2
#define HIGH 1
#define LOW 0

// Define os pinos do ESP8266.
#define PIN0 GPIO_NUM_0
#define PIN1 GPIO_NUM_1
#define PIN2 GPIO_NUM_2
#define PIN3 GPIO_NUM_3
#define PIN4 GPIO_NUM_4
#define PIN5 GPIO_NUM_5
#define PIN6 GPIO_NUM_6
#define PIN7 GPIO_NUM_7
#define PIN8 GPIO_NUM_8
#define PIN9 GPIO_NUM_9
#define PIN10 GPIO_NUM_10
#define PIN11 GPIO_NUM_11
#define PIN12 GPIO_NUM_12
#define PIN13 GPIO_NUM_13
#define PIN14 GPIO_NUM_14
#define PIN15 GPIO_NUM_15
#define PIN16 GPIO_NUM_16

#endif // Fim do arquivo constants.h.
