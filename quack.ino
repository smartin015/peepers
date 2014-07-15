class QuackControl
{
  public:
    
    int speakerPin; 
    volatile uint16_t sample;
    byte lastSample;
    
    QuackControl()
    {
      speakerPin = SPEAKER_PIN;
      pinMode(speakerPin, OUTPUT);
    }
    
    
    void stopPlayback()
    {
        // Disable playback per-sample interrupt.
        TIMSK1 &= ~_BV(OCIE1A);
    
        // Disable the per-sample timer completely.
        TCCR1B &= ~_BV(CS10);
    
        // Disable the PWM timer.
        TCCR2B &= ~_BV(CS10);
    
        digitalWrite(speakerPin, LOW);
    }


void playQuack()
{
    pinMode(speakerPin, OUTPUT);

    // Set up Timer 2 to do pulse width modulation on the speaker
    // pin.

    // Use internal clock (datasheet p.160)
    ASSR &= ~(_BV(EXCLK) | _BV(AS2));

    // Set fast PWM mode  (p.157)
    TCCR2A |= _BV(WGM21) | _BV(WGM20);
    TCCR2B &= ~_BV(WGM22);

    if(speakerPin==11){
        // Do non-inverting PWM on pin OC2A (p.155)
        // On the Arduino this is pin 11.
        TCCR2A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
        TCCR2A &= ~(_BV(COM2B1) | _BV(COM2B0));
        // No prescaler (p.158)
        TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

        // Set initial pulse width to the first sample.
        OCR2A = pgm_read_byte(&sounddata_data[0]);
    } else {
        // Do non-inverting PWM on pin OC2B (p.155)
        // On the Arduino this is pin 3.
        TCCR2A = (TCCR2A | _BV(COM2B1)) & ~_BV(COM2B0);
        TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0));
        // No prescaler (p.158)
        TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

        // Set initial pulse width to the first sample.
        OCR2B = pgm_read_byte(&sounddata_data[0]);
    }





    // Set up Timer 1 to send a sample every interrupt.

    cli();

    // Set CTC mode (Clear Timer on Compare Match) (p.133)
    // Have to set OCR1A *after*, otherwise it gets reset to 0!
    TCCR1B = (TCCR1B & ~_BV(WGM13)) | _BV(WGM12);
    TCCR1A = TCCR1A & ~(_BV(WGM11) | _BV(WGM10));

    // No prescaler (p.134)
    TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set the compare register (OCR1A).
    // OCR1A is a 16-bit register, so we have to do this with
    // interrupts disabled to be safe.
    OCR1A = F_CPU / SAMPLE_RATE;    // 16e6 / 8000 = 2000

    // Enable interrupt when TCNT1 == OCR1A (p.136)
    TIMSK1 |= _BV(OCIE1A);

    lastSample = pgm_read_byte(&sounddata_data[sounddata_length-1]);
    sample = 0;
    sei();
}

void test_quack() {
  Serial.println("Quack");
  delay(500);
  playQuack();
}
    
    void init_quack_idle()
    {
      
    }
    
    void update_quack_idle()
    {
      
    }
    
    void init_quack_on_delay(unsigned long quackdelay)
    {
      quackDelay = quackdelay;
      lastQuackTime = millis();
    }
    unsigned long lastQuackTime;
    unsigned long quackDelay;
    void update_quack_on_delay()
    {
      if((millis()-lastQuackTime)>quackDelay)
      {
        playQuack();
        lastQuackTime = millis();
      } 
    }
};
