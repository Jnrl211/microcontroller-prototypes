// Blinks an LED attached to a MCP23017 pin.

// WARNING: Some people have reported an undocumented bug that can potentially corrupt the I2C bus. It occurs if an MCP230XX input pin state changes during I2C readout,
// so DO NOT attempt to change the pinMode of MCP pins set to input mode on the fly

// On the Arduino UNO (Chinese version, without the Atmega128 detachable IC) the SDA and SCL pins of the MCP must be connected to the Arduino SDA and SCL dedicated pins
// Remember that the MCP pins start at GPA0 as pin 0 (physical pin 21, base 1) and end at GPB7 as pin 15 (physical pin 8, base 1) for a total of 16 available GPIO pins

#include <Adafruit_MCP23X17.h>

#define LED_PIN 0     // MCP23017 pin LED is attached to (on the first MCP chip, at address B000)
#define LED_PIN_2 16     // MCP23017 pin LED is attached to (on the second MCP, at address B001)

Adafruit_MCP23X17 mcp;

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  Serial.println("MCP23xxx Blink Test!");

  // The MCP23017 supports I2C communication only, so use begin_I2C to start it, not begin_SPI
  if (!mcp.begin_I2C()) {
    Serial.println("Error.");
    while (1);
  }

  // configure pins for output
  mcp.pinMode(LED_PIN, OUTPUT);
  mcp.pinMode(LED_PIN_2, OUTPUT);

  Serial.println("Looping...");
}

void loop() {
  Serial.println("Alpha on! (high) / Beta off! (low)");
  mcp.digitalWrite(LED_PIN, HIGH);
  mcp.digitalWrite(LED_PIN_2, LOW);
  delay(500);
  Serial.println("Alpha off! (low) / Beta on! (high)");
  mcp.digitalWrite(LED_PIN, LOW);
  mcp.digitalWrite(LED_PIN_2, LOW);
  delay(500);
}