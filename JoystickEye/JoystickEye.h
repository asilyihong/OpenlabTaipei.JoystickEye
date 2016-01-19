#ifndef __JOYSTICK_KEY_H
#define __JOYSTICK_KEY_H

/*
   Create LetControl object, define pin connections
   We have 2 MAX72XX for eyes.
 */
#define PIN_EYES_DIN             12
#define PIN_EYES_CS              10
#define PIN_EYES_CLK             11

/* Joystick pin */
#define X_PIN                    A1
#define Y_PIN                    A0
#define BTN_PIN                   2

/* Demostaration mode */
#define IDLE_IVL              30000 /* millsecond(s) */

/* Animate constance */
#define ANIM_IVL               2000

/* Animate enum */
#define ANIM_BLINK_SINGLE         0
#define ANIM_ROUND_SPIN           1
#define ANIM_CRAZY_SPIN           2
#define ANIM_BLINK_TWO            3
#define ANIM_CROSS_EYES           4
#define ANIM_LAZY_EYES            5
#define ANIM_METH_EYES            6
#define ANIM_GLOW_EYES            7
#define ANIM_HEART_EYES           8
#define ANIM_MOVE                99
#define ANIM_IDX_MIN              ANIM_BLINK_SINGLE
#define ANIM_IDX_MAX              ANIM_GLOW_EYES

/* define eyeball count */
#define EYEBALL_CNT               2

typedef struct _Coordinate_t
{
    int     x;
    int     y;
} Coordinate_t;
#endif /* __JOYSTICK_KEY_H */ 
