#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include <Servo.h>

Servo myservo;
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);


#define echoPin1 3
#define trigPin1 2

int i=0;
char x,x1;
char msg[]="OBSTACLE_DETECTED.!";
char msg1[]="FALL_DETECTED.!";
long duration,distance1; 

void setup() 
{
  //start serial connection
  Serial.begin(9600);
  myservo.attach(4);
  //configure pin 2 as an input and enable the internal pull-up resistor
  
  pinMode(echoPin1,INPUT);
  pinMode(trigPin1,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
   /*Enable receiver and transmitter */
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
/* Set frame format: 8data, 2stop bit */
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);

  myservo.write(0);
  delay(15);
  
  lcd.begin(16, 2);      // USING 16X2 LCD

  lcd.setCursor(0,0);  
  lcd.print("    IOT BASED");
  lcd.setCursor(0,1);  
  lcd.print("   BLIND STICK"); 
  
delay(1500);

}

void loop() 
{
  x=USART_Receive();
  if(x=='1')
  {
    lcd.clear();
    lcd.setCursor(0,0);  
  lcd.print("  BLIND OBJECT");
  lcd.setCursor(0,1);  
  lcd.print("    DETECTION"); 
  delay(1500); 
  while(1)
  {
    do
    {
      x1=USART_Receive();
    }while(x1!='$'); 
     x1=USART_Receive();
     x=USART_Receive();
     if(x1=='3')
     {
      lcd.clear();
      lcd.setCursor(0,0);  
  lcd.print("     HUMAN");
  lcd.setCursor(0,1);  
  lcd.print("   DETECTED"); 
  delay(1500); 
  for(i=0;i<1;i++)
          {
          digitalWrite(6,HIGH);
          digitalWrite(7,HIGH);
          delay(1500);
          digitalWrite(6,LOW);
          digitalWrite(7,LOW);
          delay(1500);
          }
     }
     else
     {
      lcd.clear();
      lcd.setCursor(0,0);  
  lcd.print("    OBJECT");
  lcd.setCursor(0,1);  
  lcd.print("   DETECTED");
  delay(1500);
  for(i=0;i<1;i++)
          {
          digitalWrite(6,HIGH);
          digitalWrite(7,HIGH);
          delay(1500);
          digitalWrite(6,LOW);
          digitalWrite(7,LOW);
          delay(1500);
          } 
     }
  }
  }

  else if(x=='2')
  {
    lcd.clear();
    lcd.setCursor(0,0);  
  lcd.print("  BLIND STICK");
  lcd.setCursor(0,1);  
  lcd.print("    ASSISTANCE"); 
  delay(1500); 
  while(1)
  {
  delay(100);  
  int x=analogRead(A0);
  int y=analogRead(A1);
  int wl=digitalRead(A2);


  digitalWrite(trigPin1, LOW);   
  delayMicroseconds(2);              // wait for 2uS
  digitalWrite(trigPin1, HIGH);  
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distance1 = (duration/2) / 29.1;

  //Serial.print("\nDIST: ");  //LCD DISPLAY 1.
  //Serial.print(distance1);
  

  lcd.clear();
  lcd.setCursor(0,0);  //SET THT CURSOR ON COLM 0 & ROW 0
  lcd.print("X:");  //LCD DISPLAY
  lcd.print(x);
  lcd.setCursor(6,0);  //SET THT CURSOR ON COLM 0 & ROW 0
  lcd.print("Y:");  //LCD DISPLAY 1.
  lcd.print(y);
  lcd.setCursor(13,0);  //SET THT CURSOR ON COLM 0 & ROW 0
  lcd.print("W:");  //LCD DISPLAY 1.
  lcd.print(wl);

  lcd.setCursor(0,1);  //SET THT CURSOR ON COLM 0 & ROW 0
  lcd.print("D: ");  //LCD DISPLAY 1.
  lcd.print(distance1);
  delay(900);
//Serial.print("\n\n X =");
//Serial.print(x);

//Serial.print("\n\n Y =");
//Serial.print(y);

if(distance1<30)
{
  lcd.clear();
    lcd.setCursor(0,0);  
  lcd.print("     OBSTACLE");
  lcd.setCursor(0,1);  
  lcd.print("     DETECTED"); 
  delay(100); 
  for(i=0;i<2;i++)
          {
          digitalWrite(6,HIGH);
          digitalWrite(7,HIGH);
          delay(1500);
          digitalWrite(6,LOW);
          digitalWrite(7,LOW);
          delay(1500);
          }
}

if(wl==1)
{
  lcd.clear();
    lcd.setCursor(0,0);  
  lcd.print("      WATER");
  lcd.setCursor(0,1);  
  lcd.print("    DETECTED"); 
  delay(1500); 
  for(i=0;i<3;i++)
          {
          digitalWrite(6,HIGH);
          digitalWrite(7,HIGH);
          delay(1500);
          digitalWrite(6,LOW);
          digitalWrite(7,LOW);
          delay(1500);
          }
}


if((y>360)&&(y<380))
{
myservo.write(90);
delay(15);
}
else
{
  myservo.write(0);
  delay(15);
}

if(distance1<20)
{
//iot1();
//iot2();
iot5();
delay(2000);
}

if(y<360)
{
//iot3();
//iot4();
iot6();
delay(2000);  
}
  }
  }

}

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
UDR0 = data;
}

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
return UDR0;
}


