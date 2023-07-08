// Nome: serial.cpp
// Descrição: Implementação dos métodos da classe Serial.

// Inclui as bibliotecas necessárias.
#include "serial.h"

void Serial::begin(int v)
{
	// Configura a comunicação serial.
	uart_config_t uart_config =
		{
			.baud_rate = v,						   // velocidade de transmissão
			.data_bits = UART_DATA_8_BITS,		   // 8 bits de dados
			.parity = UART_PARITY_DISABLE,		   // sem paridade
			.stop_bits = UART_STOP_BITS_1,		   // 1 bit de parada
			.flow_ctrl = UART_HW_FLOWCTRL_DISABLE, // sem controle de fluxo
			.rx_flow_ctrl_thresh = 0,			   // sem controle de fluxo
		};

	// Configura os pinos da comunicação serial.
	uart_param_config(UART_NUM_0, &uart_config);
}
int Serial::readChar(void)
{
	// Variável para armazenar o caractere lido.
	int c = EOF;

	// Enquanto não houver caractere disponível, aguarda.
	while (getchar() != EOF)
	{
		vTaskDelay(pdMS_TO_TICKS(50));
	}

	// Enquanto não houver caractere disponível, aguarda a chegada de um caractere.
	while (c == EOF)
	{
		c = getchar();
	}

	// Retorna o caractere lido.
	return c;
}

void Serial::readString(uint8_t *buf, uint32_t l)
{
	// Variável para armazenar o caractere lido e o número de caracteres lidos.
	int lidos = 0, c;

	// Enquanto os caracteres lidos forem menores que o tamanho do buffer e o
	// caractere lido for diferente de EOF e '\n', armazena o caractere no buffer.
	while (lidos <= l)
	{
		c = getchar();
		if (c != EOF && c != '\n')
		{
			buf[lidos] = c;
			lidos++;
		}
		if (c == '\n' && lidos != 0)
			break;
		vTaskDelay(pdMS_TO_TICKS(50));
	}

	// Adiciona o caractere nulo ao final da string.
	buf[lidos] = 0;
}

int Serial::readInteger()
{
	// Variável para armazenar o número lido e o caractere lido.
	int num = 0, c = EOF;

	// Enquanto o buffer de entrada não estiver vazio, aguarda.
	while (getchar() != EOF)
	{
		vTaskDelay(pdMS_TO_TICKS(50));
	}

	// Enquanto o caractere lido for EOF, aguarda a chegada de um caractere.
	while (c == EOF)
	{
		c = getchar();
	}

	// Enquanto o caractere lido for um dígito, armazena o dígito no número.
	while (c != EOF && c != '\n')
	{
		num = num * 10 + (c - '0');
		c = getchar();
	}

	// Retorna o número lido.
	return num;
}

// Instancia um objeto da classe Serial.
Serial serial = Serial();
