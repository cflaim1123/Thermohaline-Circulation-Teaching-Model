#include <FastLED.h>

#define joyX A0
#define joyY A1

#define LED_PIN1 7
#define num_LEDs1 147

#define LED_PIN2 3
#define num_LEDs2 3

#define LED_PIN3 10
#define num_LEDs3 6

#define LED_PIN4 5
#define num_LEDs4 46

#define LED_PIN5 8
#define num_LEDs5 13

#define LED_PIN6 13
#define num_LEDs6 46

uint8_t norm_val = 185;
uint8_t max_val = 255;

int xval;
int yval;

CHSVPalette16 red_blue = CHSVPalette16(
  CHSV(0, 255, norm_val), //0    red, 28°C
  CHSV(244, 255, norm_val), //16   light red
  CHSV(214, 255, norm_val), //32   pinkish purple
  CHSV(202, 255, norm_val), //48   light purple

  CHSV(192, 255, norm_val), //64   purple, 18°C
  CHSV(182, 255, norm_val), //80   bluish purple
  CHSV(172, 255, norm_val), //96   light blue
  CHSV(160, 255, norm_val), //112    blue, -1.5°C

  CHSV(160, 255, norm_val), //128    blue
  CHSV(172, 255, norm_val), //144    light blue
  CHSV(182, 255, norm_val), //175    bluish purple
  CHSV(192, 255, norm_val), //191    purple

  CHSV(202, 255, norm_val), //207    light purple
  CHSV(214, 255, norm_val), //223    pinkish purple)
  CHSV(244, 255, norm_val), //239   light red
  CHSV(0, 255, norm_val) //255   red

  );

CHSVPalette16 orange_green = CHSVPalette16(
  CHSV(96, 255, norm_val), //0  red, 33 psu
  CHSV(100, 255, norm_val), // 16
  CHSV(104, 255, norm_val), // 32
  CHSV(108, 255, norm_val), //48 

  CHSV(112, 255, norm_val), //64 yellow-orange, 34.5psu
  CHSV(116, 255, norm_val), //80
  CHSV(120, 255, norm_val),//96
  CHSV(124, 255, norm_val), //112

  CHSV(128, 255, norm_val), //128  aqua, 36psu
  CHSV(132, 255, norm_val), //144
  CHSV(136, 255, norm_val), //175
  CHSV(140, 255, norm_val), // 191

  CHSV(144, 255, norm_val), //207  purple, 37.5
  CHSV(148, 255, norm_val), //223
  CHSV(152, 255, norm_val), //239
  CHSV(156, 255, norm_val) //255 pink, 38
  );

CRGB leds1[num_LEDs1];
CRGB leds2[num_LEDs2];
CRGB leds3[num_LEDs3];
CRGB leds4[num_LEDs4];
CRGB leds5[num_LEDs5];
CRGB leds6[num_LEDs6]; 

CRGB leds_list[] = {leds1, leds2, leds3, leds4, leds5, leds6};

 
void setup() {
  
Serial.begin(9600);

xval = analogRead(joyX);
yval = analogRead(joyY);
  

/***************************************************************************************/

FastLED.addLeds<WS2812B, LED_PIN1, GRB>(leds1, num_LEDs1).setCorrection(TypicalLEDStrip);
FastLED.addLeds<WS2812B, LED_PIN2, GRB>(leds2, num_LEDs2).setCorrection(TypicalLEDStrip);
FastLED.addLeds<WS2812B, LED_PIN3, GRB>(leds3, num_LEDs3).setCorrection(TypicalLEDStrip);
FastLED.addLeds<WS2812B, LED_PIN4, GRB>(leds4, num_LEDs4).setCorrection(TypicalLEDStrip);
FastLED.addLeds<WS2812B, LED_PIN5, GRB>(leds5, num_LEDs5).setCorrection(TypicalLEDStrip);
FastLED.addLeds<WS2812B, LED_PIN6, GRB>(leds6, num_LEDs6).setCorrection(TypicalLEDStrip);

/***************************************************************************************/

initial_fill(red_blue);
init_incr_brightness();


}

