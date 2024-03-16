#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/power.h>

const int buttonPin = PB3;    // Change to your actual button pin
const int powerPin = PB4;     // Change to your actual power control pin
const int shutdownPin = PB1;  // Shutdown pin

volatile bool powerState = false;
volatile bool buttonPressed = false;

void setup() {
  // Set all unused pins to output to avoid floating inputs
  DDRB = 0xFF;
  PORTB = 0x00;

  // Set button pin as input without pull-up resistor (since it's pulled down)
  pinMode(buttonPin, INPUT);
  // Set shutdown pin as input without pull-up resistor (since it's pulled down)
  pinMode(shutdownPin, INPUT);

  // Disable pull-up resistors to save power
  PORTB &= ~(1 << buttonPin);
  PORTB &= ~(1 << shutdownPin);

  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, powerState);  // Start with power off

  // Disable ADC to save power
  ADCSRA &= ~(1 << ADEN);

  // Disable Analog Comparator to save power
  ACSR |= (1 << ACD);

  // Set up Pin Change Interrupt only for the button pin (PB3)
  GIMSK |= (1 << PCIE);    // Enable Pin Change Interrupts
  PCMSK |= (1 << PCINT3);  // Use PB3 (button pin) as interrupt pin
  sei();                   // Enable global interrupts
  goToSleep();
}

void loop() {
  if (buttonPressed) {
    // Handle power button press
    buttonPressed = false;  // Reset the button press flag

    if (!powerState) {
      // Device is off, turn it on
      powerState = true;
      digitalWrite(powerPin, powerState);  // Apply new power state
    } else {
      // Device is on, turn it off
      powerState = false;
      digitalWrite(powerPin, powerState);  // Apply new power state
      // Enter sleep mode
      goToSleep();
    }
  }

  // Check if shutdown pin is HIGH (PB1)
  if (digitalRead(shutdownPin) == HIGH) {
    // Shutdown requested, turn off power
    powerState = false;
    digitalWrite(powerPin, powerState);  // Apply new power state
    // Enter sleep mode
    goToSleep();
  }
  if (!powerState) {
    goToSleep();
  }
}

void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_bod_disable();  // Disable Brown-Out Detection to save power
  sei();                // Ensure interrupts are enabled so we wake up again
  sleep_cpu();          // Go to sleep
  sleep_disable();      // Wake up here
}

ISR(PCINT0_vect) {
  if (digitalRead(buttonPin) == HIGH && debounceButton()) {
    buttonPressed = true;  // Set button pressed flag
  }
}

bool debounceButton() {
  // Check button state multiple times to ensure it's stable
  for (int i = 0; i < 5; i++) {
    if (digitalRead(buttonPin) == LOW) {
      return false;  // Button is still pressed
    }
    // Set debounce delay based on the microcontroller
    #if defined(__AVR_ATtiny13__)
      delay(200);  // Delay for debounce for ATtiny13
    #else
      delay(25);   // Delay for debounce for ATtiny25/45/85
    #endif
  }
  return true;  // Button press detected
}

// Disable unnecessary interrupts
EMPTY_INTERRUPT(WDT_vect);         // Disable Watchdog Timer interrupt
EMPTY_INTERRUPT(TIM0_COMPA_vect);  // Disable Timer0 Compare Match A interrupt
EMPTY_INTERRUPT(TIM0_COMPB_vect);  // Disable Timer0 Compare Match B interrupt
EMPTY_INTERRUPT(TIM0_OVF_vect);    // Disable Timer0 Overflow interrupt
EMPTY_INTERRUPT(TIM1_COMPA_vect);  // Disable Timer1 Compare Match A interrupt
EMPTY_INTERRUPT(TIM1_COMPB_vect);  // Disable Timer1 Compare Match B interrupt
EMPTY_INTERRUPT(TIM1_OVF_vect);    // Disable Timer1 Overflow interrupt
EMPTY_INTERRUPT(TIM1_CAPT_vect);   // Disable Timer1 Capture Event interrupt
EMPTY_INTERRUPT(ANA_COMP_vect);    // Disable Analog Comparator interrupt