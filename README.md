# VacuumChamber

Firmware de controle e interface de uma **câmara de vácuo** usada para **simular em solo a variação de pressão de um voo**. Com a pressão reduzida e restaurada de forma controlada, os computadores de bordo "sentem" a subida e a descida do foguete. Assim dá para validar barômetros, a detecção de apogeu e o acionamento dos eventos de recuperação antes de um lançamento real.

## Funcionalidades

- Leitura contínua de pressão com **BMP280** e conversão para altitude equivalente
- Interface gráfica em display **TFT** (MCUFRIEND / ILI9341) no Arduino Mega: pressão, altitude, estado do teste e controles
- Fontes e ícones em bitmap próprios (`FreeMono*.h`, `pause_64_64_28f.h`)
- Flags de configuração para tela e debug (`SCREEN_ON`, `DEBUG_PRINTS`)

## Arquivos

| Arquivo | Descrição |
|---|---|
| `VacuumChamber.ino` | Firmware principal |
| `URD_Vacuum_Chamber_Mega_MCUFRIEND*.txt` | Versões alternativas da interface (com e sem logo) |
| `ajustes.txt` | Variante para display ILI9341 via SPI |

**Stack:** C++ · Arduino Mega · Adafruit GFX · MCUFRIEND_kbv · Adafruit BMP280
