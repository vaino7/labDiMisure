//Oggi vedremo i timer
// e.g. misuriamo il tempo in cui è premuto il pulsante user 

/*
- PREMO USER
Abilito la periferica timer
azzero il conteggio
abilito il conteggio 
- RILASCIO USER
disabilito il conteggio
leggo impulsi contati

Quanto tempo è passato? delta_t = impulsi contati * 1/freq_clock [senza prescaler]
                        delta_t = impulsi contati * 1/(freq_clock)*(PSC+1) [con prescaler]

*/

#include <stm32f303xc.h>
#include <stdio.h>
#define FREQ_CLK 8000000 // 8MHz

int main(void){
    // TIM6 si trova sul bus APB1
    // Abilito il clock sul bus APB1
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // (1<<4)
    // Abilito il pulsante USER
    RCC -> AHBENR |= (1<<17); 
    GPIOA->MODER |= 0x0 << 0; //PA0 è in modalità input

    // resetto il counter
    
    int contatore = 0;
    float tempo = 0;
    // andiamo in overflow ogni 8 millisecondi quindi settiamo il PSC a 1000 e.g. 8MHz/1000 = 8000Hz
    TIM6->PSC = 1000;
     while(1){
        if(GPIOA->IDR & 0x1){ //Se il bit 0 di IDR è 1, il pulsante è premuto 
            TIM6->CNT = 0;
            TIM6->CR1 |= TIM_CR1_CEN; // (1<<0) abilito il conteggio
            while(GPIOA->IDR & 0x1){} // IDLE
            contatore = TIM6->CNT; // numero di impulsi contati
            TIM&->CR1 &= ~TIM_CR1_CEN; // (1<<0) disabilito il conteggio
        }
        else{
            tempo = contatore * 1/FREQ_CLK;
            // printf("Tempo in cui è stato premuto il pulsante: %f\n", tempo);
        }
    return 0;
}
}