/**************************************************************************************/
void loop() {
  
xval = analogRead(joyX);
yval = analogRead(joyY);

move_dot_on(1, 80, 127, true);




}




/***********************************************************************************/

void init_incr_brightness(){
  FastLED.setBrightness(10);
  FastLED.show();
  delay(500);
  
  for(int i=0; i<60;i++){
      EVERY_N_SECONDS(.9){
      FastLED.setBrightness(10+(norm_val/60)*i);
      FastLED.show();
      }
      
  }
  
  FastLED.show();
}

/***********************************************************************************/

void move_dot_on(int leds, int start, int st_p, bool sh_w) {
  if(sh_w){
    for(int i=start; i<st_p; i++){
      leds_list[leds-1, i]*=5; 
      
      FastLED.show();
      delay(200);
  
      xval = analogRead(joyX);
      yval = analogRead(joyY);
       
      pause(xval); 
      change_palette(yval); 
        
      move_dot_off(leds-1, i);
    }
  }
  else{
    for(int i=start; i<st_p; i++){
      leds_list[leds-1, i]*=5; 
      FastLED.show();
      delay(200);
      xval = analogRead(joyX);
      yval = analogRead(joyY);
       
      pause(xval); 
      change_palette(yval); 
        
      move_dot_off(leds, i);
    }
  }
}
/***********************************************************************************/


void move_dot_off(int leds, int i) {
  xval = analogRead(joyX);
  yval = analogRead(joyY); 
  
  pause(xval); 
  change_palette(yval);
  
  leds_list[leds-1,i]/=5; 
  FastLED.show();

}

/***********************************************************************************/

void move_2dots_on(int leds, int start, int st_p,int leds2, int start2, int st_p2) {

  move_dot_on(leds, start, st_p, true);
  move_dot_on(leds2, start2, st_p2, true);
      
  }


/***********************************************************************************/

void pause(int xval) {
    if(xval < 450){
      
      while(true){
        
        if(analogRead(joyY) <450){
          change_palette(analogRead(joyY));
          break;
        }
        else if(analogRead(joyY) > 650){
          change_palette(analogRead(joyY));
          break;
        }
        
        if(analogRead(joyX) >650){
          break;
        }
      }
    } 
}

/***********************************************************************************/

void change_palette(int yval) {
  
   if(yval <450){
    salinity_fill(orange_green);
    FastLED.show();
    pause(analogRead(joyX));
    }
  
  if(yval >650){
  initial_fill(red_blue);
   }

}


/***********************************************************************************/


void initial_fill(CHSVPalette16 palette) {

  //fills blue, leds1 [0-11]
    for(int i=0; i<12; i++){
        leds1[i] = ColorFromPalette(palette, 120);
    }
    
    //fills blue to red, leds1 [12-40]
    for(int i=0; i<28; i++){
      leds1[i+12] = ColorFromPalette(palette, 115 - (115/28)*i );
    }
    
    //fills pink-red to red, leds1 [41-50]
    for(int i=0; i<10; i++){
      leds1[i+40] = ColorFromPalette(palette, 0 + (32/10)*i );
    }
    
    //fills red to purple, leds1 [51-58]
    for(int i=0; i<9; i++){
      leds1[i+50] = ColorFromPalette(palette, 32 + (64/8)*i);
    }
    
    //fills purple to red, leds1 [59-69]
    for(int i=0; i<11; i++){
      leds1[i+59] = ColorFromPalette(palette, 60 - i*(60/9));
    }
    
    //fills red to purple, leds1 [70-76]
    for(int i=0; i<7; i++){
      leds1[i+70] = ColorFromPalette(palette, 0 + i*(64/7));
    }
    
    //fills purple to light blue, leds1 [77-82]
    for(int i=0; i<6; i++){
      leds1[i+77] = ColorFromPalette(palette, 64 + i*(21/6));
    }
    
    //fills red to purple, leds1 [83-93]
    for(int i=0; i<11; i++){
      leds1[i+83] = ColorFromPalette(palette, 85 + i*(30/11));
    }
    
    //fills purpl blue, leds1 [94-121]
    for(int i=0; i<27; i++){
      leds1[i+94] = ColorFromPalette(palette, 105);
    }
    
    //fills purple blue to light purple, leds1 [122-132]
    for(int i=0; i<10; i++){
      leds1[i+122] = ColorFromPalette(palette, 105 -(20/10)*i);
    }
    
    //fills light pruple to pink red, leds1 [133-146]
    for(int i=0; i<13; i++){
      leds1[i+133] = ColorFromPalette(palette, 85 - (50/13)*i);
    }
    
    //fills light blue to pink red
    for(int i=0; i<3; i++){
      leds2[i] = ColorFromPalette(palette, 110 - (75/2)*i);
    }
    
    //fills blue, leds4 and leds6
    for(int i=0; i<46; i++){
      leds4[i] = ColorFromPalette(palette, 127);  
      leds6[i] = ColorFromPalette(palette, 110); 
     }
    
    //fills full blue to light, leds5
     for(int i=0; i<13;i++){
      leds5[i] = ColorFromPalette(palette, 110 + (17/13)*i);
     }
    
    //fills light blue to purple, leds3
     for(int i=0; i<6;i++){
      leds3[i] = ColorFromPalette(palette, 110 - (62/6)*i);
 }
}