void iot1()
{

  Serial.print("{\"data\":{\"s1\":");Serial.print("\"OBSTACLE_DETECTED.CRITICAL_ALERT\"");
  //Serial.print(",\"s2\":");Serial.print("\"NA\"");
  //Serial.print(",\"s3\":");Serial.print("\"NA\"");
  //Serial.print(",\"s4\":");Serial.print("\"NA\"");
  //Serial.print(",\"s5\":");Serial.print("\"NA\"");
  //Serial.print(",\"s6\":");Serial.print("\"NA\"");
  //Serial.print(",\"s7\":");Serial.print("\"NA\"");
  //Serial.print(",\"s8\":");Serial.print("\"NA\",");
  Serial.print(",\"sms\":");Serial.print("\"0\"");
  Serial.println("}}#");delay(3000); 

}

void iot2()
{

  Serial.print("{\"data\":{\"s1\":");Serial.print("\"OBSTACLE_DETECTED.CRITICAL_ALERT\"");
  Serial.print(",\"s2\":");Serial.print("\"NA\"");
  Serial.print(",\"s3\":");Serial.print("\"NA\"");
  Serial.print(",\"s4\":");Serial.print("\"NA\"");
  Serial.print(",\"s5\":");Serial.print("\"NA\"");
  Serial.print(",\"s6\":");Serial.print("\"NA\"");
  Serial.print(",\"s7\":");Serial.print("\"NA\"");
  Serial.print(",\"s8\":");Serial.print("\"NA\",");
  Serial.print(",\"sms\":");Serial.print("\"1\"");
  Serial.println("}}#");delay(3000); 

}


 void iot3()
{

  Serial.print("{\"data\":{\"s1\":");Serial.print("\"FALL_DETECTED.CRITICAL_ALERT\"");
  //Serial.print(",\"s2\":");Serial.print("\"NA\"");
  //Serial.print(",\"s3\":");Serial.print("\"NA\"");
  //Serial.print(",\"s4\":");Serial.print("\"NA\"");
  //Serial.print(",\"s5\":");Serial.print("\"NA\"");
  //Serial.print(",\"s6\":");Serial.print("\"NA\"");
  //Serial.print(",\"s7\":");Serial.print("\"NA\"");
  //Serial.print(",\"s8\":");Serial.print("\"NA\",");
  Serial.print(",\"sms\":");Serial.print("\"0\"");
  Serial.println("}}#");delay(3000); 

}

void iot4()
{

  Serial.print("{\"data\":{\"s1\":");Serial.print("\"FALL_DETECTED.CRITICAL_ALERT\"");
  Serial.print(",\"s2\":");Serial.print("\"NA\"");
  Serial.print(",\"s3\":");Serial.print("\"NA\"");
  Serial.print(",\"s4\":");Serial.print("\"NA\"");
  Serial.print(",\"s5\":");Serial.print("\"NA\"");
  Serial.print(",\"s6\":");Serial.print("\"NA\"");
  Serial.print(",\"s7\":");Serial.print("\"NA\"");
  Serial.print(",\"s8\":");Serial.print("\"NA\",");
  Serial.print(",\"sms\":");Serial.print("\"1\"");
  Serial.println("}}#");delay(3000); 

}


void iot5()
{

    Serial.print("sensornewgsm.php?client=iot2k20066&s1=");
    Serial.print("OBSTACLE_DETECTED.CRITICAL_ALERT");
    Serial.print("&s2=NA");
    Serial.print("&s3=NA");
    Serial.print("&s4=NA");
    Serial.print("&s5=NA");
    Serial.print("&sms=YES&msg=OBSTACLE_DETECTED.CRITICAL_ALERT#");
    delay(500);
}

void iot6()
{

    Serial.print("sensornewgsm.php?client=iot2k20066&s1=");
    Serial.print("FALL_DETECTED.CRITICAL_ALERT");
    Serial.print("&s2=NA");
    Serial.print("&s3=NA");
    Serial.print("&s4=NA");
    Serial.print("&s5=NA");
    Serial.print("&sms=YES&msg=FALL_DETECTED.CRITICAL_ALERT#");
    delay(500);
}

          
