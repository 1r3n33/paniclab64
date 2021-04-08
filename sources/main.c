#include <nusys.h>
#include <nualstl_n.h>
#include "controls/controls.h"
#include "titlescreen.h"

void audio_init()
{
    musConfig config;

    config.control_flag = 0;
    config.channels = NU_AU_CHANNELS;
    config.sched = NULL;
    config.thread_priority = NU_AU_MGR_THREAD_PRI;
    config.heap = (unsigned char *)NU_AU_HEAP_ADDR;
    config.heap_length = NU_AU_HEAP_SIZE;
    config.ptr = NULL;
    config.wbk = NULL;
    config.default_fxbank = NULL;
    config.fifo_length = NU_AU_FIFO_LENGTH;
    config.syn_updates = NU_AU_SYN_UPDATE_MAX;
    config.syn_output_rate = NU_AU_OUTPUT_RATE;
    config.syn_rsp_cmds = NU_AU_CLIST_LEN;
    config.syn_retraceCount = 1;
    config.syn_num_dma_bufs = NU_AU_DMA_BUFFER_NUM;
    config.syn_dma_buf_size = NU_AU_DMA_BUFFER_SIZE;

    nuAuStlMgrInit(&config);
}

void mainproc(void)
{
    // Initialization of graphics
    nuGfxInit();

    // Initialization of controllers
    controls_init();

    audio_init();

    // Register call-back
    nuGfxFuncSet((NUGfxFunc)titlescreen_loop);

    // The screen display ON
    nuGfxDisplayOn();

    while (1)
    {
    }
}
