// Declaração de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"



QueueHandle_t dados_dfila; // Fila para o estado do botão
QueueHandle_t acao_botao; // Fila para o estado do LED

int estado_led = 0; // Variável para simular o LED

// Tarefa que simula a leitura do Botão
void vLeitura_botao() {


    
    int dados_botao = 0;

    for(;;) {

        dados_botao = rand() % 2; // Simula o estado do botão 0 - solto e 1 - pressionado

        xQueueSend(dados_dfila, &dados_botao, portMAX_DELAY); // Envia dados para a fila

        vTaskDelay(100 / portTICK_PERIOD_MS); // Executa a cada 100ms
    }

}



// Tarefa para o processamento do estado do botão
void vProcessamento_tarefa() {

    int dados = 0; // variável para receber os dados vindo de vLeitura_botao
    int comando_led = 0; // Somente para ligar o LED

    for(;;) {

        // Verificação se a operação de receber dados foi bem-sucedida
        if(xQueueReceive(dados_dfila, &dados, portMAX_DELAY) == pdTRUE) {
            // se dados == 1 o comando é passado para a Tarefa 3(Acionar o LED)
            if(dados == 1) {
                comando_led = 1;
                xQueueSend(acao_botao, &comando_led, portMAX_DELAY);
            } else { // se não, aguarda o próximo ciclo de leitura
                comando_led = 0; // atualiza o comando para 0 - OFF
            }
            
        }
    }
}


// Tarefa para o controle do LED
void vAcionarTarefa() {
    
    int comando; // Variável para receber o comando vindo de vProcessamento_tarefa

    for(;;) {

        // Verificação se a operação de receber dados foi bem-sucedida
        if(xQueueReceive(acao_botao, &comando, portMAX_DELAY) == pdTRUE) {
            estado_led = comando;
            // se o comando for == 1 o LED é aceso
            if(estado_led == 1) {
                printf("LED ON\n");

                vTaskDelay(500 / portTICK_PERIOD_MS); // delay de 500ms

                // atualiza o estado do LED para 0 - OFF
                estado_led = 0;

                printf("LED OFF\n");

            }
        } 
    }
}

int main()
{
    stdio_init_all(); // inicialização de saída padrão 
    srand(time(NULL)); // Semente do gerador de números aleátorios

    // Criar Filas
    dados_dfila = xQueueCreate(2, sizeof(int));
    acao_botao = xQueueCreate(1, sizeof(int));

    if(dados_dfila != NULL) {
        // criar tarefas
        xTaskCreate(vLeitura_botao, "Leitura do Botao", 128, NULL, 1, NULL);
        xTaskCreate(vProcessamento_tarefa, "Processamento da tarefa 1", 128, NULL, 1, NULL);
        xTaskCreate(vAcionarTarefa, "Acionamento do LED", configMINIMAL_STACK_SIZE * 4, NULL, 1, NULL);

        // inicializa o escalonador
        vTaskStartScheduler();
    }


    while (true)
        ;

    return 0;
}
