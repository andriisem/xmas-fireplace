#include <FastLED.h>

#define LED_PIN1 2 
#define LED_PIN2 3 
#define LED_PIN3 4 
#define LED_PIN4 5 
#define LED_PIN5 6 
#define LED_PIN6 7 
#define COLOR_ORDER GRB
#define CHIPSET WS2812B 
#define NUM_LEDS 15     
#define NUM_LEDSP 18    

#define T 3000

int BRIGHTNESS = 200;
int FRAMES_PER_SECOND = 40;
int showType = 0;
int D = 0;
int W = 0;
bool oldState = HIGH;
unsigned int COOLING = 300;
int SPARKING = 250;

bool gReverseDirection = false;

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];
CRGB leds5[NUM_LEDS];
CRGB leds6[NUM_LEDSP];
CRGBPalette16 gPal;

void setup()
{
    delay(2000); // техническая пауза

    FastLED.addLeds<CHIPSET, LED_PIN1, COLOR_ORDER>(leds1, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<CHIPSET, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<CHIPSET, LED_PIN3, COLOR_ORDER>(leds3, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<CHIPSET, LED_PIN4, COLOR_ORDER>(leds4, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<CHIPSET, LED_PIN5, COLOR_ORDER>(leds5, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.addLeds<CHIPSET, LED_PIN6, COLOR_ORDER>(leds6, NUM_LEDSP).setCorrection(TypicalLEDStrip);
}

void loop()
{

    gPal = CRGBPalette16(
        CRGB::Black,
        CRGB(85, 20, 0),
        CRGB(255, 135, 10),
        CRGB(185, 110, 5));

    int a = random(0, 5);   
    int b = random(0, 100); 

    if (a == 1)
    {
        showType++;
    }

    if (b == 1)
    {
        D++;
    }

    int R = random(5, 90);
    if (showType == 2)
    {
        COOLING = (300 - R);
        showType = 0;
    }

    int F = random(100, 200);
    if (D == 2)
    {
        COOLING = (300 - F);
        D = 0;
    }

    if (COOLING < 60)
    {
        COOLING = 60;
    }

    if (COOLING < 300)
    {
        W++;
        if (W == 2)
        {
            COOLING++;
        }
        if (COOLING > 300)
            COOLING = 300;
        W = 0;
    }

    int DC = map(COOLING, 60, 300, 0, 18);
    FRAMES_PER_SECOND = 40 - DC;

    int DB = map(COOLING, 60, 300, 0, 180);
    BRIGHTNESS = 255 - DB;

    FastLED.setBrightness(BRIGHTNESS);

    random16_add_entropy(random()); 

    Fire2012WithPalette();
    Fire2012WithPalette_1();
    Fire2012WithPalette_2();
    Fire2012WithPalette_3();
    Fire2012WithPalette_4();
    Fire2012WithPalette_5();

    FastLED.show(); 
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}


void Fire2012WithPalette() 
{
    static byte heat[NUM_LEDS];

    for (int i = 0; i < NUM_LEDS; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 11) / NUM_LEDS) + 2)); 
    }

    for (int k = NUM_LEDS - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3; 
    }

    if (random8() < SPARKING)
    {
        int y = random8(2);                         
        heat[y] = qadd8(heat[y], random8(20, 255)); 
    }

    for (int j = 0; j < NUM_LEDS; j++)
    {
        byte colorindex = scale8(heat[j], 200); 
        CRGB color = ColorFromPalette(gPal, colorindex);
        int pixelnumber;
        if (gReverseDirection)
        {
            pixelnumber = (NUM_LEDS - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        leds1[pixelnumber] = color;
    }
}

void Fire2012WithPalette_1() 
{
    static byte heat[NUM_LEDS];

    for (int i = 0; i < NUM_LEDS; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2)); 
    }

    for (int k = NUM_LEDS - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3; 
    }

    if (random8() < SPARKING)
    {
        int y = random8(2);                         
        heat[y] = qadd8(heat[y], random8(20, 255)); 
    }

    for (int j = 0; j < NUM_LEDS; j++)
    {
        byte colorindex = scale8(heat[j], 200); 
        CRGB color = ColorFromPalette(gPal, colorindex);
        int pixelnumber;
        if (gReverseDirection)
        {
            pixelnumber = (NUM_LEDS - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        leds2[pixelnumber] = color;
    }
}


void Fire2012WithPalette_2() 
{
    static byte heat[NUM_LEDS];

    for (int i = 0; i < NUM_LEDS; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2)); 
    }

    for (int k = NUM_LEDS - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }

    if (random8() < SPARKING)
    {
        int y = random8(2);                          
        heat[y] = qadd8(heat[y], random8(255, 255)); 
    }

    for (int j = 0; j < NUM_LEDS; j++)
    {
        byte colorindex = scale8(heat[j], 200); 
        CRGB color = ColorFromPalette(gPal, colorindex);
        int pixelnumber;
        if (gReverseDirection)
        {
            pixelnumber = (NUM_LEDS - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        leds3[pixelnumber] = color;
    }
}


void Fire2012WithPalette_3() 
{
    static byte heat[NUM_LEDS];

    for (int i = 0; i < NUM_LEDS; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2)); 
    }

    for (int k = NUM_LEDS - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3; 
    }

    if (random8() < SPARKING)
    {
        int y = random8(2);                          
        heat[y] = qadd8(heat[y], random8(255, 255)); 
    }

    for (int j = 0; j < NUM_LEDS; j++)
    {
        byte colorindex = scale8(heat[j], 200); 
        CRGB color = ColorFromPalette(gPal, colorindex);
        int pixelnumber;
        if (gReverseDirection)
        {
            pixelnumber = (NUM_LEDS - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        leds4[pixelnumber] = color;
    }
}


void Fire2012WithPalette_4() 
{
    static byte heat[NUM_LEDS];

    for (int i = 0; i < NUM_LEDS; i++)
    {
        heat[i] = qsub8(heat[i], random8(0, ((COOLING * 10) / NUM_LEDS) + 2)); 
    }

    for (int k = NUM_LEDS - 1; k >= 2; k--)
    {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3; 
    }

    if (random8() < SPARKING)
    {
        int y = random8(2);                          
        heat[y] = qadd8(heat[y], random8(255, 255));
    }

    for (int j = 0; j < NUM_LEDS; j++)
    {
        byte colorindex = scale8(heat[j], 200); 
        CRGB color = ColorFromPalette(gPal, colorindex);
        int pixelnumber;
        if (gReverseDirection)
        {
            pixelnumber = (NUM_LEDS - 1) - j;
        }
        else
        {
            pixelnumber = j;
        }
        leds5[pixelnumber] = color;
    }
}


void Fire2012WithPalette_5() 
{

    for (int i = 0; i < NUM_LEDSP; i++)
    {

        int rf = random(50, 100);
        int gf = random(10, 25);

        leds6[i] = CRGB(rf, gf, 0);
    }
}