/***********************************************************************************/

void salinity_fill(CHSVPalette16 palette) {

  //fills blue, leds1 [0-32]
    for(int i=0; i<32; i++){
        leds1[i] = ColorFromPalette(palette, 64 - (64/32)*i);
    }
    
    //fills pink-red to red, leds1 [33-50]
    for(int i=0; i<20; i++){
      leds1[i+32] = ColorFromPalette(palette, 0 + (128/20)*i );
    }
    
    //fills red to purple, leds1 [51-58]
    for(int i=0; i<8; i++){
      leds1[i+51] = ColorFromPalette(palette, 128);
    }
    
    //fills purple to red, leds1 [59-69]
    for(int i=0; i<6; i++){
      leds1[i+59] = ColorFromPalette(palette, 128 + (128/5)*i);
    }

    for(int i=0; i<5; i++){
      leds1[i+64] = ColorFromPalette(palette, 255);
    }
    
    //fills red to purple, leds1 [70-76]
    for(int i=0; i<9; i++){
      leds1[i+69] = ColorFromPalette(palette, 255 - i*(255/7));
    }
    
    //fills purple to light blue, leds1 [77-79]
    for(int i=0; i<3; i++){
      leds1[i+77] = ColorFromPalette(palette, i*(128/6));
    }
    
    //fills red to purple, leds1 [80-93]
    for(int i=0; i<14; i++){
      leds1[i+80] = ColorFromPalette(palette, 64);
    }
    
    //fills purpl blue, leds1 [94-121]
    for(int i=0; i<27; i++){
      leds1[i+94] = ColorFromPalette(palette, 64);
    }
    
    //fills purple blue to light purple, leds1 [122-132]
    for(int i=0; i<10; i++){
      leds1[i+122] = ColorFromPalette(palette, 64 + (40/10)*i);
    }
    
    //fills light pruple to pink red, leds1 [133-146]
    for(int i=0; i<13; i++){
      leds1[i+133] = ColorFromPalette(palette, 104 - (20/13)*i);
    }
    
    //fills light blue to pink red
    for(int i=0; i<3; i++){
      leds2[i] = ColorFromPalette(palette, 64 + (64/2)*i);
    }
    
    //fills blue, leds4 and leds6
    for(int i=0; i<46; i++){
      leds4[i] = ColorFromPalette(palette, 64);  
      leds6[i] = ColorFromPalette(palette, 0); 
     }
         
    //fills full blue to light, leds5
     for(int i=0; i<13;i++){
      leds5[i] = ColorFromPalette(palette, 64 - (64/13)*i);
     }
    
    //fills light blue to purple, leds3
     for(int i=0; i<6;i++){
      leds3[i] = ColorFromPalette(palette, 32 + (128/6)*i);
 }
}
