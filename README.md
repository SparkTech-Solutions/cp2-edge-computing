# Projeto Vinheria Agnello

## Descrição: 
O projeto Vinheria Agnello é um sistema de monitoramento e controle das condições de armazenamento em uma vinícola. Utilizando diversos componentes eletrônicos, o sistema realiza leituras de umidade, temperatura e luminosidade, alertando sobre condições inadequadas por meio de um Display onde imprime informações e simbolos, LEDs indicadores e um buzzer.

## Componentes Ultilizados:
- 01 Arduino UNO R3
- 01 Display 
- 01 LDR
- 01 DHT22
- 01 Buzzer
- 01 Resistor
- 03 LEDs

## Funcionalidades:
O arduino usa o **DHT22** para verificar a temperatura e a humidade e usa uma media de 10 valores recebidos para mostrar na tela, mostrando o estado atual (Boa, Media, Ruim) e o próprio valor. Enquanto os valores estão sendo apresentados o arduino acende **LEDs** (Verde, Amarelo e Vermelho), se o valor estiver fora do ideal (Temperatura boa: entre 10 e 15 celsius; Humidade Boa: Entre 50% e 70%), o arduino acende o LED amarelo e vermelho para valores muito baixos e muito altos, respectivamente, além de ligar o buzzer até os valores entrarem nos valores desejados.
O arduino também usa o Sensor **(LDR)** Fotoresistor para medir os valores em **LUX** e passa esse valor por um **map** para transformá-lo em uma intensidade em porcentagem. O arduino utiliza do mesmo meio que o DHT22 é medido e testado para verificar o LDR, acendendo LEDs e um buzzer.
Após o arduino apresentar os valores 10 vezes ele tira uma média dos 3 valores separadamente e apresenta as 3 ao mesmo tempo, após 6 segundos o programa volta do inicio e começa a apresentar os valores novamente.

## Imagem no WOKWI:
![SparkTechSolutions](https://github.com/SparkTech-Solutions/cp2-edge-computing/assets/162123528/c9b79bf7-f4b5-4bc8-9685-4a53f3137519)

## Instalação
Para usar o sistema, monte o circuito conforme descrito no [vídeo explicativo](). Além disso, você pode visualizar e editar o circuito no [WOKWI](https://wokwi.com/projects/395465873703742465)

## Dificuldades Encontradas:
Encontramos alguns desafios ao lidar com caracteres especiais, uma novidade para nós. Além disso, dedicamos um tempo considerável para a criação da animação da logo. O buzzer não estava permanecendo ligado continuamente, e também enfrentamos dificuldades ao montar o Arduino, já que algumas peças, como o display, eram novas para nós. A transição de sites também representou um obstáculo, uma vez que estávamos habituados ao Tinkercad e mudamos para o Wokwi.
