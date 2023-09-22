
#ifndef CONFIG_H
#define CONFIG_H
#include <string.h>
#include <preferences.h>

using namespace std;
#define CONFIG_CB5_SOFTWARE_VERSION "2.0.0"

#define CONFIG_SERIAL_BAUD_RATE 115200
#define CONFIG_GPS_MAX_SETUP_VALID_DATA_RETRIES 60
#define CONFIG_DEFAULT_DEVICE_NAME "CB5_DEV"
#define CONFIG_PREFERENCES_DEVICE_NAME_KEY "DEVICE_NAME"
#define CONFIG_PROJECT_NAME "CB5"

#define CONFIG_lcd_COLUMNS_LENGTH 16

#define CONFIG_POISON_APPLICATORS 3
#define CONFIG_DOSE_APPLICATION_TIMEOUT 7000
#define CONFIG_SPIN_DIRECTION_CLOCKWISE 0
#define CONFIG_SPIN_DIRECTION_ACLOCKWISE 1

#define CONFIG_PROTOCOL_IDENTIFIER "INF"
#define CONFIG_PROTOCOL_ANY_VALUE_VALID "ANY_VALUE"
#define CONFIG_PROTOCOL_STRING_LENGTH 14
#define CONFIG_PROTOCOL_DATA_START_INDEX 4
#define CONFIG_PROTOCOL_DATA_END_INDEX 7
#define CONFIG_PROTOCOL_IDENTIFIER_START_INDEX 0
#define CONFIG_PROTOCOL_IDENTIFIER_END_INDEX 3
#define CONFIG_PROTOCOL_DO_NOT_DOSE 'N'
#define CONFIG_PROTOCOL_DO_NOT_RENAME 'N'
#define CONFIG_PROTOCOL_CR '\r'
#define CONFIG_PROTOCOL_LF '\n'
#define CONFIG_PROTOCOL_STATUS_ERROR 'E'
#define CONFIG_PROTOCOL_RESPONSE_HEADER "&5"

#define CONFIG_GPS_TIMEOUT 2000
#define CONFIG_GPS_SETUP_TIMEOUT 10000
#define CONFIG_GPS_MAX_SETUP_RETRIES 5
#define CONFIG_GPS_SETUP_RETRY_INTERVAL 15000
#define CONFIG_GPS_SERIAL_BAUD_RATE 19200
#define CONFIG_GPS_MESSAGE_LENGTH 68
#define CONFIG_GPS_START_HEADER "$GPRMC"

#define CONFIG_PORT_GPIO_GPS_RX 16
#define CONFIG_PORT_GPIO_GPS_TX 17
#define CONFIG_PORT_GPIO_MOTOR_RIGHT 25
#define CONFIG_PORT_GPIO_MOTOR_CENTER 26
#define CONFIG_PORT_GPIO_MOTOR_LEFT 33
#define CONFIG_PORT_GPIO_SENSOR_APPLICATOR_RIGHT 27
#define CONFIG_PORT_GPIO_SENSOR_APPLICATOR_CENTER 34
#define CONFIG_PORT_GPIO_SENSOR_APPLICATOR_LEFT 35
#define CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_RIGHT 13
#define CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_CENTER 18
#define CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_LEFT 19

struct CONFIG
{
    string UBLOX_SETUP_DISABLE_GLL = "$PUBX,40,GLL,0,0,0,0,0,0*5C\r\n";
    string UBLOX_SETUP_DISABLE_GSV = "$PUBX,40,GSV,0,0,0,0,0,0*59\r\n";
    string UBLOX_SETUP_DISABLE_GSA = "$PUBX,40,GSA,0,0,0,0,0,0*4E\r\n";
    string UBLOX_SETUP_DISABLE_GGA = "$PUBX,40,GGA,0,0,0,0,0,0*5A\r\n";
    string UBLOX_SETUP_DISABLE_VTG = "$PUBX,40,VTG,0,0,0,0,0,0*5E\r\n";
    string UBLOX_SETUP_DISABLE_ZDA = "$PUBX,40,ZDA,0,0,0,0,0,0*44\r\n";
    string UBLOX_SETUP_SET_SERIAL_BAUD_19200 = "$PUBX,41,1,3,3,19200,0*21\r\n";
    char UBLOX_SETUP_SET_10HZ[17] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0x64, 0x00, 0x01, 0x00, 0x01, 0x00, 0x7A, 0x12, 0x0D, 0x0A};
    char UBLOX_SETUP_SET_10HZ_1[15] = {0xB5, 0x62, 0x06, 0x04, 0x04, 0x00, 0xFF, 0x87, 0x00, 0x00, 0x94, 0xF5, 0x0D, 0x0A};
    string PROTOCOL_ALLOWED_ELEMENTS_VALUES[CONFIG_PROTOCOL_STRING_LENGTH] = {"I", "N", "F", "5", "N1234567890", "01", "01", "01", "N1234567890", "N1234567890", "N1234567890", CONFIG_PROTOCOL_ANY_VALUE_VALID, to_string(CONFIG_PROTOCOL_CR), to_string(CONFIG_PROTOCOL_LF)};
    unsigned char PORT_GPIO_SENSOR_CONNECTED_APPLICATORS[CONFIG_POISON_APPLICATORS] = {CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_RIGHT, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_CENTER, CONFIG_PORT_GPIO_SENSOR_CONNECTED_APPLICATOR_LEFT};
};

#endif