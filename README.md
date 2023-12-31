# labDiMisure
Repo per il corso di Laboratorio di Misure [prof. Annalisa Liccardo A.A. 2023/2024]

## Accensione led
1. Portare la tensione anodo-catodo positiva [i.e. alzare la tensione della linea del uControllore]. Voglio che l'output sia digitale

> GPIOx gestisce 16 linee, x $\in {0,...,15}$
e.g. GPIO*A* controlla PA0 PA1 PA2 ... PA15, GPIO*E* controlla PE0 PE1 ... PE15

> Nel datasheet vediamo a quale periferica ogni bus è collegato. è indispensabile per poter far funzionare la periferica!

2. Trovato il bus al quale è associata la periferica che mi interessa, vado nel *reference manual* per vedere quali registri devo modificare

Ogni periferica GPIO (General Purpose) possiede quattro modalità di funzionamento:
- Input Mode
- General purpose output mode
- Alternate function mode
- Analog mode

Ogni periferica possiede un:
- IDR (Input Data Register): da utilizzare quando vogliamo usare la periferica come input
- ODR (Output Data Register): da utilizzare quando vogliamo usare la periferica in output
Siccome vogliamo accendere il led [i.e. stiamo usando la periferica come output] dovremmo scrivere __qualcosa__ nel ODR

**Nota: Se settiamo l'analog mode, IDR e ODR vengono ignorati per come è stato implementato elettronicamente ogni periferica sulla scheda**

3. Impostiamo una determinata linea di una determinata GPIO in modalità __uscita digitale__
Dal *reference manual* vediamo che dobbiamo scrivere '01' nel MODERx (x=0,...,15) [i.e. una delle sedici linee di __una determinata periferica__ che vogliamo usare]

4. Alziamo il livello di tensione della linea che ci interessa [e.g. PE8]
Per poterlo fare dobbiamo scrivere __qualcosa__ nell'ODR:
   - 1 => stiamo alzando la linea quindi la si porterà a VOH
   - 0 => stiamo abbassando la linea quindi si porterà a VOL
__Nel nostro esempio quindi andremo ad alzare ODR8__

5. Identificare nel *reference manual* (cap. 3.2 - memory organization) ***dov'è mappata ogni periferica***
> Gli offset di ogni periferica è salvato in una libreria, quindi stai chill

6. Identificare l'offset, relativa al base address, dei particolari registri [e.g. MDOER]

------------------------------------------------------------------------
# Timer base (6 e 7)[16 bit]
__Cap.22 Reference manual__
> Abbiamo timer a 16 e 32 bit

- Divisore di frequenza (Prescaler PSC): Divide la freq di clock per un intero che decidiamo noi -> invece di incrementatre ogni impulso di clock, aumentiamo ogni K [costante fissata prima]

- Auto-Reload register (ARR)

> Dobbiamo abilitare il conteggio in CR1 della periferica timer che vogliamo usare (e.g. TIM6_CR1) 

> Posso usare anche il timer in modalità base dei tempi per generare un interrupt ogni tot tempo

## TIMx_CR1 Control Register
***CEN = Counter ENable bit***

## TIMx_SR Status Register
***UIF = Update Interrupt Flag*** [i.e. quando il timer arriva al valore massimo, si resetta e si alza questo flag]

## TIMx_CNT Counter Register (a 16 bit per TIM6 e TIM7)
***Contiene il valore del contatore***

## TIMx_PSC Prescaler Register
***Contiene il valore del prescaler***

## TIMx_ARR Auto-Reload Register
***Contiene il valore di auto-reload***


# Utilizziamo il timer come base dei tempi
Viene confrontato continuamente il valore del contatore con il valore di auto-reload. Quando il contatore raggiunge il valore di auto-reload, viene generato un interrupt e il contatore viene automaticamente resettato a 0.
TIMx_CNT viene incrementato e viene alzato il flag UIF (Update Interrupt Flag) 

> Dobbiamo monitorare UIF. ***Nota che dobbiamo occuparci noi di abbassare UIF***

Il valore in ARR deve essere sempre riferito agli impulsi di clock

### TIMx_SR Status Register in cui è presente UIF

***Nota che di default ARR si trova a 0xFFFF e quindi per sovrascriverelo non dobbiamo fare la or***


### Formula per il calcolo di PSC 
(PSC +1) = ($\delta t * $f_ck ) / ARR
