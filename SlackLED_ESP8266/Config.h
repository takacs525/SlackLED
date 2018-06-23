
//LED Pins
#define LED_RED D1
#define LED_GREEN D2

//Wifi
const char* ssid = "FlyingIoT";
const char* password = "FlyingIoT";

//Slack
const char* host = "slack.com";
const int httpsPort = 443;
// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "c1 0d 53 49 d2 3e e5 2b a2 61 d5 9e 6f 99 0d 3d fd 8b b2 b3";

//Slack user token
//For more information visit: https://api.slack.com/docs/token-types#user
const String token = "xoxp-.....";

//Delay between the requests (sec)
const int delay_sec = 10;
