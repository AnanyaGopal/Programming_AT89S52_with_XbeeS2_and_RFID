# Programming_AT89S52_with_XbeeS2_and_RFID
## Concepts ##
- Serial programming code for the ATMEL 89S52, transmitting and receiving serially contiguously from Zigbee and RFID modules
- Programming LCD with AT89S52

## Problem statement - Project ## 
- Introducing a "Director unit" before the actual toll gate unit that can communicate with incoming traffic, tx and rx information to the actual toll gate, and let the incoming car know if it has enough balance to go through the tag lane, or should take the recharge lane.
- This reduces stagnant traffic on the high speed Tag lanes, enabling people with enough balance in their tags to cross smoothly.

## - Hardware - ##
- Vehicle unit has an RFID card

- Director unit has an RFID Card reader and an Xbee, and for display purposes, an LCD

- Toll gate unit has an Xbee

## Process ## 

1. Rfid card read by Director unit, send the TAG ID to Toll Gate,
2. Toll gate checks data base, and sends cash/tag lane info back to Director.
3. Director displays appropriate information to the Tag owner.


## Software used ##
- Keil microvision - ATMEL family
- Proteus for simulation
- XCTU - to configure zigbees for appropriate baud rates and start,stop bits.


# STEPS
- Compile code
- To simulate on software - create a similar circuit as shown on Proteus, free versions are available, and load hex codes
   into the vehicle codes. For serial transmissions, use serial console
   
- To simulate on hardware, burn hex codes into the 3 hardware component circuits to create whole system, 
  Give input from console (XCTU) to one zigbee to test
  