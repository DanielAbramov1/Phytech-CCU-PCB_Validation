#include <Arduino.h>

#include <Adafruit_ADS1X15.h>

#define led2 12

#define sw2 36 // SENOSR_VP
#define sw3 27
#define dry_c 39 // SENSOR_VN // external switch J7

#define l_r1 33 // J9
#define l_s1 32
#define l_r2 13 // J8
#define l_s2 23

#define dac0 25 // J13
#define dac1 26 // J14

#define dt 1000

#define pulse_pin 34 //J6
int pulse_count = 0;

//Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
Adafruit_ADS1015 ads;     /* Use this for the 12-bit version */


void setup_ads()
{
  Serial.println("Hello!");

  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }


  // ------Enable when no external PS------ //
  // analogWrite(dac0,0);
  // analogWrite(dac0,120);
  // analogWrite(dac0,255);
}

void loop_ads_check()
{
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;

  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);

  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);
  volts2 = ads.computeVolts(adc2);
  volts3 = ads.computeVolts(adc3);

  Serial.println("-----------------------------------------------------------");
  Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  Serial.print("AIN1: "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
  Serial.print("AIN2: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
  Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");

  delay(dt);
}

void blink_led2 ()
{
  digitalWrite(led2,HIGH);
  delay(dt);
  digitalWrite(led2,LOW);
  delay(dt);
}

void switchs ()
{
  if(digitalRead(sw2))
    Serial.println("Switch 2 is NOT pressed");
  else
    Serial.println("Switch 2 is pressed");
    
  if(digitalRead(sw3))
    Serial.println("Switch 3 is NOT pressed");
  else
    Serial.println("Switch 3 is pressed");

  if(digitalRead(dry_c))
    Serial.println("external Switch is NOT pressed");
  else
    Serial.println("external Switch is pressed");

  delay(dt);
}

void relays()
{
  digitalWrite(l_s1,HIGH);
  digitalWrite(l_s2,HIGH);
  delay(dt/4);
  digitalWrite(l_s1,LOW);
  digitalWrite(l_s2,LOW);
  delay(dt*5);

  digitalWrite(l_r1,HIGH);
  digitalWrite(l_r2,HIGH);
  delay(dt/4);
  digitalWrite(l_r1,LOW);
  digitalWrite(l_r2,LOW);
  delay(dt*5);
}

void dac_check()
{
  analogWrite(dac0,0);
  analogWrite(dac1,0);
  delay(dt*4);

  analogWrite(dac0,155);
  analogWrite(dac1,155);
  delay(dt*4);

  analogWrite(dac0,255);
  analogWrite(dac1,255);
  delay(dt*4);
}

void pulse_counter_check()
{
  analogWrite(dac0,120); // 5v
  if(!digitalRead(pulse_pin))
  {
    pulse_count++;
  }
  Serial.println(pulse_count);
  // delay(dt/100);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led2,OUTPUT);

  pinMode(l_r1,OUTPUT);
  pinMode(l_s1,OUTPUT);
  pinMode(l_r2,OUTPUT);
  pinMode(l_s2,OUTPUT);

  pinMode(sw2,INPUT);
  pinMode(sw3,INPUT);
  pinMode(dry_c,INPUT);

  pinMode(dac0,OUTPUT);
  pinMode(dac1,OUTPUT);
  
  pinMode(pulse_pin,INPUT);

  setup_ads();
}

void loop()
{
  // Enable function that you want to check

// blink_led2 ();
// switchs ();
// relays();
// loop_ads_check();
// dac_check();
// pulse_counter_check();
}