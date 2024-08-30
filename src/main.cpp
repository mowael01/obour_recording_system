#include "WiFi.h"
#include <HTTPClient.h>
#include "time.h"
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800;
const int daylightOffset_sec = 0;
// WiFi credentials
const char *ssid = "hi";           // change SSID
const char *password = "12345678"; // change password
// Google script ID and required credentials
String GOOGLE_SCRIPT_ID = "AKfycbwof5d9S7nITuSZx3CwvmUNbP_R5tmRaYk-i1jcgX8wCFBdpP1xeOt8iP1_QNul1Phu"; // change Gscript ID
int count = 0;
void setup()
{
  delay(1000);
  Serial.begin(115200);
  delay(1000);
  // connect to WiFi
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  // WiFi.begin(ssid, password);
  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}
void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {

    String asString = "2122046";
    Serial.print("ID:");
    Serial.println(asString);
    String urlFinal = "https://script.google.com/macros/s/" + GOOGLE_SCRIPT_ID + "/exec?" + "id=" + asString;
    Serial.print("POST data to spreadsheet:");
    Serial.println(urlFinal);
    HTTPClient http;
    http.begin(urlFinal.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);
    //---------------------------------------------------------------------
    // getting response from google sheet
    String payload;
    if (httpCode > 0)
    {
      payload = http.getString();
      Serial.println("Payload: " + payload);
    }
    //---------------------------------------------------------------------
    http.end();
  }
  count++;
  delay(1000);
}
