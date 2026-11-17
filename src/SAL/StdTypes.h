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

#define MOTION_INIT_VALUE 0.0f
typedef enum {
    EMOTION_START_UP,
    EMOTION_WAKEUP_OPEN_EYES,
    EMOTION_WAKEUP_LOOK_LEFT,
    EMOTION_WAKEUP_LOOK_RIGHT,
    EMOTION_WAKEUP_YAWN,
    EMOTION_IDLE,
    EMOTION_HAPPY,
    EMOTION_ANGRY,
    EMOTION_TICKLED,
    EMOTION_SUPPRISED
} EMOTION;

typedef enum {
    EMOTION_TASK_INIT,
    EMOTION_TASK_PENDING,
    EMOTION_TASK_DONE,
} EMOTION_STATE;

typedef enum {
    MOTION_IDLE,
    MOTION_INIT,
    MOTION_INPROGRESS,
    MOTION_DONE,
} MOTION_STATE;

typedef enum {
    DISPLAY_IDLE,
    DISPLAY_INIT,
    DISPLAY_INPROGRESS,
    DISPLAY_DONE,
} DISPLAY_STATE;

typedef enum {
    AUDIO_PLAYER_IDLE,
    AUDIO_PLAYER_INIT,
    AUDIO_PLAYER_INPROGRESS,
    AUDIO_PLAYER_DONE,
} AUDIO_PLAYER_STATE;

typedef enum {
    MOTOR_HEAD,
    MOTOR_BODY,
    MOTOR_ARM_LEFT,
    MOTOR_ARM_RIGHT,
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
    int currentAngle;
    int startAngle;
    int targetAngle;
    int progress;
    int speed;
} ServoParam;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} DisplayParam;

typedef struct {
    char audioFile[128];
} AudioParam;

#endif // STDTYPES_H
