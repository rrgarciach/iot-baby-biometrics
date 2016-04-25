int pinICS8007A = 0;                // ICS8007A pulse sensor output pin (output).
int pinLM35DZ = 1;                  // LM35DZ pin 2 (output).

float temp;                         // float variable to hold LM35DZ temperature's reading.

volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS.
volatile int Signal;                // holds the incoming raw data.
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // TRUE when User's live heartbeat is detected; FALSE when not a "live beat".
volatile boolean QS = false;        // becomes TRUE when Arduino finds a beat.

void setup() {
    Serial.begin(115200);           // Starts Serial communication.
}

void loop() {
    readTemperature();              // Reads LM35DZ and calculates value to be stored in temp variable.
}

void readTemperature() {
    float reading = analogRead(pinLM35DZ);
    temp = (reading/1024.0)*500;    // Reads analog input and calculates it.
}

void readPulse() {
                                    // A Heartbeat Was Found. BPM and IBI have been Determined:
    if (QS == true) {               // Quantified Self "QS" true when Arduino finds a heartbeat
        Serial.print("BPM: ");
        Serial.println(BPM);        // prints BPM for debuging.
        QS = false;                 // reset the Quantified Self flag for next time    
  }
}
