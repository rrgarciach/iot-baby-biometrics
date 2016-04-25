#include <SoftwareSerial.h>

#define pinBtRx 2
#define pinBtTx 3
#define pinPulse 0               // ICS8007A pulse sensor output pin (output).
#define pinLM35 1                   // LM35 pin 2 (output).

SoftwareSerial bt(pinBtRx, pinBtTx);

float temp;                         // float variable to hold LM35DZ temperature's reading.

volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS.
volatile int Signal;                // holds the incoming raw data.
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // TRUE when User's live heartbeat is detected; FALSE when not a "live beat".
volatile boolean QS = false;        // becomes TRUE when Arduino finds a beat.

// Configurable variables:
int delaySecs = 5;                  // Delay time in seconds.

void setup() {
    Serial.begin(115200);           // Starts Serial communication.
    bt.begin(9600);                 // Starts Bluetooth Serial communication.
    interruptSetup();               // sets up to read Pulse Sensor signal every 2mS
}

void loop() {
    if (millis() % (delaySecs*1000) == 0) sendData();
}

void readTemperature() {
    temp = (analogRead(pinLM35)/1024.0)*500;    // Reads analog input and calculates it.    if (temp > maxTemp || temp < minTemp) {
}

void readPulse() {
    if (QS == true) {               // A Heartbeat Was Found. BPM and IBI have been Determined:
                                    // Quantified Self "QS" true when Arduino finds a heartbeat
        Serial.print("BPM: ");
        Serial.println(BPM);        // prints BPM for debuging.
        QS = false;                 // reset the Quantified Self flag for next time    
    }
}

void sendData() {
    readTemperature();              // Reads LM35DZ and calculates value to be stored in temp variable.
    readPulse();                    // Reads Pulse sensor BPM
    bt.print("t");
    bt.print(temp);
    bt.print(";");
    bt.print("p");
    bt.print(BPM);
    bt.print(";");
    bt.println();
}
