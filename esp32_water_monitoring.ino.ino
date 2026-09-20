#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <time.h>

// ======================================================
// WIFI CONFIGURATION
// ======================================================

#define WIFI_SSID     "rishi"
#define WIFI_PASSWORD "@@@@@@@@"

// ======================================================
// FIREBASE CONFIGURATION
// ======================================================

#define API_KEY       "AIzaSyCGIq7tiNdNSuslra07g4bbIdjYpRlfb_I"
#define DATABASE_URL  "https://poultry-water-monitoring-default-rtdb.firebaseio.com/"

// Example:
// https://your-project-default-rtdb.firebaseio.com/


// ======================================================
// SENSOR PINS
// ======================================================

#define ONE_WIRE_BUS       4
#define TURBIDITY_PIN      34
#define TDS_PIN            32
#define PH_PIN             35
#define FLOW_PIN           27


// ======================================================
// SENSOR OBJECTS
// ======================================================

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature temperatureSensor(&oneWire);


// ======================================================
// FIREBASE OBJECTS
// ======================================================

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;


// ======================================================
// FLOW SENSOR VARIABLES
// ======================================================

volatile unsigned long pulseCount = 0;

float flowRate = 0.0;
float totalLitres = 0.0;

unsigned long previousFlowMillis = 0;


// ======================================================
// DATA UPLOAD SETTINGS
// ======================================================

const unsigned long UPLOAD_INTERVAL = 120000; // 2 minutes

unsigned long previousUploadMillis = 0;


// ======================================================
// TIME CONFIGURATION
// India = UTC + 5:30
// ======================================================

const long GMT_OFFSET_SEC = 19800;
const int DAYLIGHT_OFFSET_SEC = 0;


// ======================================================
// FLOW SENSOR INTERRUPT
// ======================================================

void IRAM_ATTR flowPulse()
{
  pulseCount++;
}


// ======================================================
// CONNECT TO WIFI
// ======================================================

void connectWiFi()
{
  Serial.println();
  Serial.println("======================================");
  Serial.println("Connecting to Wi-Fi...");
  Serial.println("======================================");

  WiFi.mode(WIFI_STA);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  unsigned long startAttempt = millis();

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    Serial.print(".");

    if (millis() - startAttempt > 30000)
    {
      Serial.println();
      Serial.println("Wi-Fi connection timeout.");
      Serial.println("Restarting ESP32...");

      ESP.restart();
    }
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");

  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Signal strength: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
}


// ======================================================
// GET CURRENT TIMESTAMP
// ======================================================

String getTimestamp()
{
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo))
  {
    return "TIME_NOT_AVAILABLE";
  }

  char buffer[30];

  strftime(
    buffer,
    sizeof(buffer),
    "%Y-%m-%d %H:%M:%S",
    &timeinfo
  );

  return String(buffer);
}


// ======================================================
// UPDATE FLOW SENSOR
// ======================================================

void updateFlow()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousFlowMillis >= 1000)
  {
    noInterrupts();

    unsigned long pulses = pulseCount;

    pulseCount = 0;

    interrupts();

    // --------------------------------------------------
    // YF-S201:
    // Approximately 7.5 pulses / second = 1 L/min
    // --------------------------------------------------

    flowRate = pulses / 7.5;

    // Flow rate is L/min
    // One second represents 1/60 minute

    float litresThisSecond = flowRate / 60.0;

    totalLitres += litresThisSecond;

    previousFlowMillis = currentMillis;
  }
}


// ======================================================
// SEND DATA TO FIREBASE
// ======================================================

