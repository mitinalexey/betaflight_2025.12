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
#include "build/version.h"
#include "drivers/io_types.h"
#include "pg/pg.h"

/*
typedef enum {
    QMI8658_REG_WHO_AM_I = 0x00,       // chip id, should be 0x05
    QMI8658_REG_REVISION_ID = 0x01,    // chip revision, should be 0x7C

} qmi8658Register_e;
*/
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
