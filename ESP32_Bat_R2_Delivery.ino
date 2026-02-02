/*
  ESP32_Batt R2 Battery Voltage Monitor.
  This example code is in the public domain.
  Daniel deBeer
*/

#define BAT_SENSE 2     // Sense resistor control pin
#define ledR  16
#define ledG  17
#define ledB  18

#define ADC_Ch 35       // ADC Used for measuring the battery voltage.  The voltage is divided by 2.0 +- 1%.

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(BAT_SENSE, OUTPUT);
  Serial.begin(115200);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
     
}

double ReadVoltage(byte  pin )
{
  double reading = analogRead( pin ) ; // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
  if( reading < 1 || reading > 4095) {
    return 0 ;
   }
  // Return the voltage after fixin the ADC non-linearity
  return -0.000000000000016 * pow( reading, 4 ) + 0.000000000118171 * pow( reading, 3 )- 0.000000301211691 * pow( reading,2 )+ 0.001109019271794 * reading + 0.034143524634089 ;
} 

double x = 7600.0 ;
int i = 0 ;

#define CycleTime 50

void loop() {
  // Turning on the "Serial Plotter" tool shows the cell voltage as a graph
  digitalWrite(BAT_SENSE, HIGH);   // turn the Sense resistors on
  delay(40);  
  x = 2.0*ReadVoltage( ADC_Ch );
  Serial.println( x, 3 ) ;
  digitalWrite(ledR, LOW);
  digitalWrite(BAT_SENSE, LOW);    // turn thesense resistors off by making the voltage LOW
  
  delay(200);
  digitalWrite(ledR,HIGH );
  delay(200);
  digitalWrite(ledG, HIGH);
  delay(CycleTime);
  digitalWrite(ledR, LOW);

  delay(CycleTime);
  //digitalWrite(ledB, HIGH);
  //delay(CycleTime);
  //digitalWrite(ledB, LOW);
  //delay(CycleTime);
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
  delay(CycleTime);
  digitalWrite(ledG, LOW);
  //digitalWrite(ledG, LOW);
  //digitalWrite(ledB, LOW);
  delay(CycleTime);
}
