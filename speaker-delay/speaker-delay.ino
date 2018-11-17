#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2SQuad        i2s_quad1;      //xy=177.6666603088379,299.6666774749756
AudioAnalyzePeak         peak3;          //xy=396.6666603088379,138.3333339691162
AudioAnalyzePeak         peak4;          //xy=396.6666736602783,179.99999809265137
AudioAnalyzePeak         peak1;          //xy=398.3333282470703,56.666669845581055
AudioAnalyzePeak         peak2;          //xy=398.3333206176758,96.66666889190674
AudioAnalyzeRMS          rms1;           //xy=450.0000190734863,374.9999942779541
AudioAnalyzeRMS          rms3;           //xy=449.9999771118164,456.66666412353516
AudioAnalyzeRMS          rms4;           //xy=449.9999771118164,496.6666564941407
AudioAnalyzeRMS          rms2;           //xy=451.6666666666666,418.33333333333326
AudioEffectDelayExternal delayExt1(AUDIO_MEMORY_23LC1024, 700);      //xy=693.3333053588867,135
AudioEffectDelayExternal delayExt2(AUDIO_MEMORY_23LC1024, 700);      //xy=819.3333053588867,225
AudioEffectFade          fade2;          //xy=814,224
AudioEffectFade          fade1;          //xy=823,155
AudioOutputI2SQuad       i2s_quad2;      //xy=1130.666648864746,277.6666679382324
AudioConnection          patchCord1(i2s_quad1, 0, peak1, 0);
AudioConnection          patchCord2(i2s_quad1, 0, rms1, 0);
AudioConnection          patchCord3(i2s_quad1, 0, delayExt1, 0);
AudioConnection          patchCord4(i2s_quad1, 1, peak2, 0);
AudioConnection          patchCord5(i2s_quad1, 1, rms2, 0);
AudioConnection          patchCord6(i2s_quad1, 1, delayExt2, 0);
AudioConnection          patchCord7(i2s_quad1, 2, i2s_quad2, 2);
AudioConnection          patchCord8(i2s_quad1, 2, peak3, 0);
AudioConnection          patchCord9(i2s_quad1, 2, rms3, 0);
AudioConnection          patchCord10(i2s_quad1, 3, i2s_quad2, 3);
AudioConnection          patchCord11(i2s_quad1, 3, peak4, 0);
AudioConnection          patchCord12(i2s_quad1, 3, rms4, 0);
AudioConnection          patchCord13(delayExt2, 0, fade2, 0);
AudioConnection          patchCord14(delayExt1, 0, fade1, 0);
AudioConnection          patchCord15(fade2, 0, i2s_quad2, 1);
AudioConnection          patchCord16(fade1, 0, i2s_quad2, 0);
AudioControlSGTL5000     sgtl5000_2;     //xy=112,538.0000171661377
AudioControlSGTL5000     sgtl5000_1;     //xy=131.33333587646484,442.6666507720947
// GUItool: end automatically generated code

int firstDelay = 29;
int secondDelay = 29;
//int firstDelay = 100;
//int secondDelay = 100;


