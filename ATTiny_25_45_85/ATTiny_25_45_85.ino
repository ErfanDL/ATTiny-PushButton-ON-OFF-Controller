#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <avr/power.h>

const int buttonPin = PB3; // Change to your actual button pin
const int powerPin = PB4;  // Change to your actual power control pin

volatile bool powerState = false;

void setup() {
  // Set all unused pins to output to avoid floating inputs
  DDRB = 0xFF;
  PORTB = 0x00;

  // Set button pin as input without pull-up resistor
  pinMode(buttonPin, INPUT);
  
  // Disable pull-up resistor to save power
  PORTB &= ~(1 << buttonPin);

  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, powerState); // Start with power off

  // Disable ADC to save power
  ADCSRA &= ~(1 << ADEN);
  
  // Disable Analog Comparator to save power
  ACSR |= (1 << ACD);

  // Set up Pin Change Interrupt
  GIMSK |= (1 << PCIE); // Enable Pin Change Interrupts
  PCMSK |= (1 << PCINT3); // Use PB3 as interrupt pin
  sei(); // Enable global interrupts
}

void loop() {
  if (!powerState) {
    // Device is off, enter sleep mode
    goToSleep();
  }
}

void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_bod_disable(); // Disable Brown-Out Detection to save power
  sei(); // Ensure interrupts are enabled so we wake up again
  sleep_cpu(); // Go to sleep
  sleep_disable(); // Wake up here
}

ISR(PCINT0_vect) {
  // Ensure button is pressed and debounce it
  if (digitalRead(buttonPin) == LOW && debounceButton()) {
    powerState = !powerState; // Toggle power state
    digitalWrite(powerPin, powerState); // Apply new power state
  }
}

bool debounceButton() {
  // Wait for button to stabilize
  delay(10);

  // Check button state again
  return digitalRead(buttonPin) == LOW;
}

EMPTY_INTERRUPT(WDT_vect); // Disable Watchdog Timer interrupt
EMPTY_INTERRUPT(TIM0_COMPA_vect); // Disable Timer0 Compare Match A interrupt
EMPTY_INTERRUPT(TIM0_COMPB_vect); // Disable Timer0 Compare Match B interrupt
EMPTY_INTERRUPT(TIM1_COMPA_vect); // Disable Timer1 Compare Match A interrupt
EMPTY_INTERRUPT(TIM1_COMPB_vect); // Disable Timer1 Compare Match B interrupt
EMPTY_INTERRUPT(TIM1_OVF_vect); // Disable Timer1 Overflow interrupt
EMPTY_INTERRUPT(TIM1_CAPT_vect); // Disable Timer1 Capture Event interrupt
EMPTY_INTERRUPT(ANA_COMP_vect); // Disable Analog Comparator interrupt
