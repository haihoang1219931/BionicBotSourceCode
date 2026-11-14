#ifndef STDTYPES_H
#define STDTYPES_H

#include <stdio.h>

#define MAX_COMMAND_LENGTH 256
#define MAX_PARAMS_CHESSBOARD 4

#if defined(__linux__) || defined(_WIN32)
 #ifndef _UINT8_T_DECLARED
 #define _UINT8_T_DECLARED
 typedef unsigned char uint8_t;
 #endif

 #ifndef _UINT16_T_DECLARED
 #define _UINT16_T_DECLARED
 typedef unsigned short uint16_t;
 #endif

 #ifndef _UINT32_T_DECLARED
 #define _UINT32_T_DECLARED
 typedef unsigned int uint32_t;
 #endif
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef enum {
    EMOTION_START_UP,
    EMOTION_IDLE,
    EMOTION_HAPPY,
    EMOTION_ANGRY,
    EMOTION_TICKLED,
    EMOTION_SUPPRISED
} EMOTION_STATE;

typedef enum {
    MOTION_IDLE,
    MOTION_INIT,
    MOTION_INPROGRESS,
    MOTION_DONE,
} MOTION_STATE;

typedef enum {
    MOTOR_HEAD,
    MOTOR_ARM_LEFT,
    MOTOR_ARM_RIGHT,
    MOTOR_BODY,
    MAX_MOTOR
} MOTOR;

typedef enum {
    EYE_LEFT,
    EYE_RIGHT,
    MAX_EYE
} EYE;

typedef enum {
    TOUCH_HEAD,
    TOUCH_BELLY,
    TOUCH_BACK,
    MAX_TOUCH
} TOUCH;

typedef struct {
    float currentAngle;
    float startAngle;
    float targetAngle;
    float progress;
    float speed;
} ServoParam;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} EyeParam;

typedef struct {
    ServoParam servoLst[MAX_MOTOR];
    EyeParam eyeLst[MAX_EYE];
} Move;

#endif // STDTYPES_H
