# include <RTClib.h>
#include <ezButton.h>
RTC_DS1307 rtc;

byte clk=2;
byte dt=3;
byte sw=4;
ezButton button(sw);
int counter=0;
int prev_counter=0;
int flag=0;
String rtc_date="";
String rtc_time="";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!rtc.begin()){
    // Serial.println("RTC Not Initialized");
    while(true);
  }
  // Serial.println("RTC Found");
  attachInterrupt(digitalPinToInterrupt(clk),encoder,FALLING);
  button.setDebounceTime(25);
}

void encoder(){
  prev_counter=counter;
  if(digitalRead(dt)==HIGH)counter++;
  else counter--;
  counter=constrain(counter,0,3);
  flag=1;
}

void mode_selector(){
  if(prev_counter!=counter && flag == 1){
    if(counter==0){
      Serial.println("Date and Time");
    }
    else if(counter==1){
      Serial.println("Set Alarm");
    }
    else if(counter==2){
      Serial.println("Stop Watch");
    }
    else if(counter==3){
      Serial.println("Countdown Timer");
    }
    flag=0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // DateTime dt=rtc.now();
  // rtc_time=get_time(dt);
  // Serial.println(rtc_time);
  // rtc_date=get_date(dt);
  // Serial.println(rtc_date);
  button.loop();
  if(button.isPressed())select_mode();
  mode_selector();
  delay(10);
}

String get_time(DateTime current){
  int hour=current.hour();
  int minute=current.minute();
  int second=current.second();
  String current_time="Time : "+String(hour)+":"+String(minute)+":"+String(second);
  return current_time;
}

String get_date(DateTime current){
  int year=current.year();
  int month=current.month();
  int day=current.day();
  String current_date="Date : "+String(day)+"/"+String(month)+"/"+String(year);
  return current_date;
}

void select_mode(){
  if(counter==0)Serial.println("Date and Time Mode is Selected");
  if(counter==1)Serial.println("Set Alarm Mode is Selected");
  if(counter==2)Serial.println("Stop Watch Mode is Selected");
  if(counter==3)Serial.println("Countdown Timer Mode is Selected");
}