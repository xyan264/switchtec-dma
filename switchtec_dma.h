// SPDX-License-Identifier: GPL-2.0
/*
 * Microchip Switchtec(tm) DMA Controller Driver
 * Copyright (c) 2020, Microchip Corporation
 */

#ifndef _SWITCHTEC_DMA_H
#define _SWITCHTEC_DMA_H

#include <linux/dmaengine.h>

#define SWITCHTEC_HOST_PORT_NUM_PER_PAX 8
#define SWITCHTEC_BUF_NUM_PER_HOST_PORT 6

/**
 * enum ltssm_major - ltssm major state
 * @LTSSM_MAJOR_DETECT: Detect
 * @LTSSM_MAJOR_POLL: Polling
 * @LTSSM_MAJOR_CFG: Config
 * @LTSSM_MAJOR_L0: L0
 * @LTSSM_MAJOR_RECOVERY: Recovery
 * @LTSSM_MAJOR_DISABLE: Disable
 * @LTSSM_MAJOR_LOOPBK: Loopback
 * @LTSSM_MAJOR_HOTRST: Hot reset
 * @LTSSM_MAJOR_L0S: TX L0s
 * @LTSSM_MAJOR_L1: L1
 * @LTSSM_MAJOR_L2: L2
 * @LTSSM_MAJOR_NUMBER:
 */
enum ltssm_major {
	LTSSM_MAJOR_DETECT,
	LTSSM_MAJOR_POLL,
	LTSSM_MAJOR_CFG,
	LTSSM_MAJOR_L0,
	LTSSM_MAJOR_RECOVERY,
	LTSSM_MAJOR_DISABLE,
	LTSSM_MAJOR_LOOPBK,
	LTSSM_MAJOR_HOTRST,
	LTSSM_MAJOR_L0S,
	LTSSM_MAJOR_L1,
	LTSSM_MAJOR_L2,
	LTSSM_MAJOR_NUMBER,
};

/**
 * struct switchtec_host_port - host port information
 * @hfid: hfid of the host port
 * @pax_id: PAX ID of the host port
 * @phys_pid: Physical port ID of the host port
 * @link_state: Link state of the host port
 */
struct switchtec_host_port {
	u16 hfid;
	u8 pax_id;
	u8 phys_pid;
	enum ltssm_major link_state;
};

/**
 * struct switchtec_buffer - buffer information
 * @from_hfid: hfid on which the buffer is allocated
 * @to_hfid: hfid will use the buffer
 * @index: buffer index, 0 to SWITCHTEC_BUF_NUM_PER_HOST_PORT
 * @dma_addr: dma address of the buffer
 * @dma_size: size of the buffer
 * @rhi_index: RHI index of the buffer
 * @local_dfid: local DMA FID
 * @remote_dfid: remote DMA FID
 * @local_rhi_dfid: local RHI DMA FID
 * @remote_rhi_dfid: remote RHI DMA FID
 */
struct switchtec_buffer {
	u16 from_hfid;
	u16 to_hfid;
	u8 index;
	u64 dma_addr;
	u64 dma_size;
	u16 rhi_index;
	u16 local_dfid;
	u16 remote_dfid;
	u16 local_rhi_dfid;
	u16 remote_rhi_dfid;
};

int switchtec_fabric_get_pax_count(struct dma_device *dma_dev);
int switchtec_fabric_get_host_ports(struct dma_device *dma_dev, u8 pax_id,
				    int port_num,
				    struct switchtec_host_port *ports);
int switchtec_fabric_register_buffer(struct dma_device *dma_dev, u16 peer_hfid,
				     u8 buf_index, u64 buf_addr, u64 buf_size,
				     int *buf_vec);
int switchtec_fabric_deregister_buffer(struct dma_device *dma_dev,
				       u16 peer_hfid, u8 buf_index);
int switchtec_fabric_get_peer_buffers(struct dma_device *dma_dev, u16 hfid,
				      int buf_num,
				      struct switchtec_buffer *bufs);
int switchtec_fabric_get_buffer_number(struct dma_device *dma_dev);
#endif
