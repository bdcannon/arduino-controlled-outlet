int lightSensor = 0;    
int lightValue;

int potSensor = 1;
int potValue;

int relayPin = 2;

// Status Lights
int onPin = 8;
int manualModePin = 7;

//////////////////////////////
// Variables for buttons
int modeButtonPin = 12;
bool buttonState = false;
bool lastModeButtonState = false;
bool currentModeButtonState = false;
unsigned long lastModeButtonReadAt = 0;

int toggleButtonPin = 13;
bool toggleState = false;
bool currentToggleButtonState = false;
bool lastToggleButtonState = false;
unsigned long lastToggleButtonReadAt = 0;

bool switchOn = false;

unsigned long debounceDelay = 15;
//////////////////////////////

bool currentMode = false; // False = Sensor mode. True = Manual Mode
bool manualMode = true;
bool SensorMode = false;

// Modes the controller runs in
void manualModeHandler();
void lightSensorModeHandler();

// Read buttons
bool readModeButton();
bool readToggleButton();

void updateModeLights();

void setup()
{
  Serial.begin(9600);              //  setup serial
  pinMode(relayPin, OUTPUT);
  pinMode(onPin, OUTPUT);
  pinMode(manualModePin, OUTPUT);
}

void loop()
{
  if(readModeButton()){
    currentMode = !currentMode;
    updateModeLight();
    Serial.print(currentMode);
    Serial.println("Toggled Mode");
    do{}while(readModeButton());
  }
  
  switch(currentMode){
    case true : manualModeHandler(); break;
    case false : sensorModeHandler(); break;
  }
}

bool readModeButton(){
  // If we've waited long enough
  if((millis() - lastModeButtonReadAt) > debounceDelay){
    lastModeButtonReadAt = millis();
    currentModeButtonState = digitalRead(modeButtonPin);
    
    if(lastModeButtonState == currentModeButtonState){
      buttonState = currentModeButtonState;
    }
    lastModeButtonState = currentModeButtonState;
  }
  return buttonState;
}

bool readToggleButton(){
  // If we've waited long enough
  if((millis() - lastToggleButtonReadAt) > debounceDelay){
    lastToggleButtonReadAt = millis();
    currentToggleButtonState = digitalRead(toggleButtonPin);
    
    if(lastToggleButtonState == currentToggleButtonState){
      toggleState = currentToggleButtonState;
    }
    lastToggleButtonState = currentToggleButtonState;
  }
  return toggleState;
}


void updateModeLight(){
  digitalWrite(manualModePin, currentMode);
}

void manualModeHandler(){
  if(readToggleButton()){
    switchOn = !switchOn;
    digitalWrite(onPin, switchOn);
    digitalWrite(relayPin, switchOn);
    Serial.println("Turned the swtich on");
    do{}while(readToggleButton());
  } 
}

void sensorModeHandler(){
  
}




