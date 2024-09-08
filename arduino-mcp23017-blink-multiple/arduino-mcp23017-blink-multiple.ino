// Blinks an LED attached to a MCP23017 pin.

// WARNING: Some people have reported an undocumented bug that can potentially corrupt the I2C bus. It occurs if an MCP230XX input pin state changes during I2C readout,
// so DO NOT attempt to change the pinMode of MCP pins set to input mode on the fly

// On the Arduino UNO (Chinese version, without the Atmega128 detachable IC) the SDA and SCL pins of the MCP must be connected to the Arduino SDA and SCL dedicated pins
// Remember that the MCP pins start at GPA0 as pin 0 (physical pin 21, base 1) and end at GPB7 as pin 15 (physical pin 8, base 1) for a total of 16 available GPIO pins

#include <Adafruit_MCP23X17.h>

#define LED_PIN 0     // MCP23017 pin LED is attached to (on the first MCP chip, at address 0x20, the default I2C address)
#define LED_PIN_2 0     // MCP23017 pin LED is attached to (on the second MCP, at address 0x21)

Adafruit_MCP23X17 mcp;
Adafruit_MCP23X17 mcp2;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("MCP23xxx Blink Test!");

  // The MCP23017 supports I2C communication only, so use begin_I2C to start it, not begin_SPI
  if (!mcp.begin_I2C(0x20)) {
    Serial.println("Error. MCP at address 0 not found.");
    while (1);
  }

  // Specify address in the argument of begin function, default is 0 if not specified
  // For each additional MCP, plug a different combination of pins A0, A1, and A2 to set an I2C address from "0x20 + 0" to "0x20 + 7", and pass the resulting value to the begin function
  if (!mcp2.begin_I2C(0x21)) {
    Serial.println("Error. MCP at address 1 not found.");
    while (1);
  }

  // configure pins for output
  mcp.pinMode(LED_PIN, OUTPUT);
  mcp2.pinMode(LED_PIN_2, OUTPUT);

  Serial.println("Looping...");
}

void loop() {
  Serial.println("Alpha on! (high) / Beta off! (low)");
  mcp.digitalWrite(LED_PIN, HIGH);
  mcp2.digitalWrite(LED_PIN_2, LOW);
  delay(500);
  Serial.println("Alpha off! (low) / Beta on! (high)");
  mcp.digitalWrite(LED_PIN, LOW);
  mcp2.digitalWrite(LED_PIN_2, HIGH);
  delay(500);
}