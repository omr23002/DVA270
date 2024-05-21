#include "lab4.h"

extern uarte_buffer;
extern instance;
extern flag;
int loopean = 1;
int matrix[SIZE][SIZE];

int main (){
    NVIC_ClearPendingIRQ(NRFX_IRQ_NUMBER_GET(NRF_UARTE_INST_GET(0)));
    NVIC_EnableIRQ(NRFX_IRQ_NUMBER_GET(NRF_UARTE_INST_GET(0)));
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);
    nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
    if(errr != 0){}
    nrfx_uarte_init(&instance, &config, uarte_handler);
    nrfx_systick_init();

    int x = 0, y = 0;
    uint8_t cls[] = CLEAR_SCREEN;
    
    // Initialize the matrix to 0
    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE; i++) {
            matrix[i][j] = 0;
        }
    }

    matrix[y][x] = 1;
    
    uarte_write(cls, sizeof(cls));
    print_array(SIZE, matrix);

    while(loopean){
        if(flag = 1){
            flag = 0;
            nrfx_uarte_rx(&instance, &uarte_buffer, sizeof(&uarte_buffer));
            uarte_write(cls, sizeof(cls));
            print_array(SIZE, matrix);
            nrfx_systick_delay_ms(400);
        }
        
    }
}