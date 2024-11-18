#ifndef INVERTER_LIBRARY
#define INVERTER_LIBRARY

#include <CAN/CAN_Adafruit.hpp>
#include <Arduino.h>

// class Invertor {
//   public:
//   void hello_world() {
//     Serial.println("hello world");
//   }
// };

/**
 * class for an inverter
 */

class Invertor {
  public:
    /**
     * simple beginsequence for the inverter
     * @param _Inverter_ID ID from inverter in CAN_ID
     * Source: mail Unitek
     */
    void SimpleBeginSequence(int _Inverter_ID){
      LockInverter(_Inverter_ID);
      delay(1);

      UnlockInverter(_Inverter_ID); 
      delay(1);   
      }
    /**
     * beginsequence of the inverter 
     * @param _Inverter_ID ID from inverter in CAN_ID
     * @param _precharge Gives if precharge is done (true)
     * Source: mail Unitek
     */
    void BeginSequence (int _Inverter_ID, bool _precharge){
      if (!_precharge){
        LockInverter(_Inverter_ID);
        delay(1);

        CheckErrorBit(_Inverter_ID);
        delay(1);

        ReadStatusMask(_Inverter_ID);
        delay(1);
      }

      // Apply HV with precharge
      // Needs to be check what does return something from the inverters

      if (_precharge){
        ClearError(_Inverter_ID);
        delay(1);

        CheckError(_Inverter_ID);
        delay(1);

        UnlockInverter(_Inverter_ID);
        delay(1);

        ReadStatusMask(_Inverter_ID);
        delay(1);
      }
    }

    /**
     * Stop the inverter
     * @param _Inverter_ID ID from inverter in CAN_ID
     */ 
    void Stop(int _Invertor_ID);

    /**
     * lock the inverter
     * @param _Inverter_ID ID from inverter in CAN_ID
     */
    void LockInverter(int _Inverter_ID){
      Message message;
      message.id = _Inverter_ID;
      message.data_field.push_back(0x51);
      message.data_field.push_back(0x04);
      message.data_field.push_back(0x00); 

      CAN.send(message);
    }

    /**
     * clears the invertor
     * @param _Inverter_ID ID from inverter in CAN_ID
     */
    void ClearError(int _Inverter_ID){
      Message message;
      message.id = _Inverter_ID;
      message.data_field.push_back(0x8E);
      message.data_field.push_back(0x00);
      message.data_field.push_back(0x00); 

      CAN.send(message);
    }

    /**
     * Read Status, returns?
     * @param _Inverter_ID ID from inverter in CAN_ID
     */
    void ReadStatusMask(int _Inverter_ID){
      Message message;
      message.id = _Inverter_ID;
      message.data_field.push_back(0x3D);
      message.data_field.push_back(0x40);
      message.data_field.push_back(0x00); 

      CAN.send(message);
    }

    /**
     * Check for errors bit, returns?
     * @param _Inverter_ID ID from inverter in CAN_ID
     */
    void CheckErrorBit(int _Inverter_ID){
      Message message;
      message.id = _Inverter_ID;
      message.data_field.push_back(0x3D);
      message.data_field.push_back(0x40);
      message.data_field.push_back(0x00); 

      CAN.send(message);
    }

    /**
     * Checks for errors, return?
     * @param _Inverter_ID ID from inverter in CAN_ID
     */
    void CheckError(int _Inverter_ID){
      Message message;
      message.id = _Inverter_ID;
      message.data_field.push_back(0x3D);
      message.data_field.push_back(0x8F);
      message.data_field.push_back(0x00); 

      CAN.send(message);
    }

    /**
     * Unlock the inverter
     * @param _Inverter_ID ID from inverter in CAN_ID
     */
    void UnlockInverter(int _Inverter_ID){
      Message message;
      message.id = _Inverter_ID;
      message.data_field.push_back(0x51);
      message.data_field.push_back(0x00);
      message.data_field.push_back(0x00); 

      CAN.send(message);
    }

    /**
     * Enable the inverter
     */
    void Enable(int _Inverter_ID);

    /**
     * Set the speed of the motor
     * @param speed the speed of the motor
     */
    void SetSpeed(int _speed) = 0;

    /**
     * Get the speed of the motor
     * @return the speed of the motor
     */
    int GetSpeed() = 0;

    /**
     * Set the torque of the motor
     * @param _Inverter_ID ID from inverter in CAN_ID
     * @param torque the torque of the motor
     */
    void SetTorque(int _Inverter_ID , int _torque = 0){
      Message message;
      message.id = _Inverter_ID;
      message.data_field.push_back(0x90);
      message.data_field.push_back(_torque & 0xFF);
      message.data_field.push_back((_torque >>=8) & 0xFF); 

      CAN.send(message);
    }

    /**
     * Get the torque of the motor
     * @return the torque of the motor
     */
    int GetTorque() = 0;

    /**
     * Set the status of the inverter
     * @param status the status of the inverter
     */
    void SetStatus(int _status) = 0;

    /**
     * Get the status of the inverter
     * @return the status of the inverter
     */
    int GetStatus() = 0;

    /**
     * Get the temperature of the air
     * @param airTemperature the temperature of the air
     */
    void GetAirTemperature(int _airTemperature) = 0;

    /**
     * Get the temperature of the inverter
     * @return the temperature of the inverter
     */
    int GetInverterTemperature() = 0;

    /**
     * Get the temperature of the motor
     * 
     * @return the temperature of the motor
     */
    int GetMotorTemperature() = 0; 

    /**
     * Get the voltage of the DC bus
     * @return the voltage of the DC bus
     */
    int GetVdc() = 0;

    /**
     * Get the current of the motor
     * @return the current of the motor
     */
    int GetCurrent() = 0;

  private:
    CANAdafruit CAN;
    int m_speed; // speed of the motor
    int m_torque; // torque of the motor
    int m_status; // status of the inverter
    int m_airTemperature; // In degrees Celsius, the temperature of the air
    int m_inverterTemperature; // In degrees Celsius, the temperature of the inverter
    int m_motorTemperature; // In degrees Celsius, the temperature of the motor
    int m_Vdc; // Volts, the voltage of the DC bus
    int m_current; // Amps, the current of the motor
};

#endif

