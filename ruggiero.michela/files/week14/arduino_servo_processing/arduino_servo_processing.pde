
import processing.serial.*; // add library: firmadata, arduino and serial
Serial myPort;        // The serial port
void setup() {
  size(360,180); // window dimention 
    for(int i=0; i <Serial.list().length;i++){
 //  println("["+ i +"] " + Serial.list()[i]); 
  }
   myPort = new Serial(this, Serial.list()[7], 9600);

  }

void draw() {
  int gradi = mouseX/2; // servo position
 // String valore = str(gradi); // string to print
 String valore = gradi + "\n"; // string to print
 println(valore);
  myPort.write(valore);

  // Debug
  // println(mouseX); // verify mouse position
  // println(gradi); // verify degrees convertion 
  // println(valore); // verify string to print

  background(gradi); // backgroun color. IMPORTANT!!!
  
  textSize(32); // text dimention
  textAlign(CENTER); // text allignment
  text(valore, 360/2, 180/2); // print value (degrees rotation)

}
void serialEvent (Serial myPort) {
 // get the ASCII string:
String inString = myPort.readStringUntil('\n');
 
 if (inString != null) {
 // trim off any whitespace:
 inString = trim(inString);
 println("received : " + inString);
 }
}

