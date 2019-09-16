# Waves
A digital wave generator for a set of time controlled devices, with a constant dephase between each other.

It does not use digitalWrite, as it is too slow, so the PORTs are managed. Currently works with an Arduino UNO, usings PORTD, PORTB and PORT. You have to manually set the pins of the devices ordered in an array and the shape of the desired wave, aswell as other porperties.

phasewave2 is the same as phasewave1, only that it allows to operate with 2 waves.
