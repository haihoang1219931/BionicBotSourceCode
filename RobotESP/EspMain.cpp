#include "ApplicationESP.h"

extern "C" void app_main(void) {
    static ApplicationESP robot(I2C_NUM_0, GPIO_NUM_8, GPIO_NUM_9, 0x3C, true);
    robot.initRobot(); // Initializes OLED and starts the 60 Hz timer

    while (true) {
        // Run main state machine & motion updates
        robot.loop();
        robot.msleep(30); // Yield 30 ms to FreeRTOS watchdog & lower-priority tasks
    }
}
