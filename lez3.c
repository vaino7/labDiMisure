static unsigned int *puntatore;
int main(void) {
		puntatore=(unsigned int *)0x40021014;
			*puntatore=(1<<21);
    puntatore=(unsigned int *)0x48001000;
		*puntatore=(1<<16);
		puntatore=(unsigned int *)0x48001014;
		*puntatore=(1<<8);

		int i=0;
		for(i = 0;i<1000000;i++);
			*puntatore=0;
    return 0;
}