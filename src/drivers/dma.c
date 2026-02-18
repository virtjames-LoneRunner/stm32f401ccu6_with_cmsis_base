#include "dma.h"
#include <stdint.h>

// DMA Streams as 2-dimensional array
static DMA_Stream_TypeDef *streams[NUM_DMA_PERIPH][NUM_DMA_STREAM] = {
  {
    DMA1_Stream0,
    DMA1_Stream1,
    DMA1_Stream2,
    DMA1_Stream3,
    DMA1_Stream4,
    DMA1_Stream5,
    DMA1_Stream6,
    DMA1_Stream7,
  },
  {
    DMA2_Stream0,
    DMA2_Stream1,
    DMA2_Stream2,
    DMA2_Stream3,
    DMA2_Stream4,
    DMA2_Stream5,
    DMA2_Stream6,
    DMA2_Stream7,
  }
};

void dma_configure_stream(const dma_stream_config_t *dma_stream) {
  uint32_t streamIndex = dma_stream->dmaStream;
  uint32_t dmaIndex = dma_stream->dmaIndex;
  DMA_Stream_TypeDef *stream = streams[dmaIndex][streamIndex];
  DMA_TypeDef *dma = (dmaIndex == 0) ? DMA1 : DMA2;

  stream->CR &= ~(DMA_SxCR_EN);
  while (stream->CR & DMA_SxCR_EN); // Wait for DMA to be disabled
  
  uint32_t reg32 = stream->CR & ~(DMA_SxCR_CHSEL | DMA_SxCR_MBURST | DMA_SxCR_PBURST | 
                                  DMA_SxCR_DBM | DMA_SxCR_PL | DMA_SxCR_PINCOS | DMA_SxCR_MSIZE |
                                  DMA_SxCR_PSIZE | DMA_SxCR_MINC | DMA_SxCR_PINC | DMA_SxCR_CIRC |
                                  DMA_SxCR_DIR | DMA_SxCR_PFCTRL | 
                                  DMA_SxCR_TCIE | DMA_SxCR_HTIE |   // Reset the interrupt flags
                                  DMA_SxCR_TEIE | DMA_SxCR_DMEIE);

  // Edit reg32 using dma_stream values. Each would have to be shifted to the right positions
  reg32 |= dma_stream->channel << DMA_SxCR_CHSEL_Pos
        |  dma_stream->mBurst << DMA_SxCR_MBURST_Pos
        |  dma_stream->pBurst << DMA_SxCR_PBURST_Pos
        |  dma_stream->enDBM << DMA_SxCR_DBM_Pos
        |  dma_stream->pl << DMA_SxCR_PL_Pos
        |  dma_stream->pIncos << DMA_SxCR_PINCOS_Pos
        |  dma_stream->mSize << DMA_SxCR_MSIZE_Pos
        |  dma_stream->pSize << DMA_SxCR_PSIZE_Pos
        |  dma_stream->mInc << DMA_SxCR_MINC_Pos
        |  dma_stream->pInc << DMA_SxCR_PINC_Pos
        |  dma_stream->circ << DMA_SxCR_CIRC_Pos
        |  dma_stream->dir << DMA_SxCR_DIR_Pos
        |  dma_stream->pFCtrl << DMA_SxCR_PFCTRL_Pos
        |  dma_stream->enTCIE << DMA_SxCR_TCIE_Pos
        |  dma_stream->enHTIE << DMA_SxCR_HTIE_Pos
        |  dma_stream->enTEIE << DMA_SxCR_TEIE_Pos
        |  dma_stream->enDMEIE << DMA_SxCR_DMEIE_Pos;

  // Clear previous interrupts
  if (streamIndex < 4) {
      dma->LIFCR = (0x3D << (streamIndex > 1 ? (streamIndex * 6 + 4) : (streamIndex * 6)));
  } else {
      uint8_t hIndex = streamIndex - 4;
      dma->HIFCR = (0x3D << (hIndex > 1 ? (hIndex * 6 + 4) : (hIndex * 6)));
  }

  // CONFIGURE FIFO (Required for Bursts!)
  // If mBurst or pBurst is set, we must enable the FIFO.
  uint32_t fcr = stream->FCR & ~(DMA_SxFCR_DMDIS | DMA_SxFCR_FTH);
  if (dma_stream->mBurst || dma_stream->pBurst) {
      fcr |= DMA_SxFCR_DMDIS;      // Disable Direct Mode (Enable FIFO)
      fcr |= (3 << DMA_SxFCR_FTH_Pos); // Set threshold to Full for bursts
  }

  stream->FCR = fcr;
  stream->CR = reg32;
}

void dma_start(const dma_idx_e dma, const dma_stream_e stream, uint32_t *srcAddr, uint32_t *dstAddr, uint16_t length) {
  DMA_Stream_TypeDef *s = streams[dma][stream];

  s->PAR = (uint32_t)srcAddr;
  s->M0AR = (uint32_t)dstAddr;

  s->NDTR = length;

  dma_stream_enable(s);
}

void dma_stream_enable(DMA_Stream_TypeDef *dmaStream) {
  dmaStream->CR |= DMA_SxCR_EN;
}
void dma_stream_disable(DMA_Stream_TypeDef *dmaStream) {
  dmaStream->CR &= ~(DMA_SxCR_EN);
}

void dma_stream_set_mem_address(DMA_Stream_TypeDef *dmaStream, uint32_t memAddr, const dma_mem_e index) {
  switch (index) {
    case DMA_MEM0:
      dmaStream->M0AR = memAddr;
      break;
    case DMA_MEM1:
      dmaStream->M1AR = memAddr;
      break;
  }
}
void dma_stream_set_periph_address(DMA_Stream_TypeDef *dmaStream, uint32_t periphAddr) {
  dmaStream->PAR = periphAddr;
}

void dma_stream_select_channel(DMA_Stream_TypeDef *dmaStream, const dma_channel_e channel) {
  uint32_t reg32 = (dmaStream->CR & ~(DMA_SxCR_CHSEL));
  dmaStream->CR = reg32 | (channel << DMA_SxCR_CHSEL_Pos);
}
