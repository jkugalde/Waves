# Waves
A wave generator for a set of time controlled devices, with a constant dephase between each other.

It does not use digitalWrite, as it is too slow, so the PORTs are managed. Currently works with an Arduino UNO, usings PORTD and PORTB, not including pin0 or pin1. You have to manually set the pins of the devices ordered in an array and the shape of the desired wave, aswell as other porperties.
