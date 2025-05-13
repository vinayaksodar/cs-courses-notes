# Big picture

We are building abstractions from physics all the way to digital and analog components like logic gates opamps etc which are the building blocks of all digital and analog systems. This enables us to build digital systems with a simplified set of abstraction layers without having to worry about the underlying layers.

## Lec 1-3

We form our first abstraction using lumped models of real systems and go from maxwells equations to kcl and kvl and use them to analyse circuits. The below are some of the methods commonly used to analyse the circuits.

- KCL, KVL
- Intution based simplification at certain nodes/regions.
- Node method(workhorse of industry learn this one method properly)
- Methods that can be applied to only linear circuits(i.e only resistors no inductors or capacitors all voltage and current variables that we want to solve for are linear.) but enable us to solve problems quickly(Superposition, Thevnin, Norton)

## Lec 4-5

The use of digital circuits to transmit signals is motivated by using an example that shows that shows how digital signals are more resistant to noise as they operate only at high and low values.
Nand nor inverter etc are designed from a switch(mosfet) and a voltage source this is why we see nands and nors more than ands and ors as they are made from primitives.

## Lec 6

Digital circuits are inherently nonlinear as the voltages jump from 0 - 1 but if you fix all the switches at a given point in time it will behave like a linear circuit. You can apply the same linear analysis techniques above.
We see how some of our commonly used devices like led are inherently nonlinear, to pass a signal through a led we see the small signal model and operate it in a small region to essentialy make it linear and pass music signals via light.

## lec 7-9

We build up an amplifier by first seeing that a mosfet can act not only as a switch but in its saturation region acts as a current source(voltage dependent) and so our nor circuit that we saw earlier is now an amplifier.
we use two models to model the mosfet the sr model (when we commonly use it as a switch in digital circuits) and the scs model(short-current source when we use it in its saturation region commonly in analog circuits)

## lec 13

We finally see capacitor it is introduced by showing an inveter operating on a waveform but the output waveform is a tiny bit ahead in time so there is a tiny delay between when the signal to switch comes in and when the switch actually happens this is told as a limiting factor in all processors as we are limited by how fast we can switch from 0 to 1.
This is due to an internal capacitor in the mosfet which is used for switching.
