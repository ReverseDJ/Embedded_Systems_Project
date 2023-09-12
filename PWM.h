//PWV.h contains all of the defines for using PWM

//PWM defines

#define PWM_PERIOD (TB3CCR0)
#define LCD_BACKLITE_DIMING (TB3CCR1)
#define LEFT_FORWARD_SPEED (TB3CCR2)
#define LEFT_REVERSE_SPEED (TB3CCR3)
#define RIGHT_FORWARD_SPEED (TB3CCR4)
#define RIGHT_REVERSE_SPEED (TB3CCR5)

#define WHEEL_OFF (0)
#define SLOW_LEFT (9400)
#define SLOW_RIGHT (10000)
#define MEDIUM_LEFT (35000)
#define MEDIUM_RIGHT (35000)
#define FAST_LEFT (50000)
#define FAST_RIGHT (50000)
#define ARC_RIGHT (19000)
#define ARC_LEFT (35000)

#define PERCENT_100 (50000)
#define PERCENT_80 (45000)
#define PERCENT_50 (25000)
#define PERCENT_30 (15000)
#define PERCENT_10 (5000)
#define PERCENT_5 (2500)

