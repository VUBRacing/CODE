 #ifndef CAN_IDs_H_
#define CAN_IDs_H_

// CAN SETUP:
// CAN0: Inverter1&2, APPS(1&2)
// CAN1:  AMS/BMS, PreCharge, BrakeLight, GPS
// CAN2: Debug/Extra
// More info: https://trello.com/c/7XiEiakx

// ID Specs
#define MAX_CAN_ID 0x7FF

// CAN BUS DEBUG/IMPORTANT SIGNALS
// ID Range: 0x000 - 0x009
// #define CAN_ERROR_ID 0x000

// PreCharge
#define PRECHARGE_STATUS_ID 0x006

// APPS Analog Values
#define APPS1_AVAL_ID 0x010 // not used new version only averge is send
#define APPS2_AVAL_ID 0x011// not used new version only averge is send
#define APPS_AVAL_ID 0x012    


// Inverters
// INV RX Range: 0x201 - 0x27F
// INV TX Range: 0x181 - 0x1FF
#define INV1_RX_ID 0x202
#define INV1_TX_ID 0x182
#define INV2_RX_ID 0x201
#define INV2_TX_ID 0x181

// BrakeSens Analog Values
#define BRAKESENS1_AVAL_ID 0x300
#define BRAKESENS2_AVAL_ID 0x301

// AMS/BMS
#define BMS_VOLTAGE_ID 0x400
#define BMS_CURRENT_ID 0x401
#define BMS_TEMP_ID 0x402

// BrakeLight
#define BL_STATUS_ID 0x500

// GPS:




#endif /* CAN_IDs_H_ */
