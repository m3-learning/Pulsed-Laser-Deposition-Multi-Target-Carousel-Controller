# Pulsed-Laser-Deposition-Multi-Target-Carousel-Controller

Open source multi-target carousel controller for Neccera PLD System

Created by: The M3 Learning Group

All designs and code by: Ryan Forelli


![](https://github.com/ryanf123/Pulsed-Laser-Deposition-Multi-Target-Carousel-Controller/blob/main/renders/PLD_Controller_PCB_2021-Jun-19_05-58-52AM-000_CustomizedView16557687785.png)



## Components needed for PCB assembly
-   1x Custom PCB
-   2x A4988 stepper motor drivers
-   1x ATmega328P AVR microcontroller
-   5x 5mm DIP LEDs
-   1x Pin header set
-   1x [Molex 6 Circuit Wire Connector][1]
-   1x through hole pushbutton
-   1x 16 MHz crystal oscillator
-   2x 22pF ceramic capacitors
-   1x 10uF electrolytic capacitor
-   1x 100uF electrolytic capacitor
-   1x 10k through-hole resistor
-   1x 10k through-hole resistor
-   1x Assorted single-core jumper wires
-   1x [Standoffs][0] (optional)
-   1x Custom back plate (optional)
-   1x [USB to TTL Adapter][2]

## Installation Notes
-   Supply PCB with 5V supply from USB to TTL Adapter
-   Supply Stepper motor controller with 24V from Multi-Target Carousel Controller or other source
-   Only four Molex connector pins are used. Use PCB schematic for reference when wiring connectors to PCB

## Usage Instructions
-   Power PLD Controller module
-   Open LabVIEW pldsyscontrol.exe and run the Virtual Instrument (VI)
-   Select COM port
-   Home raster motor (does not home to a specific target)
-   Select target and begin use

[0]: https://www.amazon.com/Csdtylh-Male-Female-Standoff-Stainless-Assortment/dp/B06Y5TJXY1/ref=sr_1_3?dchild=1&keywords=standoff&qid=1620104015&sr=8-3
[1]: https://www.amazon.com/gp/product/B074M15FS1/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1
[2]: https://www.amazon.com/DSD-TECH-SH-U09C2-Debugging-Programming/dp/B07TXVRQ7V/ref=sr_1_8?dchild=1&keywords=FT232RL+USB+to+Serial&qid=1616559163&s=electronics&sr=1-8#customerReviews
