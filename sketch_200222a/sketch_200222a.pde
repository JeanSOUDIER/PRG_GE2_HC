import android.content.Intent;
import android.os.Bundle;
import ketai.net.bluetooth.*;
import ketai.ui.*;
import ketai.net.*;
import controlP5.*;

int taille = 800;

ControlP5 cp5;
PFont fontMy;
boolean bReleased = true; //no permament sending when finger is tap
KetaiBluetooth bt;
boolean isConfiguring = true;
String info = "";
String asd = "";
KetaiList klist;
ArrayList devicesDiscovered = new ArrayList();
Slider2D s;
byte data[] = {'A', 'A', 'A'};
ControlTimer c;
Textlabel t;
int Temp = 0;

//********************************************************************
// The following code is required to enable bluetooth at startup.
//********************************************************************
void onCreate(Bundle savedInstanceState) {
 super.onCreate(savedInstanceState);
 bt = new KetaiBluetooth(this);
}
 
void onActivityResult(int requestCode, int resultCode, Intent data) {
 bt.onActivityResult(requestCode, resultCode, data);
}
 
void setup() {
 size(displayWidth, displayHeight);
 frameRate(10);
 orientation(PORTRAIT);
 //background(0);
 
 //start listening for BT connections
 bt.start();
 //at app start select device…
 isConfiguring = true;
 //font size
 fontMy = createFont("SansSerif", 40);
 noStroke();
 textFont(fontMy);
 cp5 = new ControlP5(this);
 c = new ControlTimer();
 t = new Textlabel(cp5,"--",100,100);
 c.setSpeedOfTime(1);
 s = cp5.addSlider2D("wave")
         .setPosition(width/2-taille/2,height/2-taille/2)
         .setSize(taille,taille)
         .setMinMax(0,0,200,200)
         .setValue(100,100)
         ;
  cp5.addButton("colorA")
     .setValue(0)
     .setPosition(100,100)
     .setSize(200,100)
     ;
         
  smooth();
  background(0, 100, 0);
}
 
void draw() {
 //at app start select device
 if (isConfiguring) {
  ArrayList names;
  //background(78, 93, 75);
  klist = new KetaiList(this, bt.getPairedDeviceNames());
  isConfiguring = false;
 } else {
  //background(0,50,0);
  if((mousePressed) && (bReleased == true)) {
   //send with BT
   //first tap off to send z next message
   bReleased = false;
  }
  if(mousePressed == false) {
   bReleased = true; //finger is up
  }
  //print received data
  fill(255);
  noStroke();
  textAlign(LEFT);
  text(info, 20, 104);
 }
 if(millis()-Temp > 20) {
   Temp = millis();
   float y0 = s.getArrayValue()[0];
   float y1 = s.getArrayValue()[1];
   data[0] = 'V';
   data[1] = (byte)(y0);
   bt.broadcast(data);
   data[0] = 'A';
   data[1] = (byte)(y1);
   bt.broadcast(data);
 }
}
 
void onKetaiListSelection(KetaiList klist) {
 String selection = klist.getSelection();
 bt.connectToDeviceByName(selection);
 //dispose of list for now
 klist = null;
}
 
//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data) {
 if (isConfiguring)
 return;
 //received
 int CC = data[0]+data[1];
 if(CC == data[2]) {
  if(data[0] == 'P' && data[1] == 'I') {
   info = "PING";
  } else if(data[0] == 'B' && data[1] == '1') {
   background(255,0,0);
  } else if(data[0] == 'B' && data[1] == '0') {
   background(0, 100, 0);
  } else if(data[0] == 'E') {
   println("error : "+(char)(data[1]));
  } else {
   println("error msg"); 
  }
 } else {
  println("error CC"); 
 }
}

void controlEvent(ControlEvent theControlEvent) {
  if(theControlEvent.isFrom("wave")) {
    float y0 = s.getArrayValue()[0];
    float y1 = s.getArrayValue()[1];
    print(y0);
    print(" ");
    println(y1);
    data[0] = 'V';
    data[1] = (byte)(y0);
    bt.broadcast(data);
    data[0] = 'A';
    data[1] = (byte)(y1);
    bt.broadcast(data);
  } else {
    data[0] = 'P';
    data[1] = 'I';
    bt.broadcast(data);
    info = "";
  }
}
 