/*
 * This file is part of Cleanflight and ATBetaflight (forked by flightng).
 *
 * Cleanflight and ATBetaflight (forked by flightng) are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and ATBetaflight (forked by flightng) are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
// DEBUG VARIABLE
#include "build/version.h"

// SHOCK SENSOR INCLUDE
// FC_FIRMWARE_IDENTIFIER нет в INAV
#ifndef FC_FIRMWARE_IDENTIFIER
#define SE_INAV
#else
#define SE_BF
#endif 

#ifdef SE_BF
#include "pg/pg.h"
#include "pg/piniobox.h"
#include "msp/msp_box.h"
#endif 

#ifdef SE_INAV
#include "config/parameter_group.h"
#include "io/piniobox.h"
#include "fc/fc_msp_box.h"
#endif 

#include "drivers/io_types.h"

// SHOCK SENSOR VARIABLE
// configirated from cli command
typedef struct seConfig_s {
    uint16_t se_test1;
    uint16_t shock_acc_thr;
    uint32_t shock_delay_ms;
    uint8_t shock_box_permanentid;
} seConfig_t;

PG_DECLARE(seConfig_t, seConfig);

typedef struct seShockValues_s {
    bool init;
    bool enable;
	float acc_thr;
    float acc_max;
    float accADC_max;
    float GForce;
    int pinio_index;
    bool isOn;
    uint32_t enableOnTick;
    const box_t *box;
    bool arm_isOn;
    bool box_isOn;
} seShockValues_t;

void seShockInit(void);
void seShockSetEnable(int pinio_index, boxId_e boxid);
void seShockUpdate(float accADCf);
uint8_t seShockGetBoxId(void);

// DEBUG VARIABLE
typedef struct mtnDebugStruct_s {
    bool requestTelemetry;
    uint32_t i, j;
    uint8_t lastBucketIndex;
}  mtnDebugStruct_t;

typedef struct mtnBaseStruct_s {
    uint32_t packetCountSum;
    uint32_t invalidCountSum;
    mtnDebugStruct_t debug;
}  mtnBaseStruct_t;

extern mtnBaseStruct_t mtn;
