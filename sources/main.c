#include <nusys.h>
#include <nualstl_n.h>
#include "controls/controls.h"
#include "titlescreen.h"

int ptr_buf[NU_AU_SAMPLE_SIZE];
int sfx_buf[NU_AU_SE_SIZE];

extern u8 _audio_sfx_wbkSegmentRomStart[];
extern u8 _audio_sfx_ptrSegmentRomStart[];
extern u8 _audio_sfx_ptrSegmentRomEnd[];
extern u8 _audio_sfx_bfxSegmentRomStart[];
extern u8 _audio_sfx_bfxSegmentRomEnd[];

void Rom2Ram(void *from_addr, void *to_addr, s32 seq_size)
{
    // size must be even.
    if (seq_size & 0x00000001)
        seq_size++;

    nuPiReadRom((u32)from_addr, to_addr, seq_size);
}

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

    // Read and register the sample bank.
    Rom2Ram((void *)_audio_sfx_ptrSegmentRomStart, (void *)ptr_buf, _audio_sfx_ptrSegmentRomEnd - _audio_sfx_ptrSegmentRomStart);
    MusPtrBankInitialize(ptr_buf, _audio_sfx_wbkSegmentRomStart);

    // Read and register the sound effects.
    Rom2Ram((void *)_audio_sfx_bfxSegmentRomStart, (void *)sfx_buf, _audio_sfx_bfxSegmentRomEnd - _audio_sfx_bfxSegmentRomStart);
    MusFxBankInitialize(sfx_buf);
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
