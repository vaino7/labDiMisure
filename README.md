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
