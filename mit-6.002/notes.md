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

## lec 15

LC circuits are introduced we see how the energy stored is transferred from the capacitor to the inductor and viceversa and it oscillates. The peak voltage is also higher than the input voltage this is said to be an important concept when we want to step up dc voltage and it is used in converters.
We then see RLC circuits and see how the resistor dissipates energy essentially introducing a decay in the output oscillation. We see how it responds to varying level of resitance, too much then underdamped no oscillation only decay, underdamped multiple oscillations, critically damped only one oscillation.

## Lec 16

Response of LC and RLC circuits to sinusoidal input is studied. This is motivated by the fact than we can use fourier to convert any function to its sinusoidal components.

## Lec 17

We now learn to solve the circuits using complex analysis and just take the real part everywhere as the math is so much simpler. Remember this is only for the math we are only concerned with the real parts everywhere. we also see graphs with relation to frequency now as the circuits behave differntly wrt frequency of input not only time.

## lec 18

We see how to construct filters very easily. We can construct high pass and low pass filters using RC or RL circuits. We also see how to construct band pass filter using RLC more importantly we also see how to construct output responses wery easily by seeing how the circuits behave at vey low and very high frequencies(eg capacitor bocomes short at high freq and inductor becomes open also vice versa for low freq).

We use band pass filter to listen to a particular frequency station in a radio

## lec 19

Opamp is introduced. It is told to be the workhorse of the analog electronics industry Anant compares it to printf it is such an important abstraction.

An input is applied to an opamp and it is shown how sensitive the gain is to external factors like temperature.

We see how using feedback we can get rid of the tremondously unpredictable and large internal gain and instead create a custom gain by attaching it to a couple of resistors.
