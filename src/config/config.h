
#ifndef CONFIG_H
#define CONFIG_H
#include <string.h>
using namespace std;
#define POISON_APPLICATORS 3
struct CONFIG
{
    int SERIAL_BOUD_RATE = 115200, GPS_SERIAL_BOUD_RATE = 9600, PROTOCOL_STRING_LENGTH = 16, PROTOCOL_DATA_START_INDEX = 3;
    int PROTOCOL_DATA_END_INDEX = 10, PROTOCOL_IDENTIFIER_START_INDEX = 0, PROTOCOL_IDENTIFIER_END_INDEX = 3, GPS_TIMEOUT = 2000, GPS_SETUP_TIMEOUT = 10000, GPS_MAX_SETUP_RETRIES = 5, GPS_SETUP_RETRY_INTERVAL = 7000;
    string DEVICE_NAME = "CB5_DEV", PROTOCOL_IDENTIFIER = "INF", PROTOCOL_ANY_VALUE_VALID = "ANY_VALUE";
    string PROTOCOL_ALLOWED_ELEMENTS_VALUES[14] = {"I", "N", "F", "01", "N1234567890", "CN", "x", "x", "x", "x", "x", "x", "x", PROTOCOL_ANY_VALUE_VALID}, PROTOCOL_STATUS_ERROR = "E", PROTOCOL_STATUS_BUSY = "B", PROTOCOL_STATUS_STAND_BY = "S";
    char PORT_GPS_RX = 16, PORT_GPS_TX = 17;
    int PORT_MOTOR_A_1 = 1, PORT_MOTOR_B_1 = 2, PORT_SENSOR_APPLICATOR_1 = 3, SPIN_DIRECTION_CLOCKWISE = 0, SPIN_DIRECTION_ACLOCKWISE = 1, GPS_MESSAGE_LENGTH = 68; // TODO: ADJUST PORTS
    char PROTOCOL_DO_NOT_DOSE = 'N',
         PROTOCOL_DO_NOT_CLEAR_WHELL_BOLT_COUNTS = 'N', ALARM_SIREN_OFF = '0', PROTOCOL_CR = '\r', PROTOCOL_LF = '\n';
    unsigned long DOSE_APPLICATION_TIMEOUT = 1500;
};

#endif