void uploadData()
{
  Serial.println();
  Serial.println("======================================");
  Serial.println("Reading sensors...");
  Serial.println("======================================");


  // ====================================================
  // TEMPERATURE
  // ====================================================

  temperatureSensor.requestTemperatures();

  float temperature =
    temperatureSensor.getTempCByIndex(0);


  // ====================================================
  // TURBIDITY
  // ====================================================

  int turbidityRaw =
    analogRead(TURBIDITY_PIN);

  float turbidityVoltage =
    turbidityRaw * (3.3 / 4095.0);


  // ====================================================
  // TDS
  // ====================================================

  int tdsRaw =
    analogRead(TDS_PIN);

  float tdsVoltage =
    tdsRaw * (3.3 / 4095.0);


  // ====================================================
  // PH
  // ====================================================

  int phRaw =
    analogRead(PH_PIN);

  float phVoltage =
    phRaw * (3.3 / 4095.0);


  // ----------------------------------------------------
  // IMPORTANT:
  // pH is NOT calibrated yet.
  //
  // This is only a temporary approximation.
  // Do NOT use this pH value for ML training until
  // proper calibration is completed.
  // ----------------------------------------------------

  float ph = 3.5 * phVoltage;


  // ====================================================
  // CREATE TIMESTAMP
  // ====================================================

  String timestamp =
    getTimestamp();


  // ====================================================
  // DISPLAY SENSOR VALUES
  // ====================================================

  Serial.println();
  Serial.println("--------- SENSOR DATA ---------");

  Serial.print("Timestamp: ");
  Serial.println(timestamp);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Turbidity Raw: ");
  Serial.println(turbidityRaw);

  Serial.print("Turbidity Voltage: ");
  Serial.print(turbidityVoltage, 3);
  Serial.println(" V");

  Serial.print("TDS Raw: ");
  Serial.println(tdsRaw);

  Serial.print("TDS Voltage: ");
  Serial.print(tdsVoltage, 3);
  Serial.println(" V");

  Serial.print("pH Raw: ");
  Serial.println(phRaw);

  Serial.print("pH Voltage: ");
  Serial.print(phVoltage, 3);
  Serial.println(" V");

  Serial.print("pH (UNCALIBRATED): ");
  Serial.println(ph, 2);

  Serial.print("Flow Rate: ");
  Serial.print(flowRate, 3);
  Serial.println(" L/min");

  Serial.print("Total Litres: ");
  Serial.print(totalLitres, 3);
  Serial.println(" L");


  // ====================================================
  // CREATE FIREBASE JSON
  // ====================================================

  FirebaseJson json;


  json.set(
    "timestamp",
    timestamp
  );

  json.set(
    "temperature",
    temperature
  );

  json.set(
    "turbidity_raw",
    turbidityRaw
  );

  json.set(
    "turbidity_voltage",
    turbidityVoltage
  );

  json.set(
    "tds_raw",
    tdsRaw
  );

  json.set(
    "tds_voltage",
    tdsVoltage
  );

  json.set(
    "ph_raw",
    phRaw
  );

  json.set(
    "ph_voltage",
    phVoltage
  );

  json.set(
    "ph",
    ph
  );

  json.set(
    "ph_calibrated",
    false
  );

  json.set(
    "flow_rate",
    flowRate
  );

  json.set(
    "total_litres",
    totalLitres
  );


  // ====================================================
  // UPLOAD TO FIREBASE
  // ====================================================

  Serial.println();
  Serial.println("Uploading to Firebase...");


  if (Firebase.ready())
  {

    if (
      Firebase.RTDB.pushJSON(
        &fbdo,
        "/water_monitoring/records",
        &json
      )
    )
    {
      Serial.println("======================================");
      Serial.println("UPLOAD SUCCESSFUL!");
      Serial.println("======================================");

      Serial.print("Firebase Path: ");
      Serial.println(fbdo.dataPath());

      Serial.print("Record ID: ");
      Serial.println(fbdo.pushName());

    }
    else
    {
      Serial.println("======================================");
      Serial.println("FIREBASE UPLOAD FAILED");
      Serial.println("======================================");

      Serial.println(
        fbdo.errorReason()
      );
    }

  }
  else
  {
    Serial.println(
      "Firebase is not ready."
    );
  }
}


// ======================================================
// SETUP
// ======================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("======================================");
  Serial.println("AI POULTRY WATER MONITORING SYSTEM");
  Serial.println("======================================");


  // ====================================================
  // SENSOR INITIALIZATION
  // ====================================================

  temperatureSensor.begin();

  pinMode(TURBIDITY_PIN, INPUT);

  pinMode(TDS_PIN, INPUT);

  pinMode(PH_PIN, INPUT);

  pinMode(FLOW_PIN, INPUT_PULLUP);


  // ====================================================
  // FLOW INTERRUPT
  // ====================================================

  attachInterrupt(
    digitalPinToInterrupt(FLOW_PIN),
    flowPulse,
    RISING
  );


  // ====================================================
  // WIFI
  // ====================================================

  connectWiFi();


  // ====================================================
  // NTP TIME
  // ====================================================

  configTime(
    GMT_OFFSET_SEC,
    DAYLIGHT_OFFSET_SEC,
    "pool.ntp.org",
    "time.nist.gov"
  );


  Serial.println();
  Serial.println("Synchronizing time...");

  struct tm timeinfo;

  if (getLocalTime(&timeinfo))
  {
    Serial.println("Time synchronized!");

    Serial.print("Current time: ");
    Serial.println(getTimestamp());
  }
  else
  {
    Serial.println(
      "Time synchronization failed."
    );
  }


  // ====================================================
  // FIREBASE CONFIGURATION
  // ====================================================

  config.api_key =
    API_KEY;

  config.database_url =
    DATABASE_URL;


  // ====================================================
  // FIREBASE AUTHENTICATION
  // ====================================================

  Serial.println();
  Serial.println("Connecting to Firebase...");


  if (
    Firebase.signUp(
      &config,
      &auth,
      "",
      ""
    )
  )
  {
    Serial.println(
      "Anonymous authentication successful!"
    );
  }
  else
  {
    Serial.println(
      "Anonymous authentication failed."
    );

    Serial.println(
      config.signer.signupError.message.c_str()
    );
  }


  // ====================================================
  // START FIREBASE
  // ====================================================

  Firebase.begin(
    &config,
    &auth
  );

  Firebase.reconnectWiFi(true);


  // ====================================================
  // INITIAL TIMERS
  // ====================================================

  previousFlowMillis = millis();

  // Upload first dataset shortly after startup
  previousUploadMillis =
    millis() - UPLOAD_INTERVAL;


  Serial.println();
  Serial.println("======================================");
  Serial.println("SYSTEM READY");
  Serial.println("======================================");
}


// ======================================================
// LOOP
// ======================================================

void loop()
{

  // ====================================================
  // CHECK WIFI
  // ====================================================

  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(
      "Wi-Fi disconnected."
    );

    connectWiFi();
  }


  // ====================================================
  // UPDATE FLOW EVERY SECOND
  // ====================================================

  updateFlow();


  // ====================================================
  // UPLOAD EVERY 2 MINUTES
  // ====================================================

  if (
    millis() - previousUploadMillis
    >= UPLOAD_INTERVAL
  )
  {

    previousUploadMillis =
      millis();

    uploadData();
  }


  delay(10);
}