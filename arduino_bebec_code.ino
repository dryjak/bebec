#define motor_a_pwm 10
#define motor_b_pwm 5
#define motor_c_pwm 6
#define motor_d_pwm 9

//define direction of the motors
#define dir_a_1 12
#define dir_a_2 11
#define dir_b_1 2
#define dir_b_2 13
#define dir_c_1 4
#define dir_c_2 3
#define dir_d_1 8
#define dir_d_2 7

//additional features like led ligths, buzzer. Lights are not used yet.
#define led1 A1
#define led2 A2
#define buzzer A3
//voltage needs to be checked to make sure that lion batteries are not over discharged. If lion batteries are over discharged, they are destroyed
#define voltage_input A4



char character_read;
unsigned long current_time;
unsigned long last_read;
int speed = 200; //you may use it to change the speed of the motors

//checking battery vltage
float voltage_in;
unsigned long voltage_time;
float voltage =0.00;
//you may use different types of resistors to make voltage devider. Be cautious
float R1 = 4700;
float R2 = 10000;


void setup() {
  Serial.begin(9600);
  pinMode(motor_a_pwm, OUTPUT);
  pinMode(motor_b_pwm, OUTPUT);
  pinMode(motor_c_pwm, OUTPUT);
  pinMode(motor_d_pwm, OUTPUT);
  pinMode(dir_a_1, OUTPUT);
  pinMode(dir_a_2, OUTPUT);
  pinMode(dir_b_1, OUTPUT);
  pinMode(dir_b_2, OUTPUT);
  pinMode(dir_c_1, OUTPUT);
  pinMode(dir_c_2, OUTPUT);
  pinMode(dir_d_1, OUTPUT);
  pinMode(dir_d_2, OUTPUT);

  pinMode(buzzer,OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void gogogo(int apwm, int bpwm, int cpwm, int dpwm, int a1, int a2, int b1,int b2,int c1, int c2, int d1, int d2)
{
  analogWrite(motor_a_pwm, apwm);
  analogWrite(motor_b_pwm, bpwm);
  analogWrite(motor_c_pwm, cpwm);
  analogWrite(motor_d_pwm, dpwm);
  digitalWrite(dir_a_1, a1);
  digitalWrite(dir_a_2, a2);
  digitalWrite(dir_b_1, b1);
  digitalWrite(dir_b_2, b2);
  digitalWrite(dir_c_1, c1);
  digitalWrite(dir_c_2, c2);
  digitalWrite(dir_d_1, d1);
  digitalWrite(dir_d_2, d2);
}

void loop() {
  current_time = millis();
  if(Serial.available())  //checking if there is data to read
{
  character_read = Serial.read();
  last_read = current_time;
}
  //making sure lipo batteries are not over discharged. If so turn on the buzzer
  if(current_time - voltage_time > 2000)
  {
    voltage = (analogRead(voltage_input) * 5.0/1024.0) / ((R1+R2)/R2);
    if (voltage < 7) //setting voltage treshold to 7V. You may change it to 6.6V, I hadn't done that in order to have larger voltage margin
    {
      digitalWrite(buzzer, HIGH);
      Serial.print("Voltage in:");
      Serial.println(voltage_in);
    }
    voltage_time = current_time;
  }
  if(current_time - last_read > 600 ){
    gogogo(0,0,0,0,0,0,0,0,0,0,0,0);
  }
  /********************Go forward********************/
  if(character_read == 'W'){
    gogogo(speed, speed, speed, speed, 1, 0, 1, 0, 1, 0, 1, 0);
  }
  /********************Go backwards******************/
  if(character_read == 'S'){
    gogogo(speed, speed, speed, speed, 0, 1, 0, 1, 0, 1, 0, 1);
  }
  /********************Turn left*********************/
  if(character_read == 'A'){
    gogogo(speed, speed, speed, speed, 1, 0, 0, 1, 0, 1, 1, 0);
  }
  /********************Turn right********************/
  if(character_read == 'D'){
    gogogo(speed, speed, speed, speed, 0, 1, 1, 0, 1, 0, 0, 1);
  }
  /********************Led 1*************************/
  if(character_read == 'L'){
    digitalWrite(led1, HIGH);
  }
  if(character_read == 'l'){
    digitalWrite(led1, LOW);
  }
  /********************Led 2*************************/
    if(character_read == 'K'){
    digitalWrite(led2, HIGH);
  }
  if(character_read == 'k'){
    digitalWrite(led2, LOW);
  }
  /********************Buzzer************************/
  if(character_read == 'B'){
    digitalWrite(buzzer, HIGH);
  }
  if(character_read == 'b'){
    digitalWrite(buzzer, LOW);
  }
  
}
