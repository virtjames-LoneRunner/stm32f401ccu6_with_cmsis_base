#ifndef DMA_H
#define DMA_H

#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>

#define NUM_DMA_PERIPH  2
#define NUM_DMA_STREAM  8
#define NUM_DMA_CHANNEL 8

// Notes:
// 1. The DMA controller only copes with little-endian addressing
// 2. PSIZE, MSIZE and NDT[15:0] have to be configured so as to ensure that the last transfer is not incomplete.

typedef enum {
  DMA_1,
  DMA_2,
} dma_idx_e;

typedef enum {
  DMA_STREAM0,
  DMA_STREAM1,
  DMA_STREAM2,
  DMA_STREAM3,
  DMA_STREAM4,
  DMA_STREAM5,
  DMA_STREAM6,
  DMA_STREAM7,
} dma_stream_e;

typedef enum {
  DMA_CH0,
  DMA_CH1,
  DMA_CH2,
  DMA_CH3,
  DMA_CH4,
  DMA_CH5,
  DMA_CH6,
  DMA_CH7,
} dma_channel_e;

typedef enum {
  DMA_BURST_SINGLE,
  DMA_BURST_INCR4,
  DMA_BURST_INCR8,
  DMA_BURST_INCR16,
} dma_burst_e;

typedef enum {
  DMA_DBM_DISABLED,
  DMA_DBM_ENABLED,
} dma_dbm_e;

typedef enum {
  DMA_PL_LOW,
  DMA_PL_MEDIUM,
  DMA_PL_HIGH,
  DMA_PL_VERY_HIGH,
} dma_pl_e;

typedef enum {
  DMA_PINCOS_0,
  DMA_PINCOS_1,
} dma_pincos_e;

typedef enum {
  DMA_SIZE_BYTE,
  DMA_SIZE_HALF_WORD,
  DMA_SIZE_WORD,
} dma_size_e;

typedef enum {
  DMA_INC_MODE_FIXED,
  DMA_INC_MODE_INCR,
} dma_incr_mode_e;

typedef enum {
  DMA_CIRCULAR_MODE_DISABLED,
  DMA_CIRCULAR_MODE_ENABLED,
} dma_circ_e;

typedef enum {
  DMA_DIR_PERIPH_TO_MEM,
  DMA_DIR_MEM_TO_PERIPH,
  DMA_DIR_MEM_TO_MEM,
} dma_dir_e;

typedef enum {
  DMA_PFCTRL_DMA_CONTROL,
  DMA_PFCTRL_AS_CONTROL,
} dma_pfctrl_e;

typedef enum {
  DMA_MEM0,
  DMA_MEM1,
} dma_mem_e;

typedef enum {
  DMA_FIFO_INT_DISABLED,
  DMA_FIFO_INT_ENABLED,
} dma_FEIE_e;

typedef enum {
  DMA_FIFO_LESS_1_4,
  DMA_FIFO_LESS_1_2,
  DMA_FIFO_LESS_3_4,
  DMA_FIFO_LESS_FULL,
  DMA_FIFO_EMPTY,
  DMA_FIFO_FULL,
} dma_FS_e;

typedef enum {
  DMA_FIFO_TRESH_1_4,
  DMA_FIFO_TRESH_1_2,
  DMA_FIFO_TRESH_3_4,
  DMA_FIFO_TRESH_FULL,
} dma_FTH_e;

typedef enum {
  DMA_FIFO_DMDIS_ENABLE,
  DMA_FIFO_DMDIS_DISABLE,
} dma_DMDIS_e;

typedef enum {
  DMA_STREAM_ENABLE,
  DMA_STREAM_DISABLE,
} dma_stream_ctrl_e;

typedef struct {
  // Identify which DMA_Stream Reg to set
  dma_idx_e      dmaIndex;
  dma_stream_e      dmaStream;

  dma_channel_e     channel;
  dma_burst_e       mBurst;
  dma_burst_e       pBurst;
  dma_dbm_e         enDBM;
  dma_pl_e          pl;
  dma_pincos_e      pIncos;
  dma_size_e        mSize;
  dma_size_e        pSize;
  dma_incr_mode_e   mInc;
  dma_incr_mode_e   pInc;
  dma_circ_e        circ;
  dma_dir_e         dir;
  dma_pfctrl_e      pFCtrl;

  bool              enTCIE;
  bool              enHTIE;
  bool              enTEIE;
  bool              enDMEIE;

  dma_stream_ctrl_e enStream;

  uint32_t          m0Addr;
  uint32_t          m1Addr;
  uint32_t          pAddr;
  uint32_t          numDataTransfer;

  // TODO: Check how mBurst and pBurst
  // should affect these configurations
  // dma_FEIE_e        enFEIE;
  // dma_FS_e          fifoStatus;
  // dma_DMDIS_e       enDMDIS;
  // dma_FTH_e         fifoTresh;
} dma_stream_config_t;

// SETUP
void dma_global_conf(DMA_TypeDef *globalConfig);
void dma_configure_stream(const dma_stream_config_t *dma_stream);
void dma_start(const dma_idx_e dma, const dma_stream_e stream, uint32_t *srcAddr, uint32_t *dstAddr, uint16_t length);

void dma_stream_set_mem_address(DMA_Stream_TypeDef *dmaStream, uint32_t memAddr, const dma_mem_e index);
void dma_stream_set_periph_address(DMA_Stream_TypeDef *dmaStream, uint32_t periphAddr);
void dma_stream_select_channel(DMA_Stream_TypeDef *dmaStream, const dma_channel_e channel);
void dma_stream_set_num_data_trans(DMA_Stream_TypeDef *dmaStream, const uint32_t numDataTrans);
void dma_stream_set_direction(DMA_Stream_TypeDef *dmaStream, const uint32_t dir);
void dma_stream_set_data_size(DMA_Stream_TypeDef *dmaStream, const uint32_t size);

void dma_stream_set_stream_buffer_mode(DMA_Stream_TypeDef *dmaStream);
void dma_stream_set_stream_prio_lvl(DMA_Stream_TypeDef *dmaStream);

void dma_stream_enable(DMA_Stream_TypeDef *dmaStream);
void dma_stream_disable(DMA_Stream_TypeDef *dmaStream);

void dma_stream_set_fifo_mode(DMA_Stream_TypeDef *dmaStream);
void dma_stream_flush_fifo(DMA_Stream_TypeDef *dmaStream);

#endif
