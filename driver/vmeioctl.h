/*
    Defines and typedefs for the interface between universeII driver and
    vmelib library.
    Copyright (C) 2008 Andreas Ehmanns <universeII@gmx.de>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef VMEIOCTL_H
#define VMEIOCTL_H

/* Image related defines */
#define IOCTL_SET_CTL      0xF001
#define IOCTL_GET_IMAGE    0xF002
#define IOCTL_SET_IMAGE    0xF003
// 0xF003 and 0xF004 undefined
//#define IOCTL_PCI_SIZE     0xF006
//#define IOCTL_SET_WINT     0xF007
#define IOCTL_GET_ADDR     0xF004
#define IOCTL_SET_OPT      0xF005


/* IRQ related defines */
#define IOCTL_GEN_VME_IRQ  0xF101
#define IOCTL_SET_IRQ      0xF102
#define IOCTL_WAIT_IRQ     0xF103
#define IOCTL_FREE_IRQ     0xF104


/* DMA defines */
#define IOCTL_REQUEST_DMA  0xF201
#define IOCTL_RELEASE_DMA  0xF202


/* Defines for DMA linked list operations */
#define IOCTL_NEW_DCP      0xF301
#define IOCTL_ADD_DCP      0xF302
#define IOCTL_EXEC_DCP     0xF303
#define IOCTL_DEL_DCL      0xF304


/* Mailbox related defines */
#define IOCTL_SET_MBX      0xF401
#define IOCTL_WAIT_MBX     0xF402
#define IOCTL_RELEASE_MBX  0xF403


/* Misc. */
#define IOCTL_TEST_ADDR    0xF901
#define IOCTL_TEST_BERR    0xF902

#define IOCTL_RESET_ALL    0xF903
#define IOCTL_VMESYSRST    0xF904



typedef struct
{
    int32_t ms;
    uint32_t base;
    uint32_t size;
} image_regs_t;


typedef struct
{
    uint32_t addr;
    uint32_t count;
    int32_t vas;
    int32_t vdw;
    int32_t dma_ctl;
    int32_t bufNr;
} dma_param_t;


typedef struct
{
    uint32_t dctl;
    uint32_t dtbc;
    uint32_t dva;
    int32_t list;
} list_packet_t;


typedef struct
{
    int32_t vmeIrq;
    int32_t vmeStatus;
    int32_t vmeAddrSt;
    int32_t vmeValSt;
    int32_t vmeAddrCl;
    int32_t vmeValCl;
} irq_setup_t;


typedef struct
{
    int32_t irqLevel;
    int32_t statusID;
    uint32_t timeout;
} irq_wait_t;


typedef struct
{
    uint32_t addr;
    uint32_t mode;
} there_data_t;

#endif
