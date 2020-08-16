#include <slave.h>
#use spi (CLK=PIN_B7, DI=PIN_B5, DO=PIN_B6, ENABLE=PIN_B4, MODE=0, BITS=8, , msb_first)

/*******************************************************************************/
#define  RF24_CS        PIN_A0    //RC1;  chipselect nRF24L01+
#define  RF24_CE        PIN_A1    //RC2;  chipEnable nRF24L01+
#define  RF24_IRQ       PIN_B0    // interrupt pin
#define  DEVICE         0x31      // hex for '1' char.
#define  ENCENDER       0x41      // hex for 'A' char
/*******************************************************************************/

/*******************STATUS LED DEFINE**************************************/
#define  alive          PIN_B3   //


#include <nrf.c>


void main()
{
   // Configuramos el puerto B.
   set_tris_b(0b00100011);
   
   // Inicializamos el rf (Librer�a)
    init_rf();
    flush_rx();
    
    // Configuramos el dispositivo como receptor (slave)
    configure_rx(DEVICE,s_ad2,s_ad3,s_ad4,s_ad5);
    delay_ms(10);
    
   while(TRUE)
   {
   
   if(!input(RF24_IRQ)){
         if(data_in_rf()){
            output_high(alive);
            delay_ms(300); // evitamos un fallo por tiempo.
            rf_read_Data(); // cargamos el bufer de entrada
        }
      }
   
      // aqu� revisamos el estado de la variable correspondiente a este comando.
      if(RF_RCV_DATA[1] == ENCENDER) {
         // Encendemos
         output_high(alive);
      } else {
         // caso contrario apagamos.
         output_low(alive);
      }
      
   }

}
