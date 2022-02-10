/*
  Embedded Software (B31DG)
  Assignment 1
  Hannah Mokhberi
  10/02/2022
*/

//test using LEDs:
//byte NumPls = 5;                     //No. pulses in block, normal mode
//byte ModNumPls = 3;                  //No. pulses in block, mode 1
//unsigned int width_us = 1E6;         //width of 1st pulse(s)
//unsigned int extend_us = 1E6;        //addition to the next pulse width(s)
//unsigned int PlsGap_us = 1E6;        //gap between pulses(s)
//unsigned int BlckGap_us = 2E6;       //gap between blocks(s)

//test using oscilloscope:
byte NumPls = 15;               //No. pulses in block, normal mode
byte ModNumPls = 12;            //No. pulses in block, mode 1
unsigned int width_us = 1300;   //width of 1st pulse(µs)
unsigned int extend_us = 50;    //addition to the next pulse width(µs)
unsigned int PlsGap_us = 1200;  //gap between pulses(µs)
unsigned int BlckGap_us = 400;  //gap between blocks(µs)

byte LEDgren = 21;  //LED green connected to pin 21
byte LEDred = 15;   //LED red connected to pin 15

byte SW1 = 22;      //switch 1 connected to pin 22
byte SW2 = 23;      //switch 2 connected to pin 23

byte Num;                       //holds No. pulses in block depending on mode
unsigned int delai;             //Signal A's pulse widths

void setup()
{
  Serial.begin(9600); //set the data rate in bits per second (baud) for serial data transmission

  pinMode(LEDred, OUTPUT);  //configure pin 15 to behave as an output
  pinMode(LEDgren, OUTPUT); //configure pin 21 to behave as an output

  digitalWrite(LEDred, LOW);  //have the red LED initially off
  digitalWrite(LEDgren, LOW); //have the green LED initially off

  pinMode(SW1, INPUT); //configure pin 22 to behave as an input
  pinMode(SW2, INPUT); //configure pin 23 to behave as an input
}

void loop()
{
  if (HIGH == digitalRead(SW1)) //if SW1 pressed, stop stream
  {
    Serial.println("Stream disabled");
    digitalWrite(LEDred, LOW);  //turn off red LED
    digitalWrite(LEDgren, LOW); //turn off green LED
  }

  else {    //SW1 has not been pressed so start/ continue with the stream

    if (HIGH == digitalRead(SW2)) //if SW2 pressed, change to mode 1
    {
      //Serial.println("mode 1");
      Num = ModNumPls;
    }
    else {             //SW2 has not been pressed so change to continue in normal mode
      Num = NumPls;
    }
    digitalWrite(LEDgren, HIGH);     //green LED ON
    //Serial.println("green on");
    delayMicroseconds(extend_us);    //keep it on for 'extend_us' seconds
    digitalWrite(LEDgren, LOW);      //green LED OFF

    for (int i = 0; i <= (Num - 1); i++) //Num pulses in a block, loop Num-1 times, Num determined by mode
    {
      //calculate the width for each pulse in signal A
      delai = width_us + (i * extend_us); //for 1st iteration, i = 0 therefore extend_us = 0

      //Serial.println(i);
      digitalWrite(LEDred, HIGH);   //red LED ON
      //Serial.println("red ON");
      delayMicroseconds(delai); //keep ON for 'delai' seconds
      digitalWrite(LEDred, LOW); //red LED OFF
      delayMicroseconds(PlsGap_us); //wait until next pulse
    }
    delayMicroseconds(BlckGap_us);//'gap between blocks
  }

}
