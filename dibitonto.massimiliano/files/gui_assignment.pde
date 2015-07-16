import processing.serial.*;
import controlP5.*;

ControlP5 cp5;

// variables to set the rule
String majminTxt;
int majmin ;
int majminR = 0 ;
int cond ;
int condR = 0;
String  condTxt;
int degrees = 28; //initial position of the slider
int degreesR = 0;

boolean attivo = true;
boolean statoCond = false;
RadioButton r;
RadioButton r2;
Textlabel myTextlabelA;
ListBox l;
int indx = 0;
boolean debounce= false;



int myColor = color(0,0,0);
int temp=0;
float t = 0;
int light = 0;
PFont font;
int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port

void setup() {
  
  background(30);
  // List all the available serial ports
  println(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[3], 9600);
  myPort.clear();
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
  
  size(600, 500);  
font = createFont("Arial",12);
textAlign(CENTER);
textFont(font);
frameRate(10);

//create slider
  cp5 = new ControlP5(this);
 // radio = new ControlP5(this);
  // add a horizontal sliders, the value of this slider will be linked
  // to variable 'sliderValue' 
  cp5.addSlider("degrees")
     .setPosition(200,90)
     .setRange(0,50)
     ;
  r = cp5.addRadioButton("radioTemp")
         .setPosition(200,60)
         .setSize(40,20)
         .setColorForeground(color(255, 204, 0))
         .setColorActive(color(255,0,0))
         .setColorLabel(color(0))
         .setItemsPerRow(2)
         .setSpacingColumn(50)
         .addItem("< than",1)
         .addItem("> than",2)
        
         ;
     
     for(Toggle t:r.getItems()) {
       t.captionLabel().setColorBackground(color(255,80));
       t.captionLabel().style().moveMargin(-7,0,0,-3);
       t.captionLabel().style().movePadding(7,0,0,3);
       t.captionLabel().style().backgroundWidth = 45;
       t.captionLabel().style().backgroundHeight = 13;
     }
     
     
     textAlign(LEFT);
    text("If temperature gets", 200,50);
    text("turn air conditioning", 200,120);
     r2 = cp5.addRadioButton("radioCond")
         .setPosition(200,130)
         .setSize(40,20)
         .setColorForeground(color(255, 204, 0))
         .setColorActive(color(255,0,0))
         .setColorLabel(color(0))
         .setItemsPerRow(2)
         .setSpacingColumn(50)
         .addItem("ON",1)
         .addItem("OFF",2)
        
         ;
     
     for(Toggle t:r2.getItems()) {
       t.captionLabel().setColorBackground(color(255,80));
       t.captionLabel().style().moveMargin(-7,0,0,-3);
       t.captionLabel().style().movePadding(7,0,0,3);
       t.captionLabel().style().backgroundWidth = 45;
       t.captionLabel().style().backgroundHeight = 13;
     }
     
      cp5.addButton("setRule")
     .setValue(0)
     .setCaptionLabel("Set rule")
     .setPosition(200,170)
     .setSize(200,19)
     ;
     
     l = cp5.addListBox("myList")
         .setPosition(200, 250)
         .setSize(300, 300)
         .setItemHeight(15)
         .setBarHeight(15)
         .setColorBackground(color(255, 128))
         .setColorActive(color(0))
         .setColorForeground(color(255, 100,0))
         ;

  l.captionLabel().toUpperCase(true);
  l.captionLabel().set("Rule");
  l.captionLabel().setColor(0xffff0000);
  l.captionLabel().style().marginTop = 3;
  l.valueLabel().style().marginTop = 3;
   
//  for (int i=0;i<80;i++) {
//    ListBoxItem lbi = l.addItem("item "+i, i);
//    lbi.setColorBackground(0xffff0000);
//  }
  
   cp5.addToggle("toggle")
     .setPosition(200,20)
     .setSize(50,20)
     .setValue(false)
    // .setCaptionLabel("label")
     .setMode(ControlP5.SWITCH)
     ; 
}

