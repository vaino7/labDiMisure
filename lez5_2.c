#include <stm32f303xc.h>
// Voglio fare in modo tale che premo il pulsante, aspetto in un ciclo bloccante che il pulsante viene rilasciato e poi incrementare il contatore
//GPIOA sta sul bus AHB2
int main(void){
    RCC -> AHBENR |= (1<<17); //Abilito il clock per il bus AHB2
    RCC -> AHBENR |= (1<<21); //Abilito il clock per il bus AHB2
    GPIOA->MODER |= 0x0 << 0; //PA0 è in modalità input

    //Settiamo la linee 8 a 15 in modalità output
    unsigned int i=0;
    for(i = 8; i <= 15; i++){
        GPIOE->MODER |= 0x1 << (i*2); //PA8, PA9, ... , PA15 sono in modalità output
    }
    int contatore = 0;
    while(1){
        if(GPIOA->IDR & 0x1){ //Se il bit 0 di IDR è 1, il pulsante è premuto
            contatore++;
            while(GPIOA->IDR & 0x1){} //Aspetto che il pulsante venga rilasciato
            GPIOE -> ODR = (contatore << 8);
    }

    return 0;
}
