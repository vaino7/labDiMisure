// Iniziamo a lavorare con input digitali i.e. pulsante blu 
// Usiamo l'IDR 
// 6.5 reference manual dice user button usa PA0

//Facciamo una cazzatina: pulsante premuta -> led blu acceso, pulsante rilasciato -> led blu spento

#include <stm32f303xc.h>

//GPIOA sta sul bus AHB2
int main(void){
    RCC -> AHBENR |= (1<<17); //Abilito il clock per il bus AHB2
    RCC -> AHBENR |= (1<<21); //Abilito il clock per il bus AHB2
    GPIOA->MODER |= 0x0 << 0; //PA0 è in modalità input

    //Settiamo la linea 8 in modalità output
    GPIOE->MODER |= 0x1 << 16; //PA8 è in modalità output

    while(1){
        if(GPIOA->IDR & 0x1){ //Se il bit 0 di IDR è 1, il pulsante è premuto
            GPIOE->ODR |= 0x1 << 8; //Accendo il led blu
        }else{
            GPIOE->ODR &= ~(0x1 << 8); //Spengo il led blu
        }
    }

    return 0;
}

