#define ndev 12 // numers of devices, like LEDs
#define nsteps 12 // number of steps in the primitive wave
#define scale 1 // enlargement of the wave e.g if the wave is {1,0} and the scale is 2 it becomes {1,1,0,0}
#define dt 80 // time between steps in miliseconds
#define phaseshift 1 // step difference between modules

#define clrbit(reg,bit) (reg & ~(1<<bit)) // to turn off a pin
#define setbit(reg,bit) (reg | (1<<bit)) // to turn on a pin

byte _pins[ndev] = {2, 3 , 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

int tsteps = scale * nsteps; // final number of steps
byte wave[nsteps] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // primite wave
byte wave2[scale * nsteps]; // final wave
byte _step = 0; // step index
volatile byte* port_config[] = { &PORTD, &PORTB, &PORTC};
byte portindex;
byte cons;

void generatewave() { // increases the resolution of the primitive wave by the scale factor
  for (int i = 0; i < tsteps; i++) {
    wave2[i] = wave[int(i / scale)];
  }
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
  _step = _step + 1;
  if (_step == tsteps) {
    _step = 0;

  }

}

void actuate() {

  for (int i = 0; i < ndev; i++) {

    int value = wave[(_step + (phaseshift * i)) % tsteps];
    int pin = _pins[i];

    if (pin < 8) {
      portindex = 0;
      cons = 0;
    }
    else if (pin < 14) {
      portindex = 1;
      cons = 8;
    }
    else {
      portindex = 2;
      cons = 14;
    }

    if (0 == value) {
      *port_config[portindex] = clrbit(*port_config[portindex], pin - cons);
    }
    else {
      *port_config[portindex] = setbit(*port_config[portindex], pin - cons);
    }
  }

}
