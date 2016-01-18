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

/* Animate constance */
#define ANIM_IVL               2000

/* Animate enum */
#define ANIM_BLINK_RIGHT          0
#define ANIM_BLINK_LEFT           1
#define ANIM_BLINK_TWO            2
#define ANIM_CROSS_EYES           3
#define ANIM_LAZY_EYES            4
#define ANIM_METH_EYES            5
#define ANIM_GLOW_EYES            6
#define ANIM_IDX_MAX              6
#define ANIM_MOVE                99

/* define eyeball count */
#define EYEBALL_CNT               2
#if (EYEBALL_CNT == 2)
# define MIN_ANIM ANIM_BLINK_RIGHT
#else /* EYEBALL_CNT == 2 */
# define MIN_ANIM ANIM_BLINK_LEFT
#endif /* EYEBALL_CNT != 2 */

#endif /* __JOYSTICK_KEY_H */ 
