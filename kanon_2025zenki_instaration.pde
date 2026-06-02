import processing.serial.*;
import processing.sound.*;

Serial myPort;

SoundFile sound1;
SoundFile sound2;
SoundFile sound3;
SoundFile sound4;

float threshold = 10.0;

void setup() {

  size(400, 200);

  println(Serial.list());  
  myPort = new Serial(this, Serial.list()[0], 9600);
  myPort.bufferUntil('\n');

  sound1 = new SoundFile(this, "Canon_in_D_strings_quartet-viola.mp3");
  sound2 = new SoundFile(this, "Canon_in_D_strings_quartet-violin.mp3");
  sound3 = new SoundFile(this, "Canon_in_D_strings_quartet-chello.mp3");
  sound4 = new SoundFile(this, "Canon_in_D_strings_quartet-bass.mp3");
}

void draw() {
}


void serialEvent(Serial myPort) {

  String data = myPort.readStringUntil('\n');

  if (data == null) return;

  data = trim(data);

  String[] values = split(data, ',');

  if (values.length == 4) {

    float d1 = float(values[0]);
    float d2 = float(values[1]);
    float d3 = float(values[2]);
    float d4 = float(values[3]);

    println(d1, d2, d3, d4);

    if (d1 <= threshold && !sound1.isPlaying()) {
      sound1.play();
    }

    if (d2 <= threshold && !sound2.isPlaying()) {
      sound2.play();
    }

    if (d3 <= threshold && !sound3.isPlaying()) {
      sound3.play();
    }

    if (d4 <= threshold && !sound4.isPlaying()) {
      sound4.play();
    }
  }
}
