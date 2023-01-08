#include <ArduinoBLE.h>

const int btnPin = 4; //Setting the button pin to 4

BLEService btnService("e267751a-ae76-11eb-8529-0242ac130003"); //Creating a service

BLEByteCharacteristic btnState("00002a19-0000-1000-8000-00805f9b34fb", BLERead | BLENotify);

void setup() {

  pinMode(btnPin, INPUT); //Setting the button pin as input pin
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(9600); //Starting the serial monitor
  delay(500);

  BLE.begin(); //Starting the Bluetooth Low Energy
  delay(500);

  BLE.setLocalName("Fitness Band"); //Setting the local name

  BLE.setAdvertisedService(btnService); //Setting the UUID for the advertised service

  btnService.addCharacteristic(btnState); //Adding the characteristic to the service

  BLE.addService(btnService); //Adding the service

  btnState.writeValue(0); //Setting the initial value of the button state

  BLE.advertise();

  Serial.println("Fitness Band is sharing data");

}

void loop() {
  BLEDevice central = BLE.central(); //Listen for Bluetooth® Low Energy peripherals to connect:

  if (central) { // If a central is connected to peripheral
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("Connected to central: "); //Print the central's MAC address
    Serial.println(central.address());

  while (central.connected()) {
  char buttonValue = digitalRead(btnPin);
  bool buttonChanged = (btnState.value() != buttonValue);

  if (buttonChanged) {  //Button state changed, update characteristics
    btnState.writeValue(buttonValue);
    Serial.print("The button State is: ");
    Serial.println(buttonValue);
  }
  
  }
  
  Serial.print("Disconnected from central: "); //When the central disconnects, print it out:
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, LOW);
  }

}
