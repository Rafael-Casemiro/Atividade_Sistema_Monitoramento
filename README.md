# Sistema_de_Monitoramento

Este projeto é uma aplicação embarcada utilizando **FreeRTOS**, composta por três tarefas que simulam o monitoramento de um sistema com sensores simples, como um botão e um LED.

## Descrição do Sistema

O sistema é composto por três tarefas principais:

### 🟢 Tarefa 1 - Leitura do Botão

- Responsável por simular a leitura do estado de um botão.
- Executada periodicamente a cada **100ms**.
- Envia o estado atual do botão para a **Tarefa 2** (Processamento).

### ⚙️ Tarefa 2 - Processamento do Botão

- Recebe o estado do botão enviado pela Tarefa 1.
- Se o botão estiver pressionado (simulado por uma variável), aciona a **Tarefa 3** (Controle do LED).
- Caso contrário, apenas aguarda o próximo estado.

### 💡 Tarefa 3 - Controle do LED

- Responsável por simular o controle de um LED (pode ser uma variável ou uma saída digital).
- Se o botão estiver pressionado, o LED é aceso.
- Caso o botão não esteja pressionado, o LED é apagado.
- Esta tarefa é executada **somente quando acionada** pela Tarefa 2.

## Tecnologias Utilizadas

- Linguagem C
- FreeRTOS
- Simulação de hardware (botão e LED como variáveis ou GPIOs)

## Objetivo

O objetivo principal deste projeto é demonstrar o uso de tarefas no FreeRTOS e a comunicação entre elas para simular um sistema de monitoramento embarcado simples.

