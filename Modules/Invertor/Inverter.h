/**
 * Abstract class for an inverter
 */
class Inverter {
  public:
    /**
     * Start the inverter
     */
    virtual void Start(int _Invertor_ID);

    /**
     * Stop the inverter
     */ 
    virtual void Stop(int _Invertor_ID);

    /**
     * Enable the inverter
     */
    virtual void Enable(int _Invertor_ID);

    /**
     * Set the speed of the motor
     * @param speed the speed of the motor
     */
    virtual void SetSpeed(int _speed) = 0;

    /**
     * Get the speed of the motor
     * @return the speed of the motor
     */
    virtual int GetSpeed() = 0;

    /**
     * Set the torque of the motor
     * @param torque the torque of the motor
     */
    virtual void SetTorque(int _torque) = 0;

    /**
     * Get the torque of the motor
     * @return the torque of the motor
     */
    virtual int GetTorque() = 0;

    /**
     * Set the status of the inverter
     * @param status the status of the inverter
     */
    virtual void SetStatus(int _status) = 0;

    /**
     * Get the status of the inverter
     * @return the status of the inverter
     */
    virtual int GetStatus() = 0;

    /**
     * Get the temperature of the air
     * @param airTemperature the temperature of the air
     */
    virtual void GetAirTemperature(int _airTemperature) = 0;

    /**
     * Get the temperature of the inverter
     * @return the temperature of the inverter
     */
    virtual int GetInverterTemperature() = 0;

    /**
     * Get the temperature of the motor
     * 
     * @return the temperature of the motor
     */
    virtual int GetMotorTemperature() = 0; 

    /**
     * Get the voltage of the DC bus
     * @return the voltage of the DC bus
     */
    virtual int GetVdc() = 0;

    /**
     * Get the current of the motor
     * @return the current of the motor
     */
    virtual int GetCurrent() = 0;

  private:
    int m_speed; // speed of the motor
    int m_torque; // torque of the motor
    int m_status; // status of the inverter
    int m_airTemperature; // In degrees Celsius, the temperature of the air
    int m_inverterTemperature; // In degrees Celsius, the temperature of the inverter
    int m_motorTemperature; // In degrees Celsius, the temperature of the motor
    int m_Vdc; // Volts, the voltage of the DC bus
    int m_current; // Amps, the current of the motor
};

