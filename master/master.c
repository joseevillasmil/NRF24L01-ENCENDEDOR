#include <master.h>
#use spi (CLK=PIN_B7, DI=PIN_B5, DO=PIN_B6, ENABLE=PIN_B4, MODE=0, BITS=8, , msb_first)
#use RS232 (baud = 9600, bits = 8, parity = N, xmit = pin_c6, rcv = pin_c7)


/*******************************************************************************/
#define  RF24_CS        PIN_A0    // RC1;  chipselect nRF24L01+
#define  RF24_CE        PIN_A1    // RC2;  chipEnable nRF24L01+
#define  RF24_IRQ       PIN_B0    // interrupt pin

#include <nrf.c>
char device;
char action;

#INT_RDA
void  RDA_isr(void) 
{
       // recibimos el dispositivo y la acci�n.
       device = getc();
       delay_ms(5);
       action = getc();
       
       // Respondemos el ok.
       puts("ok ");
       putc(device);
       putc(action);
       puts("\n");
       
       // Enviamos la petici�n.
       RF_TX_DATA[1] = action;
       send_shock_burst(device,s_ad2,s_ad3,s_ad4,s_ad5);
       
       // La enviamos 2 veces para asegurarnos.
       delay_ms(50);
       send_shock_burst(device,s_ad2,s_ad3,s_ad4,s_ad5);
}


void main()
{
   // Iniciamos el buffer de salida.
   for(int i = 0; i<16; i++) {
      RF_TX_DATA[i] = '1';
   }
   
   // Configuramos los puertos b y c.
   set_tris_b(0b00100011);
   set_tris_c(0b10000000);
   
   // Inicializamos el rf, seg�n la libreria.
   init_rf();
   flush_rx();
   
   // Habilitamos la interrupci�n de UART.
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   
   while(1) {
      // Nada por el momento.
   }
}
