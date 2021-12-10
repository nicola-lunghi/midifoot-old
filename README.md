# Required Functionality
- Midi in/out-thru
- BLE midi
- midi over usb
- 6 switches
- 6 rgb led
- graphical display
- 2 foot pedal/footswitch
- optional:
  - 6 channel tb switch
  - buffer + tuner out
  - amp control
  - amp 
  - CV out?
  - tempo out?
  - touch switch?
  - LED display?
  - volume in/out?

- Supported Midi messages:
  - CC
  - PC
  - START/STOP
  - Tempo
  - note on/off
  - sysex?
  - MSB/LSB?
    
- switch function:
  - momentary
  - toggle
  - page up/down
  - tap tempo


- arpeggiator/midi pattern?
- emulate footswitch toggle/temporary
- footswitch curve
- copy/paste/move preset/buttons
- OTA
- factory reset
- templates/library
- custom color/ preset names
- preset
- midi channel
- Android / WEB app? + IOS? -> https://editor.morningstar.io/mcgen2
- LPM/batttery? / save on brownout battery operation
- mesh?

# Plan
- implement midi i/o over serial
- implement midi i/o over bluetooth
- handle buttons
- handle rgb led
- handle display
- handle display touch
- handle FOTA
- handle reset
- LPM
- menu
- settings
- copy/paste
- web app + rest api

