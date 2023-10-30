// utilizziamo il timer come base dei tempi con delta_t = 1s
#include <stm32f303xc.h>
#include <stdio.h>
#define FREQ_CLK 8000000 // 8MHz
#define arr 32000

// Vogliamo fare in modo che il led si accendano per rappresentare un contatore binario dei secondi
int main(){
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; // (1<<4)
    RCC->AHBENR |= RCC_AHBENR_GPIOEEN; // (1<<21)
    for(int i=8; i<16;i++) GPIOE->MODER |= 0x1 << (i*2); //PE8-PE15 sono in modalità output
    TIM6->PSC = 249; 
    //Imposto il valore di arr in modo da alzare a 1sec il segnale di overflow
    TIM6->ARR = arr;
    TIM6->CR1 |= TIM_CR1_CEN; // (1<<0) abilito il conteggio
    TIM6->SR = 0; // resetto il flag di overflow
    int contatore = 0;
    while(1){
        if(TIM->SR & 0x1){
            TIM6->SR=0;
            contatore++;
            GPIOE->ODR = contatore << 8;
        }
    }
    return 0;
}