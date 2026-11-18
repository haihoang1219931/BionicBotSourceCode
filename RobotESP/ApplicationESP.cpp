#include "ApplicationESP.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ssd1306.h"
#include "esp_log.h"
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <math.h>
#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif
static const char *TAG = "ApplicationESP";
constexpr uint32_t I2C_CLK_HZ = 800000;
constexpr uint64_t TIMER_60HZ_US = 16667; // 60 Hz = 16.667 ms

// Servo LEDC PWM Settings (50 Hz, 14-bit resolution)
constexpr ledc_mode_t SERVO_LEDC_MODE        = LEDC_LOW_SPEED_MODE;
constexpr ledc_timer_t SERVO_LEDC_TIMER      = LEDC_TIMER_0;
constexpr ledc_timer_bit_t SERVO_DUTY_RES    = LEDC_TIMER_14_BIT;
constexpr uint32_t SERVO_FREQ_HZ             = 50;
constexpr uint32_t SERVO_MAX_DUTY            = (1 << 14) - 1; // 16383
constexpr uint32_t SERVO_PERIOD_US           = 20000;         // 20 ms
constexpr int SERVO_MIN_PULSE_US             = 500;
constexpr int SERVO_CENTER_PULSE_US          = 1500;
constexpr int SERVO_MAX_PULSE_US             = 2500;

// Change these GPIOs to match your ESP32-S3 servo wiring
constexpr gpio_num_t SERVO_PINS[MAX_MOTOR] = {
    GPIO_NUM_11, // MOTOR_HEAD
    GPIO_NUM_13, // MOTOR_ARM_LEFT
    GPIO_NUM_14, // MOTOR_ARM_RIGHT
    GPIO_NUM_12  // MOTOR_BODY
};
ApplicationESP::ApplicationESP(i2c_port_num_t i2cPort,
                               gpio_num_t sdaPin,
                               gpio_num_t sclPin,
                               uint8_t i2cAddr,
                               bool rotate180)
    : m_i2cPort(i2cPort),
      m_sdaPin(sdaPin),
      m_sclPin(sclPin),
      m_i2cAddr(i2cAddr),
      m_rotate180(rotate180) {
    std::memset(m_ssd1306Buffer, 0x00, sizeof(m_ssd1306Buffer));
}

ApplicationESP::~ApplicationESP() {
    if (m_timer60Hz) {
        esp_timer_stop(m_timer60Hz);
        esp_timer_delete(m_timer60Hz);
    }
}

void ApplicationESP::initRobot() {
    initOled();
    initServos();
    initTimer60Hz();
    this->printf("Robot initialized with independent %dHz OLED timer",60);
}

void ApplicationESP::initOled() {
    i2c_master_bus_handle_t i2c_bus = nullptr;
    i2c_master_bus_config_t bus_config = {};
    bus_config.clk_source = I2C_CLK_SRC_DEFAULT;
    bus_config.glitch_ignore_cnt = 7;
    bus_config.i2c_port = m_i2cPort;
    bus_config.sda_io_num = m_sdaPin;
    bus_config.scl_io_num = m_sclPin;
    bus_config.flags.enable_internal_pullup = true;
    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &i2c_bus));

    esp_lcd_panel_io_handle_t io_handle = nullptr;
    esp_lcd_panel_io_i2c_config_t io_config = {};
    io_config.dev_addr = m_i2cAddr;
    io_config.scl_speed_hz = I2C_CLK_HZ;
    io_config.control_phase_bytes = 1;
    io_config.lcd_cmd_bits = 8;
    io_config.lcd_param_bits = 8;
    io_config.dc_bit_offset = 6;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_i2c(i2c_bus, &io_config, &io_handle));

    esp_lcd_panel_ssd1306_config_t ssd1306_config;
    ssd1306_config.height = static_cast<uint8_t>(getScreenHeight());
    esp_lcd_panel_dev_config_t panel_config = {};
    panel_config.bits_per_pixel = 1;
    panel_config.reset_gpio_num = GPIO_NUM_NC;
    panel_config.vendor_config = &ssd1306_config;

    ESP_ERROR_CHECK(esp_lcd_new_panel_ssd1306(io_handle, &panel_config, &m_panelHandle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(m_panelHandle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(m_panelHandle));

    if (m_rotate180) {
        ESP_ERROR_CHECK(esp_lcd_panel_mirror(m_panelHandle, true, true));
    }

    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(m_panelHandle, true));
}

void ApplicationESP::initServos() {
    // 1. Configure shared 50 Hz LEDC timer
    ledc_timer_config_t timer_conf = {};
    timer_conf.speed_mode      = SERVO_LEDC_MODE;
    timer_conf.duty_resolution = SERVO_DUTY_RES;
    timer_conf.timer_num       = SERVO_LEDC_TIMER;
    timer_conf.freq_hz         = SERVO_FREQ_HZ;
    timer_conf.clk_cfg         = LEDC_AUTO_CLK;
    ESP_ERROR_CHECK(ledc_timer_config(&timer_conf));

    // 2. Configure one LEDC channel per motor, starting at 0 deg (1500 us center)
    uint32_t centerDuty = angleToDuty(0);
    for (int i = 0; i < static_cast<int>(MAX_MOTOR); i++) {
        ledc_channel_config_t ch_conf = {};
        ch_conf.gpio_num   = SERVO_PINS[i];
        ch_conf.speed_mode = SERVO_LEDC_MODE;
        ch_conf.channel    = static_cast<ledc_channel_t>(i);
        ch_conf.intr_type  = LEDC_INTR_DISABLE;
        ch_conf.timer_sel  = SERVO_LEDC_TIMER;
        ch_conf.duty       = centerDuty;
        ch_conf.hpoint     = 0;
        ESP_ERROR_CHECK(ledc_channel_config(&ch_conf));
    }
}

