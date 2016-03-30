#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h>
int lightreading;
Servo microservo; 
int pos = 0;
int led = 9;
int vcc = 2; //attach pin 2 to vcc
int trig = 3; // attach pin 3 to Trig
int echo = 4; //attach pin 4 to Echo
int gnd = 5; //attach pin 5 to GND
int tonePin = 8; 
int t1=15;
int minSecsBetweenEmails = 10; // 1 min
long lastSend = -minSecsBetweenEmails * 1000l;
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x17 };
IPAddress ip(192,168,1,126);
EthernetServer server(80);
//EthernetServer server(80);                             //server port     
String readString;
void setup() {

pinMode (vcc,OUTPUT);
pinMode (gnd,OUTPUT);
// initialize serial communication:
Serial.begin(9600);
pinMode(led, OUTPUT);
  microservo.attach(7);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

}
void loop()
{
digitalWrite(vcc, HIGH);
// establish variables for duration of the ping,
// and the distance result in inches and centimeters:
long duration, inches, cm;

// The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(5);
digitalWrite(trig, LOW);

// The same pin is used to read the signal from the PING))): a HIGH
// pulse whose duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
pinMode(echo,INPUT);
duration = pulseIn(echo, HIGH);

// convert the time into a distance
inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);
//t2=cm;
//Serial.print(inches);
//Serial.print("in, ");
//Serial.print(cm);
//Serial.print("cm");
//Serial.println("%d in, %d cm",inches,cm);
//if((t1-t2)>3)
//  Serial.println("Movement");
EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           //client.println("<?php $conn=new mysqli('localhost','amithrajsn','dell3543'); if($conn->connect_error){die('connection failed');}else echo'Successfully connected';?>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>Random Nerd Tutorials Project</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Random Nerd Tutorials Project</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Arduino with Ethernet Shield</H2>");
           client.println("<br />");  
           client.println("<a href=\"/button1on\"\">Turn On LED</a>");
           client.println("<a href=\"/button1off\"\">Turn Off LED</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           client.println("<a href=\"/button2on\"\">Rotate Left</a>");
           client.println("<a href=\"/button2off\"\">Rotate Right</a><br />"); 
           client.println("<p>Created by Rui Santos. Visit http://randomnerdtutorials.com for more projects!</p>");  
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons
           if (readString.indexOf("button1on") >0){
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("button1off") >0){
               digitalWrite(led, LOW);
           }
           if (readString.indexOf("button2on") >0){
                for(pos = 0; pos < 180; pos += 3)  // goes from 0 degrees to 180 degrees 
                {                                  // in steps of 1 degree 
                  microservo.write(pos);              // tell servo to go to position in variable 'pos' 
                  
                  delay(15);                       // waits 15ms for the servo to reach the position 
                } 
           }
           if (readString.indexOf("button2off") >0){
                for(pos = 180; pos>=1; pos-=3)     // goes from 180 degrees to 0 degrees 
                {                                
                  microservo.write(pos);              // tell servo to go to position in variable 'pos' 
                  
                  delay(15);                       // waits 15ms for the servo to reach the position 
                } 
           }
            //clearing string for next read
            readString="";  
           
         }
       }
    }
}
if(cm<10)
{
  long now = millis();
  tone(tonePin,5000, 200);
  if (now > (lastSend + minSecsBetweenEmails * 1000l))
  {  
    Serial.println("MOVEMENT");
    lastSend = now; 
    } 
    else 
    {   
    Serial.println("Too soon");
    }
  }
  //Serial.println("MOVEMENT");

delay(400);
}

long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}
