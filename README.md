# Arduino-Matrix-Face
Arduino project to make a led Matrix face that can do several different things
The Face requires the lbiraries from both https://github.com/FastLED/FastLED and https://github.com/Jorgen-VikingGod/LEDMatrix to work
The LED Martix is a generic WS2812B panel from ALiExpress.
THe code is meant to run on a arduino Nano but a MEga works as well.
The system uses 4 buttons for control of the brightness, mouth choice and ebrow choice.
The Panel data is connect to pin 6 and the buttons are pin 7,8,9,10
button 8 and 9 are for brightness
button 7 is mouth cycle and button 10 is eyebrow cycle.


THe code is very modular as I tried my best to sperate each action into spereate parts to make it look very nice and easy to add to.
the pupils are set to randomly look in differnt directions.  THe system will test the entire panel roughly every 5-15 minutes.  It will run all leds through each major coclor to allow to see any defects.
pressing button 7 and 10 at the same time will put the system into a sleep mode where the leds are all off until they are pushed again.  When woken up or plugged in it will run a test cycle of colors on all the leds
