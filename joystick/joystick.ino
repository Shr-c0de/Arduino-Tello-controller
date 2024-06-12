void setup(){
  Serial.begin(115200);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}

class SmoothingFilter {
  private:
    const int numReadings;
    int *readings;
    int readIndex;
    int total;
    int average;

  public:
    // Constructor
    SmoothingFilter() : numReadings(10), readIndex(0), total(0), average(0) {
      readings = new int[numReadings];
      for (int i = 0; i < numReadings; i++) {
        readings[i] = 0;
      }
    }
    SmoothingFilter(int numReadings) : numReadings(numReadings), readIndex(0), total(0), average(0) {
      readings = new int[numReadings];
      for (int i = 0; i < numReadings; i++) {
        readings[i] = 0;
      }
    }

    // Destructor
    ~SmoothingFilter() {
      delete[] readings;
    }


    int addReading(int newReading) {
      total = total - readings[readIndex];
      readings[readIndex] = newReading;
      total = total + readings[readIndex];
      readIndex = (readIndex + 1) % numReadings;
      average = total/numReadings;
      return average;
    }
};

SmoothingFilter height, spin, front, side;
int fun1(){
  int in = analogRead(A2);
  if(in > 527) return map(in, 527, 1022, 0, 100);
  else return map(in, 0, 527, -100, 0);
}
void loop() {
  int x1 =   side.addReading(map(analogRead(A0)-3, 0, 1020, -100, 100)); //side
  int y1 =  front.addReading(map(analogRead(A1)-3, 0, 1020, -100, 100)); // front
  int x2 =   spin.addReading(fun1()); //rotate left/ right  map(analogRead(A2)-15, -5, 1000, -100, 100)
  int y2 = height.addReading(map(analogRead(A3)+10, 0, 1030, -100, 100)); //up/down
  char s[100];
  sprintf(s, "rc %d %d %d %d", x1, y1, x2, y2);
  Serial.println(s);

  delay(10);
}