void setup() {
  // put your setup code here, to run once:
  delay(250);
  AudioMemory(256); // 2.9ms per block (mono), if using internal memory
  delay(250);
  
  sgtl5000_1.setAddress(LOW);
  sgtl5000_2.setAddress(HIGH);

  // TODO - Use internal delay??? Teensy 3.6 should support a total of ~2400ms of delay

  delayExt1.delay(0, firstDelay);
  delayExt1.disable(1);
  delayExt1.disable(2);
  delayExt1.disable(3);
  delayExt1.disable(4);
  delayExt1.disable(5);
  delayExt1.disable(6);
  delayExt1.disable(7);

  delayExt2.delay(0, secondDelay);
  delayExt2.disable(1);
  delayExt2.disable(2);
  delayExt2.disable(3);
  delayExt2.disable(4);
  delayExt2.disable(5);
  delayExt2.disable(6);
  delayExt2.disable(7);

  sgtl5000_1.enable();
  sgtl5000_1.muteLineout();
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.volume(0);
  sgtl5000_1.muteHeadphone();
  sgtl5000_1.lineInLevel(0, 0);  // default 5 = 1.33Vpp
  //sgtl5000_1.lineInLevel(10, 10);  // default 5 = 1.33Vpp

  // Output from Yamaha 166CX is usually +4 dBu, and -10 dBV for REC OUT
  // Input for BOSE L1 max input +12 dBu on channel 2 (line in, set to line-level)
  // (BOSE L1 nominal output is +2.2 dBu, max +20 dBu)

  //lineInLevel(both);

/*Adjust the sensitivity of the line-level inputs. Fifteen settings are possible:

 0: 3.12 Volts p-p
 1: 2.63 Volts p-p
 2: 2.22 Volts p-p
 3: 1.87 Volts p-p
 4: 1.58 Volts p-p
 5: 1.33 Volts p-p  (default)
 6: 1.11 Volts p-p
 7: 0.94 Volts p-p
 8: 0.79 Volts p-p
 9: 0.67 Volts p-p
10: 0.56 Volts p-p
11: 0.48 Volts p-p
12: 0.40 Volts p-p
13: 0.34 Volts p-p
14: 0.29 Volts p-p
15: 0.24 Volts p-p */


/*
lineInLevel(both);

Adjust the sensitivity of the line-level inputs. Fifteen settings are possible:

13: 3.16 Volts p-p
14: 2.98 Volts p-p
15: 2.83 Volts p-p
16: 2.67 Volts p-p
17: 2.53 Volts p-p
18: 2.39 Volts p-p
19: 2.26 Volts p-p
20: 2.14 Volts p-p
21: 2.02 Volts p-p
22: 1.91 Volts p-p
23: 1.80 Volts p-p
24: 1.71 Volts p-p
25: 1.62 Volts p-p
26: 1.53 Volts p-p
27: 1.44 Volts p-p
28: 1.37 Volts p-p
29: 1.29 Volts p-p  (default)
30: 1.22 Volts p-p
31: 1.16 Volts p-p*/
  
  // Use                Nominal level  Nominal level, Vrms  Peak amplitude, Vpk  Peak-to-peak amplitude, Vpp
  // Professional audio  +4 dBu        1.228                1.736                3.472
  // Consumer audio     -10 dBV        0.316                0.447                0.894
  sgtl5000_1.lineOutLevel(13, 13); // default 29 = 1.29Vpp

  // Disable auto-volume
  sgtl5000_1.adcHighPassFilterDisable(); // Freeze???
  sgtl5000_1.dacVolumeRamp();
  sgtl5000_1.dacVolume(1.0);
  sgtl5000_1.audioProcessorDisable();
  delay(250);
  sgtl5000_1.unmuteLineout();

  
  sgtl5000_2.enable();
  sgtl5000_2.muteLineout();
  sgtl5000_2.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_2.volume(0);
  sgtl5000_2.muteHeadphone();
  sgtl5000_2.lineInLevel(0, 0); // default 5
  sgtl5000_2.lineOutLevel(13, 13); // default 29
  // Disable auto-volume
  sgtl5000_2.adcHighPassFilterDisable(); // Freeze???
  sgtl5000_2.dacVolumeRamp();
  sgtl5000_2.dacVolume(1.0);
  sgtl5000_2.audioProcessorDisable();
  delay(250);
  sgtl5000_2.unmuteLineout();

  usbMIDI.setHandleControlChange(OnControlChange);
}


elapsedMillis fps;
uint8_t cnt=0;

