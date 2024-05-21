#include "lab4.h"

nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);
uint8_t uarte_buffer;
uint8_t tab[] = "  ", newRow[] = "\n\r", errmsg[] = "You have gone too far!!!!";
int x = 0, y = 0;
extern matrix[SIZE][SIZE]; 
extern loopean;
int flag = 0;
       
void uarte_write(uint8_t* data, uint8_t length){
    nrfx_uarte_tx(&instance, data, length, 0);
    while(nrfx_uarte_tx_in_progress(&instance)){};
}

void uarte_handler(nrfx_uarte_event_t const *p_event, void *p_context){
    nrfx_uarte_t * p_inst = p_context;
    if (p_event->type == NRFX_UARTE_EVT_RX_DONE){
      flag = 1;
        switch(uarte_buffer){
            case 'w': 
                matrix[y][x] = 0;
                y++;
                break;

            case 's': 
                matrix[y][x] = 0;
                y--;
                break;

            case 'a':   
                matrix[y][x] = 0;
                x--;
                break;

            case 'd': 
                matrix[y][x] = 0;
                x++;
                break;

            case 'q': 
                loopean = 0; 
                break;

            if(y < SIZE && x < SIZE && y >= 0 && x >= 0){
                matrix[y][x] = 1;
            }
            else{
                uarte_write(errmsg, sizeof(errmsg));
            }
        }
    }
}

void send_int(int i){
    char string[SIZE];
    sprintf(string, "%d ", i);
    nrfx_uarte_tx(&instance, string, strlen(string), 0);
}

void print_array(int size, int matrix[SIZE][SIZE]) {
  
  uarte_write(tab, sizeof(tab));

  for (int j = 0; j < size; j++) {
    //printf("%2d ", j); // Print column numbers
    send_int(j);
  }

  //printf("\n"); 
  uarte_write(newRow, sizeof(newRow));
    
    for (int i = size - 1; i >= 0; i--) { // Print from bottom to top
      //printf("%2d ", i); // Print row number
      send_int(i);
      for (int j = 0; j < size; j++) {
          //printf("%2d ", matrix[i][j]);
          send_int(matrix[i][j]);
      }
      uarte_write(newRow, sizeof(newRow));
    }
}