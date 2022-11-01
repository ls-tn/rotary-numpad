# rotary-numpad

Using an old rotary dial phone as a numeric keypad. No operators though, just the numbers.

[See it working on YouTube](https://www.youtube.com/watch?v=xyL7fjYyEtQ)

## Uses

- An Arduino Micro compatibe board. I used one [from KeeYes with **ATmega32U4**](https://www.amazon.de/gp/product/B07FXCTVQP/ref=ppx_yo_dt_b_asin_title_o00_s01?ie=UTF8&psc=1). 
  The microcontroller type in bold is important, if you want to use it in USB mode, hooked to a computer.
- The Arduino IDE and this piece of code

## About the rotary dial

I bought a phone on a local site for classifieds. The dial is a separate unit 
inside the phone with 3 wires. One is common (in my case it's the white one), 
the other two are the terminals for two switches.

One switch (on the green wire) is off by default, goes from off to on when you 
move the dial wheel. Also stays on until the wheel rotates back to the normal 
position. 

The other switch (brown wire) is on by default. Stays on while you rotate the 
wheel clockwise, but breaks the curcuit once for each number as it's spinning 
back to the normal position counter-clockwise. 3 breaks = the number 3. 9 breaks
= the number 9. 10 for zero.

The job is to count the short "circuit breaks" while the first switch is on, 
and then emit that number. More info: [Pulse dialing](https://en.wikipedia.org/wiki/Pulse_dialing)

## Wiring

[See the pin layout here](https://m.media-amazon.com/images/I/71VuVojNFbL._AC_SL1001_.jpg).

- Common wire (white) to VCC
- Pulse wire (brown) to Pin 9
- Op (green) wire to Pin 8
- 10K ohm "pull down" resistor between GND and Pin 8
- 10K ohm "pull down" resistor between GND and Pin 9

Launch

Open the code in the Arduino IDE, connect your Arduino board to a USB port 
and upload the code to the board.

**Important note:** Some boards do not support debugging. If you decide to 
debug with tactical outputs (Keyboard.print or .println), be very cautious.
You may face a hard time updating the code again as it will output the debug 
messages into the active window - the Arduino IDE.