void loop() {
  // put your main code here, to run repeatedly:
  delay(5);
  usbMIDI.read();

  if(fps > 50) {
    if (peak1.available() && peak2.available() && peak3.available() && peak4.available() 
        && rms1.available() && rms2.available() && rms3.available() && rms4.available()) {
      fps=0;
      float p1 = peak1.read() * 150.0;
      uint8_t PeakChars1 = p1 / 10.0;
      float p2 = peak2.read() * 150.0;
      uint8_t PeakChars2 = p2 / 10.0;
      uint8_t PeakChars3 = peak3.read() * 15.0;
      uint8_t PeakChars4 = peak4.read() * 15.0;
      float g = rms2.read() * 150.0;
      uint8_t RmsChars1 = rms1.read() * 15.0;
      uint8_t RmsChars2 = g / 10.0;
      uint8_t RmsChars3 = rms3.read() * 15.0;
      uint8_t RmsChars4 = rms4.read() * 15.0;

      for (cnt=0; cnt < 15-PeakChars1; cnt++) {
        Serial.print(" ");
      }
      while (cnt++ < 14 && cnt < 15-RmsChars1) {
        Serial.print("<");
      }
      while (cnt++ < 15) {
        Serial.print("=");
      }
      
      Serial.print("||");
      
      for(cnt=0; cnt < RmsChars2; cnt++) {
        Serial.print("=");
      }
      for(; cnt < PeakChars2; cnt++) {
        Serial.print(">");
      }
      while(cnt++ < 15) {
        Serial.print(" ");
      }

      
      Serial.print(" ");

      
      for (cnt=0; cnt < 15-PeakChars3; cnt++) {
        Serial.print(" ");
      }
      while (cnt++ < 14 && cnt < 15-RmsChars3) {
        Serial.print("<");
      }
      while (cnt++ < 15) {
        Serial.print("=");
      }
      
      Serial.print("||");
      
      for(cnt=0; cnt < RmsChars4; cnt++) {
        Serial.print("=");
      }
      for(; cnt < PeakChars4; cnt++) {
        Serial.print(">");
      }
      while(cnt++ < 15) {
        Serial.print(" ");
      }
      Serial.print(AudioProcessorUsage());
      Serial.print("/");
      Serial.print(AudioProcessorUsageMax());
      Serial.print(" ");
      Serial.print(p2);
      Serial.print(" ");
      Serial.print(g);
      Serial.println();

      if (p1 > 2.0)
      {
        fade1.fadeIn(5);
      }
      else
      {
        fade1.fadeOut(2000);
      }
      if (p2 > 2.0)
      {
        fade2.fadeIn(5);
      }
      else
      {
        fade2.fadeOut(2000);
      }
    }
  }
}

void OnControlChange(byte channel, byte control, byte value)
{
  Serial.println("Control Change");
  Serial.println(channel);
  Serial.println(control);
  Serial.println(value);
  
  switch(control)
  {
    case 10: // Volume
      Serial.println("Volume");
      Serial.println(1.0 * value / 127.0);
      sgtl5000_1.dacVolume(1.0 * value / 127.0);
      break;
    
    case 50: // Let's just say this could be delay MSB
      if (channel == 1)
      {
        firstDelay = (firstDelay & (0x007F)) | (0x3F80 & (value << 7));
        //Serial.println("First delay");
        //Serial.println(firstDelay);
        //delayExt1.delay(0, firstDelay); // Don't update on MSB, wait until LSB
      }
      else if (channel == 2)
      {
        secondDelay = (secondDelay & (0x007F)) | (0x3F80 & (value << 7));
        //Serial.println("Second delay");
        //Serial.println(secondDelay);
        // delayExt2.delay(0, secondDelay); // Don't update on MSB, wait until LSB
      }
      break;
    case 51: // Let's just say this could be delay LSB
      if (channel == 1)
      {
        firstDelay = (firstDelay & (0x3F80)) | (0x7F & value);
        Serial.println("First delay");
        Serial.println(firstDelay);
        delayExt1.delay(0, firstDelay);
      }
      else if (channel == 2)
      {
        secondDelay = (secondDelay & (0x3F80)) | (0x7F & value);
        Serial.println("Second delay");
        Serial.println(secondDelay);
        delayExt2.delay(0, secondDelay);
      }
      break;
  }
}
