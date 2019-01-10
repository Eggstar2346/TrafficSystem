  //Due: Monday January 18 2016
  //Names: Jennifer Huynh, Naomi Kothiyal, Esther Yoo
  //Teacher: Mr Wong
  //Purpose: This program contains the final code, with the traffic 
  //  light system, pedestrian light system, and the gate system all
  //  combined

  //imports
  #include <Servo.h>

  //global variables declaration
  Servo servo;
  int timer = -1;
  int button = 12;
  int pred = 8;
  int pgreen = 9;
  int buttonState = 1;
  int motorTimer = 0;
  int pos = 0;
  int moveMotor = false;

  //this method sets up all the components, including the main traffic
  //  light system, pedestrian lights, button, and servo.
  void setup()
  {
  for (int thisPin = 2; thisPin <= 7; thisPin++)
  {
  pinMode(thisPin, OUTPUT);
  }
  pinMode(pred, OUTPUT);
  pinMode(pgreen, OUTPUT);
  pinMode(button, INPUT);
  servo.attach(10);
  pinMode (A0, INPUT);
  Serial.begin (9600);
  }

  //this method is called when the button is pressed at a certain time.
  //its purpose is to speed up the amount of time the 2 red lights of
  //  the main system are on for
  void speedRed ()
  {
  digitalWrite (7, LOW);
  digitalWrite (3, LOW);
  for (int x = 0; x <= 1500; x++)
  {
  digitalWrite (4, HIGH);
  digitalWrite (8, HIGH);
  digitalWrite (5,HIGH);
  delay(1);
  }
  digitalWrite(5, LOW);
  }

  //this method is called when the button is pressed at a certain time.
  //its purpose is to speed up the amount of time the 2 yellow lights of
  //  the main system are on for
  void speedYellow ()
  {
  digitalWrite (3, LOW); //2 yellows
  for (int x = 0; x <= 1500; x++)
  {
  digitalWrite (3, HIGH);
  digitalWrite (6, LOW);
  digitalWrite (7, HIGH);
  delay(1);
  }
  digitalWrite(7, LOW);
  }
  
  //this is the main loop that runs the entire system
  void loop() {
  buttonState = digitalRead(button); //read in button's state
  //main traffic light system
  if (timer == 0)
  {
  digitalWrite (4, LOW);
  digitalWrite (2, HIGH);
  digitalWrite (6, LOW);
  digitalWrite (7, HIGH);
  digitalWrite (pgreen, HIGH);
  digitalWrite (pred, LOW);
  }
  else if (timer == 3000)
  {
  digitalWrite (2, LOW);
  digitalWrite (3, HIGH);
  digitalWrite (pgreen, LOW);
  digitalWrite (pred, HIGH);
  }
  else if (timer == 6000)
  {
  digitalWrite (3, LOW);
  digitalWrite (4, HIGH);
  digitalWrite (5, HIGH);
  digitalWrite (7, LOW);
  }
  else if (timer == 9000)
  {
  digitalWrite (5, LOW);
  digitalWrite (6, HIGH);
  }

  //pedestrian light system
  if (buttonState == 0)
  {
  if (timer >= 4500)
  {
    speedRed();
    timer = -1;
  }
  else if (timer >= 3000 && timer < 4500)
  {
    speedYellow();
    speedRed();
    timer = -1;
  }
  else if (timer >= 7500)
  {
    timer = -1;
  }
  else if (timer >= 6000 && timer < 7500)
  {
    speedRed();
    timer = -1;
  }
  }
  else
  {
  timer = timer + 0;
  }
  
  //gate system
  int sensorValue = analogRead(0);
    Serial.println(sensorValue);

  if (sensorValue >= 1000)
  {
  moveMotor = true;
  }
  if (moveMotor == true)
  {
  if (motorTimer < 300 && motorTimer % 10 == 0)
  {
  pos += 3;
  }
  else if (motorTimer >= 800 && motorTimer % 10 == 0)
  {
  pos -= 3;
  }
  else
  {
  }
  servo.write(pos);
  motorTimer++;
  if (motorTimer == 1100)
  {
  motorTimer = 0;
  moveMotor = false;
  }
  }
  
  if ((timer >= 12000))
  {
  timer = -1; //resetting timer after a certain point
  }
  buttonState = 1; //resetting button state in case it was pressed
  delay(1);
  timer++; //increment timer (represents every millisecond)
  }
  
//end of program
