// #include <Arduino.h>
// #include <ChRt.h>
// #include <Servo.h>
// #define TRIG 3
// #define ECHO 2

// Servo srv1, srv2;
// int srv1_angle = 0;
// int srv2_angle = 90;
// long int SR_duration;
// int SR_distance;

// int readSR(){
//   digitalWrite(TRIG, LOW);
//   delayMicroseconds(2);
//   digitalWrite(TRIG, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(TRIG, LOW);
//   SR_duration = pulseIn(ECHO, HIGH);
//   return SR_duration * 0.034 / 2;
// }

// static THD_WORKING_AREA(servo1waThread, 64);
// static THD_FUNCTION(servo1Thread, arg){
//   (void) arg;
//   while(1){
//     Serial.print("T1");
//     if(Serial.available()){
//       srv1_angle = Serial.parseInt();
//       srv1.write(srv1_angle);
//     }
//   }
// }

// static THD_WORKING_AREA(servo2waThread, 64);
// static THD_FUNCTION(servo2Thread, arg){
//   (void) arg;
//   while(1){
//     chThdSleepMilliseconds(1);
//     Serial.println("T2");
//     SR_distance = readSR();
//     srv2_angle = map(SR_distance, 10, 100, 0, 360);
//     srv2.write(srv2_angle);
//   }
// }

// void chSetup(){
// //  chThdCreateStatic(servo1waThread, sizeof(servo1waThread),NORMALPRIO + 1, servo1Thread, NULL);
//   chThdCreateStatic(servo2waThread, sizeof(servo2waThread),NORMALPRIO + 1, servo2Thread, NULL);
// }

// void setup() {
//   // put your setup code here, to run once:
//   srv1.attach(5);
//   srv2.attach(7);
//   srv1.write(srv1_angle);
//   srv1.write(srv2_angle);

//   pinMode(TRIG, OUTPUT);
//   pinMode(ECHO, INPUT);
//   Serial.begin(9600);

//   chBegin(chSetup);
//   while(true){}
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//       Serial.print("T1");
//     if(Serial.available()){
//       srv1_angle = Serial.parseInt();
//       srv1.write(srv1_angle);
//     }
// }


// #include <Arduino.h>
// #include <ChRt.h>

// int main(){
//     DDRB |= (1 << PB5);
// 	while(1){
// 		PORTB |= (1 << PB5);
// 		_delay_ms(500);
// 		PORTB &= ~(1 << PB5);
// 		_delay_ms(500);
// 	}
// }

#include <Arduino.h>
#include <ChRt.h>
static THD_WORKING_AREA(wa_thd1, 64);
static THD_FUNCTION(thd1, arg){
	(void)arg;
	while(1){
		digitalWrite(LED_BUILTIN, HIGH);
		chThdSleepMilliseconds(1000);
		digitalWrite(LED_BUILTIN, LOW);
		chThdSleepMilliseconds(500);
	}
}
void setup(){
	pinMode(13, OUTPUT);
	chThdCreateStatic(wa_thd1, sizeof(wa_thd1),NORMALPRIO + 1, thd1, NULL);
}
void loop(){}
// //int main (){}


// #include <ChRt.h>
// #include <Arduino.h>
// #include <SoftwareSerial.h>
// SoftwareSerial myBT(0, 1); //rx, tx (reverse in bluetooth)
// #define IN1 4
// #define IN2 5
// #define IN3 6
// #define IN4 7
// int code;
// // 1 = forward, 2 = backward, 3 = left, 4 = right

// void forward(){
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
// }

// void left(){
//   digitalWrite(IN1, HIGH);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
// }

// void right(){
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, HIGH);
//   digitalWrite(IN4, LOW);
// }

// void reverse(){
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, HIGH);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, HIGH);
// }

// void stop (){
//   digitalWrite(IN1, LOW);
//   digitalWrite(IN2, LOW);
//   digitalWrite(IN3, LOW);
//   digitalWrite(IN4, LOW);
// }

// int readBT(){
//   int code_t;
//   if (myBT.available()) code_t = myBT.parseInt();
//   return code_t;
// }

// static THD_WORKING_AREA(waBT, 64);
// static THD_FUNCTION(thdBT, arg){
//   (void) arg;
//   while(1){
//     code = readBT();
// //    Serial.println(code);
//     chThdSleepMicroseconds(100000);
//   }
// }

// void chSetup(){
//   chThdCreateStatic(waBT, sizeof(waBT), NORMALPRIO + 1, thdBT, NULL);
// }

// void setup() {
//   // put your setup code here, to run once:
//   myBT.begin(9600);  
//   Serial.begin(9600);
//   chBegin(chSetup);
// }

// void loop() {
//   // put your main code here, to run repeatedly:

//   if (code == 1) {
//     Serial.println("Forward");
//     forward();
//   }
//   if (code == 2) {
//     Serial.println("Backward");
//     reverse();
//   }
//   if (code == 3) {
//     Serial.println("Left");
//     left();
//   }
//   if (code == 4) {
//     Serial.println("Right");
//     right();
//   }
// //  if (code == 0) Serial.println("Engine Off");
// }