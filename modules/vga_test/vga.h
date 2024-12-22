#ifndef vga_test
#define vga_test

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include <algorithm>
#include "./rgb.pio.h"
#include "./vsync.pio.h"
#include "./hsync.pio.h"   

/**
 * VGA Test
 */

//Test data, 153600 = 640 * 480 / 2 (Because it process 2 pixels at a time in rgb.pio)
unsigned char test_data[153600];
unsigned char * test_addr = &test_data[0];

void start_vga_test(){
    for (int i = 0; i < 153600; i++){
        test_data[i] = strtol("10011100", (char **)NULL, 2);
    }
    //Init the PIO module
    PIO pio = pio0;

    //Add the programs to the PIO   
    uint h_offset = pio_add_program(pio, &hsync_program);
    uint v_offset = pio_add_program(pio, &vsync_program);
    uint rgb_offset = pio_add_program(pio, &rgb_program);

    //Set the state machine of the programs
    uint h_sm = 0;
    uint v_sm = 1;
    uint rgb_sm = 2;


    //Config pins
    hsync_program_init(pio, h_sm, h_offset, 16);
    vsync_program_init(pio, v_sm, v_offset, 17);
    rgb_program_init(pio, rgb_sm, rgb_offset, 18);

    //Claim a rgb direct memory access channel
    int rgb_channel = dma_claim_unused_channel(true);
    //Claim a supervisor (resets the rgb channel when done) channel for the rgb channel
    int rgb_supervisor = dma_claim_unused_channel(true);

    dma_channel_config rgb_channel_config = dma_channel_get_default_config(rgb_channel);
    channel_config_set_transfer_data_size(&rgb_channel_config, DMA_SIZE_8);
    channel_config_set_read_increment(&rgb_channel_config, true);
    channel_config_set_write_increment(&rgb_channel_config, false);
    channel_config_set_dreq(&rgb_channel_config, DREQ_PIO0_TX2);
    channel_config_set_chain_to(&rgb_channel_config, rgb_supervisor);
    dma_channel_configure(rgb_channel, &rgb_channel_config, &pio->txf[rgb_sm], &test_data, 153600, false);

    dma_channel_config supervisor_config = dma_channel_get_default_config(rgb_supervisor);
    channel_config_set_transfer_data_size(&supervisor_config, DMA_SIZE_32);
    channel_config_set_read_increment(&supervisor_config, false);
    channel_config_set_write_increment(&supervisor_config, false);
    channel_config_set_chain_to(&supervisor_config,rgb_channel);

    dma_channel_configure(rgb_supervisor, &supervisor_config, &dma_hw->ch[rgb_channel].read_addr,&test_addr,1,false);

    pio_sm_put_blocking(pio,h_sm, 655);
    pio_sm_put_blocking(pio,v_sm, 479);
    pio_sm_put_blocking(pio,rgb_sm, 319);

    pio_enable_sm_mask_in_sync(pio, ((1u << h_sm) | (1u << v_sm) | (1u << rgb_sm)));

    dma_start_channel_mask((1u << rgb_channel));

}






#endif