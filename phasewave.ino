#define ndev 12 // numers of devices, like LEDs
#define nsteps 12 // number of steps in the primitive wave
#define scale 1 // enlargement of the wave e.g if the wave is {1,0} and the scale is 2 it becomes {1,1,0,0}
#define dt 500// time between steps in miliseconds
#define phaseshift 2 // step difference between modules

#define clrbit(reg,bit) (reg & ~(1<<bit)) // to turn off a pin
#define setbit(reg,bit) (reg | (1<<bit)) // to turn on a pin

byte _pins[ndev] = {2, 3 , 4, 5, 6, 7, 13, 12, 11, 10, 9, 8};

int tsteps = scale * nsteps; // final number of steps
byte wave[nsteps] = {1, 1, 0,0,0,0,0,0,0,0,0,0}; // primite wave
byte wave2[scale * nsteps]; // final wave
byte _step = 0; // step index
volatile byte* port_config[] = { &PORTD, &PORTB, &PORTC};

void generatewave() { // increases the resolution of the primitive wave by the scale factor
  for (int i = 0; i < tsteps; i++) {
    wave2[i] = wave[int(i / scale)];
  }
}
void assign(byte pin, byte value) {
  byte division = pin/8;
  byte rest = pin % 8;
  *port_config[division] = value ? setbit(*port_config[division], rest) : clrbit(*port_config[division], rest);
}

void setup() {

  for (int i = 0; i < ndev; i++) {
    pinMode(_pins[i], OUTPUT);
  }
  generatewave();
}

void loop() {

  actuate();
  delay(dt);
  _step = (_step + 1)%tsteps;


}

void actuate() {

  for (int i = 0; i < ndev; i++) {
    assign(_pins[i], wave[(_step + (phaseshift * i)) % tsteps]);
  }

}
