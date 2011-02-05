/*HEADER**********************************************************************
Copyright (c)
All rights reserved
This software embodies materials and concepts that are confidential to Redpine
Signals and is made available solely pursuant to the terms of a written license
agreement with Redpine Signals

Project name : RS22
Module name  : SPI driver
File Name    : rs22_firmware.h

File Description:


Author :

Rev History:
Ver  By         date          Description
---------------------------------------------------------
1.1  Redpine Signals
--------------------------------------------------------
*END**************************************************************************/

#ifndef __RS22_FIRMWARE_H__
#define __RS22_FIRMWARE_H__


const uint8_t sbtaim1[] = {
#include "sbinst1.map"
};
const uint8_t sbtaim2[] = {
#include "sbinst2.map"
};
const uint8_t sbtadm[] = {
#include "sbdata1.map"
};

#if 1

const uint8_t iutaim1[] = {
#include "iuinst1.map"
};

const uint8_t iutaim2[] = {
#include "iuinst2.map"
};


const uint8_t iutadm[] = {
#include "iudata.map"
};

const uint8_t fftaim1[] = {
#include "ffinst1.map"
};
const uint8_t fftaim2[] = {
#include "ffinst2.map"
};
const uint8_t fftadm[] = {
#include "ffdata.map"
};
const uint8_t sbtadm2[] = {
#include "sbdata2.map"
};
#endif




#endif
