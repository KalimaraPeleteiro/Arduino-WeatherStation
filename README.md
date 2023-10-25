<h1 align = "Center">Estação Meteorológica com Arduino</h1>

Aqui, temos um exemplo de como um dos modelos de Estação Meteorológica vendidos pela AgroConnect seria. Este seria um descritivo do modelo "Agro Duo", capaz de captar 
valores de Umidade e Temperatura. O código está disponível no arquivo `Firmware.ino`. Para esse projeto, são necessários:


- Uma Protoboard
- Um Arduino Modelo "Uno"
- Um Sensor DHTT11 ou DHTT22
- Um Módulo WiFi ESP8266-01 ou um Módulo Ethernet

A princípio, __a estação meteorológica coleta os dados de 8 em 8 horas__ e envia para uma API com uma requisição POST (daí a necessidade de acesso a Internet) com os valores coletados,
que são então adicionados ao banco de dados. Caso a requisição, a medição ou a conexão com a Internet apresentem algum erro, a Estação é Silenciada por uma hora. Caso
o usuário também não tenha cadastrado a Chave da API na plataforma, ativando a estação, a mesma também é silenciada por uma hora.
<br>
<br>

Apesar de poder ser organizada de diversas maneiras, um exemplo de projeto para a estação seria como o abaixo.
<br>
<br>

<div align = "center">
  
  ![image](https://github.com/KalimaraPeleteiro/Arduino-WeatherStation/assets/94702837/18cedbd9-04bc-4ee5-9cf4-1f800541b071)

</div>
