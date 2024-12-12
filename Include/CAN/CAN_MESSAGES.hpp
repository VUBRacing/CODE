 #ifndef CAN_MESSAGES
#define CAN_MESSAGES_

/**
 * header to define usefull messages
 */

#include "CAN/CAN_ID.h"
#include "CAN/CAN_Library.hpp"

// messages for dashboard
inline const Message MESSAGE_dash_board_switch_on = {DASH_BOARD_INFO, 1, {DASH_BOARD_SWITCH_R2D_ON}};
inline const Message MESSAGE_dash_board_switch_off = {DASH_BOARD_INFO, 1, {DASH_BOARD_SWITCH_R2D_OFF}};
inline const Message MESSAGE_dash_board_button_on = {DASH_BOARD_INFO, 1, {DASH_BOARD_BUTTON_R2D_ON}};
inline const Message MESSAGE_dash_board_led_R2D_on = {DASH_BOARD_INFO, 1, {DASH_BOARD_LED_R2D_ON}};
inline const Message MESSAGE_dash_board_led_R2D_off = {DASH_BOARD_INFO, 1, {DASH_BOARD_LED_R2D_OFF}};
inline const Message MESSAGE_dash_board_led_CAN_on = {DASH_BOARD_INFO, 1, {DASH_BOARD_LED_CAN_ON}};
inline const Message MESSAGE_dash_board_led_CAN_off = {DASH_BOARD_INFO, 1, {DASH_BOARD_LED_CAN_OFF}};

// messages for precharge
inline const Message MESSAGE_precharge_on = {PRECHARGE_STATUS_ID, 1, {PRECHARGE_MESSAGE_ON}};
inline const Message MESSAGE_precharge_off = {PRECHARGE_STATUS_ID, 1, {PRECHARGE_MESSAGE_OFF}};

#endif