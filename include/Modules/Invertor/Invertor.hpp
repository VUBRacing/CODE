#ifndef INVERTER_LIBRARY
#define INVERTER_LIBRARY

#include <CAN/CAN_Adafruit.hpp>
#include <Arduino.h>

/**
 * class for an inverter
 */

class Invertor
{
public:
  /**
   * setup needed for the invertor
   * @param mycan pointer to main can
   */
  void setup(CANAdafruit *mycan){
    CAN = *mycan;
  }

  /**
   * simple beginsequence for the inverter
   * @param _Inverter_ID ID from inverter in CAN_ID
   * geeft geen respons van de invertor
   * Source: mail Unitek
   */
  void SimpleBeginSequence(int _Inverter_ID)
  {
    LockInverter(_Inverter_ID);
    delay(1);

    UnlockInverter(_Inverter_ID);
    delay(1);
  }

  /**
   * beginsequence of the inverter before the precharge is done
   * @param _Inverter_ID ID from inverter in CAN_ID
   *
   * Invertor antwoord op statusmask met
   * 
   * Source: mail Unitek
   */
  void BeginSequence_beforeprecharge(int _Inverter_ID)
  { 
    LockInverter(_Inverter_ID);
    delay(1);

    CheckErrorBit(_Inverter_ID);
    delay(1);

    ReadStatusMask(_Inverter_ID);
    delay(1);
  }

  /**
   * beginsequence of the invertor after the precharge is done
   * @param _Inverter_ID ID from inverter in CAN_ID
   *
   * source: mail Unitek
   */
  void BeginSequence_afterprecharge(int _Inverter_ID)
  {
    // Apply HV with precharge
    // Needs to be check what does return something from the inverters
    ClearError(_Inverter_ID);
    delay(1);

    CheckError(_Inverter_ID);
    delay(1);

    UnlockInverter(_Inverter_ID);
    delay(1);

    ReadStatusMask(_Inverter_ID);
    delay(1);
  }

  /**
   * Stop the inverter
   * @param _Inverter_ID ID from inverter in CAN_ID
   */
  void Stop(int _Inverter_ID){
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x51);
    message.data_field.push_back(0x04);
    message.data_field.push_back(0x00);
  }

  /**
   * lock the inverter
   * @param _Inverter_ID ID from inverter in CAN_ID
   * No CAN respons from the invertor
   */
  void LockInverter(int _Inverter_ID)
  {
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
   * No CAN respons from the invertor
   */
  void ClearError(int _Inverter_ID)
  {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x8E);
    message.data_field.push_back(0x00);
    message.data_field.push_back(0x00);

    CAN.send(message);
  }

  /**
   * Read Status
   * Geeft een waarde terug waarschijnelijk over de status in de invertor
   * @param _Inverter_ID ID from inverter in CAN_ID
   */
  void ReadStatusMask(int _Inverter_ID)
  {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(0x40);
    message.data_field.push_back(0x00);

    CAN.send(message);
  }

  /**
   * Check for errors bit
   * Invertor antwoord met de bit error
   *    error :
   *    No error :
   * 
   * @param _Inverter_ID ID from inverter in CAN_ID
   */
  void CheckErrorBit(int _Inverter_ID)
  {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(0x40);
    message.data_field.push_back(0x00);

    CAN.send(message);
  }

  /**
   * Checks for errors
   * Answer of the invertor
   *  Error :
   *  No error : 
   * @param _Inverter_ID ID from inverter in CAN_ID
   */
  void CheckError(int _Inverter_ID)
  {
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
   * No CAN respons of the invertor
   */
  void UnlockInverter(int _Inverter_ID)
  {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x51);
    message.data_field.push_back(0x00);
    message.data_field.push_back(0x00);

    CAN.send(message);
  }


  /**
   * Set the torque of the motor
   * @param _Inverter_ID ID from inverter in CAN_ID
   * @param torque the torque of the motor
   * No answer of the invertor
   */
  void SetTorque(int _Inverter_ID, int _torque = 0)
  {
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x90);
    message.data_field.push_back(_torque & 0xFF);
    message.data_field.push_back((_torque >>= 8) & 0xFF);

    CAN.send(message);
  }

  /**
   * Transmitting request Sending once
   *@param _Inverter_ID ID from inverter in CAN_ID
   *@param regID regbit to send, see CAN manual
   * CAN respons of the needed regValue
   */
  void Transmitting_request(int _Inverter_ID, int regID){
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(regID);
    message.data_field.push_back(0x00);
  }

  /**
   * Cycic Transmitting request
   *@param _Inverter_ID ID from inverter in CAN_ID
   *@param regID regbit to send, see CAN manual
   *@param time_interval 0-254ms time interval for transmittion
   *cyclic CAN respons of needed regValue
   */
  void Cyclic_transmitting_request(int _Inverter_ID, int regID, int time_interval){
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(regID);
    message.data_field.push_back(time_interval);
  }

    /**
   * Stop Cycic Transmitting request
   *@param _Inverter_ID ID from inverter in CAN_ID
   *No CAN respons from the inverter
   */
  void Stop_transmitting(int _Inverter_ID){
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x3D);
    message.data_field.push_back(0x00);
    message.data_field.push_back(0xff);
  }

  /**
   * Changes the transmitting adress
   * @param _Inverter_ID previous adress
   * @param adress New adress
   * No CAN respons from the inverter
   * (pls do not use)
   */
  void Change_transmitting_address(int _Inverter_ID, int adress){
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x68);
    message.data_field.push_back(adress);
  }

  void SetSpeed(int _Inverter_ID, int speed){
    Message message;
    message.id = _Inverter_ID;
    message.data_field.push_back(0x31);
    message.data_field.push_back(speed & 0xFF);
    message.data_field.push_back((speed >>= 8) & 0xFF);
  }


private:
  enum return_invertor
  {


  };

  CANAdafruit CAN;
  int m_speed;               // speed of the motor
  int m_torque;              // torque of the motor
  int m_status;              // status of the inverter
  int m_airTemperature;      // In degrees Celsius, the temperature of the air
  int m_inverterTemperature; // In degrees Celsius, the temperature of the inverter
  int m_motorTemperature;    // In degrees Celsius, the temperature of the motor
  int m_Vdc;                 // Volts, the voltage of the DC bus
  int m_current;             // Amps, the current of the motor

};

#endif
