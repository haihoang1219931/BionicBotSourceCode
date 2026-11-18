cmake_minimum_required(VERSION 3.16)

get_property(ROBOT_ESP_PROJECT_DEFINED GLOBAL PROPERTY ROBOT_ESP_PROJECT_DEFINED)

if(CMAKE_SCRIPT_MODE_FILE OR ROBOT_ESP_PROJECT_DEFINED)
    # Runs during component scan AND add_subdirectory() pass (prevents recursion)
    file(GLOB SAL_SOURCES "${CMAKE_CURRENT_LIST_DIR}/../src/SAL/*.cpp")

    idf_component_register(
        SRCS 
            "EspMain.cpp"
            "ApplicationESP.cpp"
            ${SAL_SOURCES}
        INCLUDE_DIRS 
            "."
            "../src/SAL"
        REQUIRES 
            driver
            esp_driver_ledc
            esp_lcd 
            esp_timer
    )
else()
    # Runs once on the top-level project pass
    set_property(GLOBAL PROPERTY ROBOT_ESP_PROJECT_DEFINED TRUE)

    set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}")
    set(COMPONENTS RobotESP)

    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    project(RobotESP)
endif()
