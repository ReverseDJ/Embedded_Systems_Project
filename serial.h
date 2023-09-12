#define RING_SIZE (32)
#define BEGINNING (0)
#define RESET     (0)
//Command names
#define PORT "AT+CIPSERVER=1,8910\r\n"
#define IP_Command "AT+CIFSR\r\n"
#define SSID_Command "AT+CWJAP?\r\n"
#define MULTICONN "AT+CIPMUX=1\r\n"
#define PING "AT+PING=\"www.google.com\"\r\n"
#define DOT "."

//Boot states
#define BOOTUP        (0)
#define SERVER        (1)
#define IP            (2)
#define END           (100)

//Commandn times
#define FIRSTCOMMAND  (4)
#define SECONDCOMMAND (12)
#define THIRDCOMMAND  (18)

//Line Following
#define START          (1)   
#define FINDING        (2) 
#define INTERCEPT      (3)
#define TURNING        (4)
#define LINE           (5)
#define CIRCLE         (6)
#define PAUSE          (7)

//Timers
#define STARTFIND      (100)
#define STARTTURN      (100)
#define STARTTRAVEL    (200)
#define STARTCIRCLE    (100)

//Color Values

#define BLVALUE        (900)
#define GRAYR          (550)
#define GRAYL          (600)
#define OFFSET         (200)

//ORIGINAL MAC ADDRESS: e8:9f:6d:e5:3e:60