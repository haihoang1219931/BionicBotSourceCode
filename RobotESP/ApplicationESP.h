#ifndef APPLICATIONESP_H
#define APPLICATIONESP_H

#include "ApplicationController.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "driver/ledc.h"
#include "esp_lcd_panel_ops.h"
#include "esp_timer.h"
#include <cstdint>

class ApplicationESP : public ApplicationController {
public:
    ApplicationESP(i2c_port_num_t i2cPort = I2C_NUM_0,
                   gpio_num_t sdaPin = GPIO_NUM_8,
                   gpio_num_t sclPin = GPIO_NUM_9,
                   uint8_t i2cAddr = 0x3C,
                   bool rotate180 = true);
    virtual ~ApplicationESP();

    // Overrides from ApplicationController
    void initRobot() override;
    int printf(const char *fmt, ...) override;
    void msleep(int millis) override;
    long getSystemTime() override;
    void enableHardwareTimer(bool enable) override;
    void enableMotor(MOTOR motorID, bool enable) override;
    void setMotorAngle(MOTOR motorID, int angle) override;

    void renderOled();

private:
    void initOled();
    void initServos();
    void initTimer60Hz();
    uint32_t angleToDuty(int angle) const;
    static void onTimer60Hz(void *arg);

    i2c_port_num_t m_i2cPort;
    gpio_num_t m_sdaPin;
    gpio_num_t m_sclPin;
    uint8_t m_i2cAddr;
    bool m_rotate180;

    esp_lcd_panel_handle_t m_panelHandle = nullptr;
    uint8_t m_ssd1306Buffer[128 * 64 / 8]{};
    esp_timer_handle_t m_timer60Hz = nullptr;
    static constexpr const char *TAG = "ApplicationESP";
};

#endif // APPLICATIONESP_H
