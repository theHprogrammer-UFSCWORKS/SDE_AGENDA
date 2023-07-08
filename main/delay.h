// Nome: delay.h
// Descrição: Biblioteca para atrasos.

#ifndef __DELAY__
#define __DELAY__

// Inclui as bibliotecas necessárias.
#include "esp_system.h"

// Define a função de atraso em microsegundos e milissegundos.
#define delay_us(A) ets_delay_us(2 * A)
#define delay_ms(A) vTaskDelay(A / portTICK_RATE_MS)

#endif