uint32_t ApplicationESP::angleToDuty(int angle) const {
    // Map signed angle (0 deg = 1500 us, -90 deg = 500 us, +90 deg = 2500 us)
    int pulseUs = SERVO_CENTER_PULSE_US + (angle * 1000) / 90;
    pulseUs = max(SERVO_MIN_PULSE_US, min(pulseUs, SERVO_MAX_PULSE_US));
    return (static_cast<uint32_t>(pulseUs) * SERVO_MAX_DUTY) / SERVO_PERIOD_US;
}

void ApplicationESP::enableMotor(MOTOR motorID, bool enable) {
    int idx = static_cast<int>(motorID);
    if (idx < 0 || idx >= static_cast<int>(MAX_MOTOR)) return;

    ledc_channel_t channel = static_cast<ledc_channel_t>(idx);

    if (enable) {
    } else {
        // 0% duty stops PWM pulses so hobby servos relax / stop holding torque
        ledc_set_duty(SERVO_LEDC_MODE, channel, 0);
        ledc_update_duty(SERVO_LEDC_MODE, channel);
    }
}

void ApplicationESP::setMotorAngle(MOTOR motorID, int angle) {
    int idx = static_cast<int>(motorID);
    if (idx < 0 || idx >= static_cast<int>(MAX_MOTOR)) return;
    ESP_LOGI(TAG, "Motor %d -> %d deg", (int)motorID, angle);
    ledc_channel_t channel = static_cast<ledc_channel_t>(idx);
    uint32_t duty = angleToDuty(angle);
    ledc_set_duty(SERVO_LEDC_MODE, channel, duty);
    ledc_update_duty(SERVO_LEDC_MODE, channel);
}

void ApplicationESP::initTimer60Hz() {
    esp_timer_create_args_t timer_args = {};
    timer_args.callback = &ApplicationESP::onTimer60Hz;
    timer_args.arg = this;
    timer_args.dispatch_method = ESP_TIMER_TASK;
    timer_args.name = "oled_60hz";

    ESP_ERROR_CHECK(esp_timer_create(&timer_args, &m_timer60Hz));
    ESP_ERROR_CHECK(esp_timer_start_periodic(m_timer60Hz, TIMER_60HZ_US));
}

// Runs independently every 16.67ms (60Hz)
void ApplicationESP::onTimer60Hz(void *arg) {
    auto *self = static_cast<ApplicationESP *>(arg);
    self->executeMotionLoop(MOTOR_HEAD);
    self->executeMotionLoop(MOTOR_ARM_LEFT);
    self->executeMotionLoop(MOTOR_ARM_RIGHT);
    self->executeMotionLoop(MOTOR_BODY);
    self->executeOledLoop();
    self->renderOled();

}

void ApplicationESP::renderOled() {
    if (!m_panelHandle) return;

    const unsigned char *src = getScreenData();
    const int width = getScreenWidth();
    const int height = getScreenHeight();
    if (!src) return;

    std::memset(m_ssd1306Buffer, 0x00, sizeof(m_ssd1306Buffer));

    const int srcBytesPerRow = width / 8;
    for (int page = 0; page < (height / 8); page++) {
        int baseY = page * 8;
        int dstRowOffset = page * width;

        for (int bit = 0; bit < 8; bit++) {
            int y = baseY + bit;
            uint8_t dstMask = 1 << bit;
            const unsigned char *srcRow = src + (y * srcBytesPerRow);

            for (int byteCol = 0; byteCol < srcBytesPerRow; byteCol++) {
                uint8_t srcByte = srcRow[byteCol];
                if (srcByte == 0) continue;

                int baseX = byteCol * 8;
                if (srcByte & 0x80) m_ssd1306Buffer[dstRowOffset + baseX + 0] |= dstMask;
                if (srcByte & 0x40) m_ssd1306Buffer[dstRowOffset + baseX + 1] |= dstMask;
                if (srcByte & 0x20) m_ssd1306Buffer[dstRowOffset + baseX + 2] |= dstMask;
                if (srcByte & 0x10) m_ssd1306Buffer[dstRowOffset + baseX + 3] |= dstMask;
                if (srcByte & 0x08) m_ssd1306Buffer[dstRowOffset + baseX + 4] |= dstMask;
                if (srcByte & 0x04) m_ssd1306Buffer[dstRowOffset + baseX + 5] |= dstMask;
                if (srcByte & 0x02) m_ssd1306Buffer[dstRowOffset + baseX + 6] |= dstMask;
                if (srcByte & 0x01) m_ssd1306Buffer[dstRowOffset + baseX + 7] |= dstMask;
            }
        }
    }

    esp_lcd_panel_draw_bitmap(m_panelHandle, 0, 0, width, height, m_ssd1306Buffer);
}

int ApplicationESP::printf(const char *fmt, ...) {
    char buf[256];
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    if (len > 0) {
        ESP_LOGI(TAG, "%s", buf);
    }
    return len;
}

void ApplicationESP::msleep(int millis) {
    if (millis > 0) {
        vTaskDelay(pdMS_TO_TICKS(millis));
    }
}

long ApplicationESP::getSystemTime() {
    return static_cast<long>(esp_timer_get_time() / 1000ULL);
}

void ApplicationESP::enableHardwareTimer(bool enable) {
    if (!m_timer60Hz) return;
    if (enable) {
        if (!esp_timer_is_active(m_timer60Hz)) {
            esp_timer_start_periodic(m_timer60Hz, TIMER_60HZ_US);
        }
    } else {
        if (esp_timer_is_active(m_timer60Hz)) {
            esp_timer_stop(m_timer60Hz);
        }
    }
}