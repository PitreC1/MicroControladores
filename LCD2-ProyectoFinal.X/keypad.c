#include <xc.h>
#include <pic16f887.h>

#define write_port PORTB             /* latch register to write data on port */
#define read_port PORTB            /* PORT register to read data of port */
#define Direction_Port TRISB

#define KEYPAD_WRITE PORTB             /* latch register to write data on port */
#define KEYPAD_READ PORTB             /* PORT register to read data of port */
#define KEYPAD_PORT TRISB

#define _XTAL_FREQ 4000000

unsigned char col_loc,rowloc,temp_col;
unsigned char keypad[4][4]={'1','2','3','A',
                             '4','5','6','B',
                             '7','8','9','C',
                             '*','0','#','D'}; 

unsigned char Keypad_Key_Press(void){
 const unsigned char keypad_deco[17]=   
 {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C','*', '0', '#', 'D', 0};
 
    unsigned int tec = 0, fila;
 
    
    for (fila = 0b00000001; fila < 0b00010000; fila <<= 1)
    {
        PORTB =fila<<4;  //lo traslada 4  posicones para sacar por las filas
        if (PORTBbits.RB0== 1) break; tec++;
        if (PORTBbits.RB1 == 1) break; tec++;
        if (PORTBbits.RB2 == 1) break; tec++;
        if (PORTBbits.RB3 == 1) break; tec++;
    }
    PORTB = 0x00;
    return keypad_deco[tec];//retorna el codigo deseao de la tecla
}


unsigned char keyfind()
{      
    
    Direction_Port = 0xf0;              /*TRISB = 0B 1111 0000*/
    unsigned char temp1;
   
        write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/
      do
      {
        do
        {
          
            col_loc = read_port & 0xf0; /*mask port with f0 and copy it to col_loc variable*/   
        
        }while(col_loc!=0xf0);          /*Check initially at the start there is any key pressed*/ 
         col_loc = read_port & 0xf0;    /*mask port with f0 and copy it to col_loc variable*/  
      }while(col_loc!=0xf0);
      
      __delay_ms(50);
        write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/
        do
        { do
            
            {
               
                col_loc = read_port & 0xf0;
            }while(col_loc==0xf0);      /*Wait for key press*/
         col_loc = read_port & 0xf0;
        }while(col_loc==0xf0);          /*Wait for key press*/
               
        __delay_ms(20);
         
        col_loc = read_port & 0xf0;
               
   
    
    while(1)
    {
        write_port  = 0xfe;                 /*make Row0(D0) Gnd and keep other row(D1-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=0;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Monitor the status of Port and Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/    
            }
            break;
        }
        
        write_port = 0xfd;                  /*make Row1(D1) Gnd and keep other row(D0-D2-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=1;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Monitor the status of Port and Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
        write_port = 0xfb;                  /*make Row0(D2) Gnd and keep other row(D0-D1-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=2;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
        write_port = 0xf7;                  /*make Row0(D3) Gnd and keep other row(D0-D2) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=3;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
    }

    
    
    while(1)
    {
        
        if(col_loc==0xe0)
        {
             return keypad[rowloc][0];      /*Return key pressed value to calling function*/            
        }
        else 
            if(col_loc==0xd0)
        {
            return keypad[rowloc][1];       /*Return key pressed value to calling function*/   
        }
        else
            if(col_loc==0xb0)
        {
            return keypad[rowloc][2];       /*Return key pressed value to calling function*/
        }
        else
            
        {
            return keypad[rowloc][3];       /*Return key pressed value to calling function*/           
        }    
    }
    
   __delay_ms(300);     
}