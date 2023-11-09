# Creazione progetto in KEIL uVision
1. Proj > new uVision proj [selezionare cartella in cui depositare il progetto]
2. Selezionare dal menu che appare (i.e. " Select Device for Target 'Target x'") STM32F303VCTx
3. Creare il file sorgente in 'Source Group'

## Cambiare il Debugger 
Dopo aver creato con successo il progetto, è necessario specificare il debugger "ST-LINK":
1. Nel pannello a sinistra (i.e. pannello progetti), tasto destro su 'Target 1'
2. Cliccare 'Options for Target 1'
3. Andare nella sezione 'Debug' (penultima scheda) e selezionare St-LINK Debugger