void draw() {
  applyRule();
  background(30);
  while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      myString= trim(myString);
      println(myString);
      String[] q = split(myString, "/");
//println(q.length + " values found");  // Prints "4 values found"
light = int(q[0]);  
temp = int(q[1]);  
lightR(light);
t = temp * 0.48828125; // the constant to have temperature in °C
tempR(t);
println("l="+light + " t=" + t);
    }
  }
 t = random(26, 27);
 tempR(t);
 lightR(int(random(440,450)));
 
}

void lightR(int l){
 stroke(255,255,255);
float lRel = map(l, 0, 650, 0, height - 40);
//println(lRel);
rect(20, (height - 20), 35, -int(lRel));
text("Light "+ l,5,(height - int(lRel) - 40 ));
}
void tempR(float t){
 stroke(255,255,255);
float tRel = map(t, 0, 50, 0, height - 40);
//println(tRel);
rect(100, (height - 20), 35, -int(tRel));
text("Temp "+ t ,85,(height - int(tRel) - 40 ));
}

void radioTemp(int a) {
  println("a radio Button event: "+a);
majmin = a;
  
     if(a == 1){
     majminTxt = " minor than ";
  }
  if(a == 2){
    majminTxt = " major than ";
  }
 
}
void radioCond(int a) {
  println("a radio Button event: "+a);
  cond = a;
  if(a == 1){
    condTxt = " turn conditioning ON";
  }
  if(a == 2){
    condTxt = " turn conditioning OFF";
  }
  
  
}

public void setRule(int theValue) {
  if(debounce ){
   if(majminTxt != null && condTxt != null){ 
  println("If temperature gets " + majminTxt + degrees +" degrees "+condTxt );
  String msg = ("If temperature gets " + majminTxt + degrees +condTxt );
 l.clear();
 ListBoxItem lbi = l.addItem(msg,1);
 
 lbi.setColorBackground(0xffff0000);
 
 majminR = majmin;
 condR = cond;
 degreesR = degrees;
   }else{
     
    println("you have to set all the parameters"); 
MsgBox("You have to set all the parameters","Error");
   }
  }
  debounce = true;

}
void MsgBox( String Msg, String Titel ){
  // Messages 
  javax.swing.JOptionPane.showMessageDialog ( null, Msg, Titel, javax.swing.JOptionPane.ERROR_MESSAGE  );

}

void toggle(boolean theFlag) {
  Controller tt = (cp5.getController("toggle"));

   
  if(theFlag==true) {
    //col = color(255);
    
    tt.setCaptionLabel("ON");
attivo = true;

  } else {
    //col = color(100);
   tt.setCaptionLabel("OFF"); 
   attivo = false;
    
  }
  println("a toggle event.");
}

void controlEvent(ControlEvent theEvent) {
  // ListBox is if type ControlGroup.
  // 1 controlEvent will be executed, where the event
  // originates from a ControlGroup. therefore
  // you need to check the Event with
  // if (theEvent.isGroup())
  // to avoid an error message from controlP5.

  if (theEvent.isGroup()) {
    // an event from a group e.g. scrollList
    println(theEvent.group().value()+" from "+theEvent.group());
  }
  
  if(theEvent.isGroup() && theEvent.name().equals("myList")){
    float test = theEvent.group().value();
    println("test "+test);
}
}

void applyRule(){
  if(attivo){
  if(majminR == 1){// min than
    if(t < degrees){
        if(condR == 1 && !statoCond){
          println("accendi");
          statoCond = true;
        }else if(condR==2 && statoCond){
          println("spegni");
          statoCond = false;
        }
    }   
    }else if(majminR == 2){
     if(t > degreesR){
        if(condR == 1 && !statoCond){
          println("accendi");
          statoCond = true;
          myPort.write(1);
        }else if(condR==2 && statoCond){
          println("spegni");
          statoCond = false;
          myPort.write(0);
        }
    } 
    }
  } 
    }

//public void controlEvent(ControlEvent theEvent) {
//  println(theEvent.getController().getInfo());
//
//}

