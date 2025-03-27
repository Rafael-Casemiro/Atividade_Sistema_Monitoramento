# Sistema_de_Monitoramento
 uma aplicação embarcada no FreeRTOS com 3 tarefas que simulam o monitoramento de um sistema com sensores (como um botão e um LED).
Descrição do Sistema:
Tarefa 1 (Leitura do Botão): Essa tarefa será responsável por simular a leitura de um botão. Ela será executada periodicamente, a cada 100ms, e enviará o estado do botão para a próxima tarefa.
Tarefa 2 (Processamento do Botão): Receberá o estado do botão da Tarefa 1. Caso o botão seja pressionado (simulado com a variável), ela acionará a próxima tarefa (a de controlar o LED). Caso contrário, apenas aguardará o próximo ciclo de leitura.
Tarefa 3 (Controle do LED): Controlará um LED (simulado como uma variável ou saída digital). Se o botão for pressionado, o LED será aceso, caso contrário, será apagado. A tarefa será executada sempre que for acionada pela Tarefa 2.
