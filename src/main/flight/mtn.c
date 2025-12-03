#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"
#include "flight/mtn.h"

#ifdef SE_BF
#include "pg/pg.h"
#include "pg/pg_ids.h"
#include "msp/msp_box.h"
#define BOX_PERMANENT_ID_USER1 40
#endif 

#ifdef SE_INAV
#include "config/parameter_group.h"
#include "config/parameter_group_ids.h"
#include "fc/fc_msp_box.h"
#endif 


#include "common/axis.h"
#include "fc/runtime_config.h"
#include "sensors/acceleration.h"

#include "io/piniobox.h"

#include "drivers/system.h"
#include "drivers/time.h"

#include "build/debug.h"

mtnBaseStruct_t mtn;

// SHOCK SENSOR
PG_REGISTER_WITH_RESET_FN(seConfig_t, seConfig, PG_SE_CONFIG, 1);

void pgResetFn_seConfig(seConfig_t *config) {
	config->se_test1 = 123;
	config->shock_acc_thr = 1000;
	config->shock_delay_ms = 1000;
  	config->shock_box_permanentid = BOX_PERMANENT_ID_USER1;
}
/*
bool BoxIdState4 = false;
bool Arming4 = false;
bool Shock4 = false;

bool ShockVal4 = false;
*/
float seGForce = 0;

#ifdef SE_BF
bool get_arming_flag(void) {
	// !(getArmingDisableFlags() & ARMING_DISABLED_ARM_SWITCH)
	armingDisableFlags_e flag = getArmingDisableFlags();
	// unset ARMING_DISABLED_MSP
    if (flag & ARMING_DISABLED_MSP) {
        if (flag & ARMING_DISABLED_ARM_SWITCH) {
            return true;
        }
    }

    return ARMING_FLAG(ARMED);
}

#define se_armingDisableFlags_e             armingDisableFlags_e
#define SE_getBoxIdState                    getBoxIdState
#define SE_SET_ARMING_DISABLED_BOXSHOCK     setArmingDisabled(ARMING_DISABLED_BOXSHOCK)
#define SE_CLR_ARMING_DISABLED_BOXSHOCK     unsetArmingDisabled(ARMING_DISABLED_BOXSHOCK)
#define SE_GET_ARMING_FLAG				    get_arming_flag()


#define se_acc_1G_rec                       acc.dev.acc_1G_rec
#define se_shock_acc_thr_mul                (acc.dev.acc_1G * 0.01)

#endif 

#ifdef SE_INAV
#define se_armingDisableFlags_e             armingFlag_e
#define SE_getBoxIdState                    IS_RC_MODE_ACTIVE
#define SE_SET_ARMING_DISABLED_BOXSHOCK     ENABLE_ARMING_FLAG(ARMING_DISABLED_BOXSHOCK)
#define SE_CLR_ARMING_DISABLED_BOXSHOCK     DISABLE_ARMING_FLAG(ARMING_DISABLED_BOXSHOCK)
#define SE_GET_ARMING_FLAG				    ARMING_FLAG(ARMED)

#define SE_GET_ARMING_DISABLED_ARM_SWITCH   ARMING_FLAG(ARMING_DISABLED_ARM_SWITCH)

#define se_acc_1G_rec                       1.0f
#define se_shock_acc_thr_mul                0.01f
#endif 

//se_armingDisableFlags_e armingDisableFlags4;

seShockValues_t Shock;

void seShockInit(void) {
	Shock.init = false;
	Shock.enable = false;
	Shock.acc_thr = 0;
	Shock.acc_max = 0;
	Shock.pinio_index = 0;
	Shock.isOn = false;
    Shock.accADC_max = 0;
    Shock.box = findBoxByPermanentId(seConfig()->shock_box_permanentid);
    Shock.arm_isOn = false;
    Shock.box_isOn = false;
}
uint8_t seShockGetBoxId(void) {
    return Shock.box->boxId;
}

void seShockSetEnable(int pinio_index, boxId_e boxid) {
	Shock.acc_thr = seConfig()->shock_acc_thr * se_shock_acc_thr_mul;
	Shock.pinio_index = pinio_index;

    Shock.arm_isOn = SE_GET_ARMING_FLAG;
    Shock.box_isOn = SE_getBoxIdState(boxid);

	if (Shock.init) {
		SE_CLR_ARMING_DISABLED_BOXSHOCK;

        bool enable = true;

		if (Shock.box_isOn == false) {
			enable = false;
            Shock.acc_max = 0;
		}

		if (Shock.arm_isOn == false) {
			enable = false;
		}

    	if ((Shock.box_isOn == true) && (Shock.arm_isOn == false)) {
            Shock.init = false;
        }

		uint32_t tickUptime = millis();
		if (enable) {
			if (Shock.enableOnTick > tickUptime) {
				enable = false;
			}
		} else {
			Shock.enableOnTick = tickUptime + seConfig()->shock_delay_ms;
		}

		Shock.enable = enable;

		if (Shock.enable == false) {
			pinioSet(Shock.pinio_index, false);
			Shock.isOn = false;
		}
	} else {
		if (Shock.box_isOn == false) {
			Shock.init = true;
		} else {
            SE_SET_ARMING_DISABLED_BOXSHOCK;
        }
	}

	// debug
	Shock.GForce = Shock.accADC_max * se_acc_1G_rec;
	DEBUG_SET(DEBUG_SHOCK, 0, Shock.GForce * 100);
	DEBUG_SET(DEBUG_SHOCK, 1, Shock.enable);
	DEBUG_SET(DEBUG_SHOCK, 2, pinioGet(Shock.pinio_index));

	//debug[0] = seGForce * 100; //  / 3 * 100
	//debug[1] = Shock.enable;
	//debug[2] = pinioGet(Shock.pinio_index);
	Shock.accADC_max = 0;
}

void seShockUpdate(float accADCf) {
    float max = ABS(accADCf);
    if (Shock.accADC_max < max) {
        Shock.accADC_max = max;
    }

	if ((Shock.enable) && (!Shock.isOn)) {
		if (Shock.accADC_max > Shock.acc_thr) {
			Shock.isOn = true;
			Shock.acc_max = Shock.accADC_max;
			pinioSet(Shock.pinio_index, true);
			//debug[0] = acc.accADC_max * acc.dev.acc_1G_rec * 100;
			//DEBUG_SET(DEBUG_SHOCK, 0, acc.accADC_max * acc.dev.acc_1G_rec * 100);
		}
	}
}
// END SHOCK SENSOR
