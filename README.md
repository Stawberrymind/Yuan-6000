<img width="463" height="286" alt="image" src="https://github.com/user-attachments/assets/110cd321-0ad9-45a0-8d74-5e02288eb51d" />


# Yuan Converter 6000- A handheld currency converter

A handheld currency converter (made with left-handed people in mind :) ), that converts currency on the spot, it features a Colour TFT Circular display with an iPod-like rotary encoder. Also displays your WeChat QR Code!

## Why did I make it?
I don't like the concept of currency converters on your phone! So I decided to make a handheld offline converter that also shows my WeChat QR Code
 
## Components Required for the Build
I have listed everything in the project; you can find the same in the BOM

| No.   | Quantity | Comment                                             | Footprint                                                                  | Link                                                                                                                                                       | Price | Total Cost(USD) |
| ----- | -------- | --------------------------------------------------- | -------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------- | ----- | --------------- |
| 1     | 1        | 2.4GHz                                              | BULETM-SMD_ESP32-S3-MINI-1-N8                                              | https://www.electropi.in/espressif-esp32-s3-mini-1-n8-module                                                                                               | 4.05  | 4.05            |
| 2     | 1        | Adafruit ANO Rotary Navigation Encoder Breakout PCB | Adafruit ANO 6311 Rotary Navigation Encoder Breakout with Soldered Control | https://www.adafruit.com/product/6311                                                                                                                      | 10.95 | 10.95           |
| 3     | 1        | AP2112K-3.3TRG1                                     | SOT-23-5_L2.9-W1.6-P0.95-LS2.8-BR                                          | https://robu.in/product/ap2202k-3-3trg1-diodes-inc-ldo-fixed-3-3v-0-15a-40-to-125deg-c/                                                                    | 0.14  | 0.14            |
| 4     | 1        | B2B-XH-A(LF)(SN)                                    | CONN-TH_B2B-XH-A-LF-SN                                                     | https://robu.in/product/b2b-xh-alfsn-jst-1x2p-2p-xh-tin-2-25%E2%84%8385%E2%84%83-3a-1-2-5mm-brass-direct-insert-pluginp2-5mm-wire-to-board-connector-rohs/ | 0.049 | 0.049           |
| 5     | 1        | GC9A01 Round Display                                | GC9A01_1.28_240x240-Slim                                                   | https://robu.in/product/goldenmorning-gc9a01-7p-240x240-spi-1-28-inch-round-display-module                                                                 | 5.16  | 5.16            |
| 6     | 1        | TP4056                                              | ESOP-8_L4.9-W3.9-P1.27-LS6.0-BL-EP-4                                       | https://robu.in/product/1-month-warranty-1253/                                                                                                             | 0.14  | 0.14            |
| 7     | 1        | TYPE-C 16PIN 2MD(073)                               | USB-C-SMD_TYPE-C-16PIN-2MD-073                                             | https://www.ktron.in/product/16-pin-usb-type-c-connector-smd                                                                                               | 0.049 | 0.049           |
| 8     | 2        | 5.1k?                                               | RES-TH_BD2.3-L6.5-P10.50-D0.5                                              | https://jlcpcb.com/partdetail/VO-MF1_4W_1K_1_ST52/C2903245                                                                                                 | 0.01  | 0.02            |
| 9     | 2        | 10k?                                                | R0402                                                                      | https://jlcpcb.com/partdetail/HKR_Hong_Kong_Resistors-RCT0510KFLF/C702829                                                                                  | 0.01  | 0.02            |
| 10    | 2        | LED_0402-R                                          | LED0402-RD_YELLOW                                                          | https://robu.in/product/0402-surface-mount-led-red-50pcs/                                                                                                  | 0.01  | 0.02            |
| 11    | 3        | 1k?                                                 | R0603                                                                      | https://jlcpcb.com/parts/componentSearch?searchTxt=PTFR0603B1K00N9                                                                                         | 0.02  | 0.06            |
| 12    | 3        | 10uF                                                | C0603                                                                      | https://jlcpcb.com/partdetail/FOJAN-FCC0603X106K100CT/C5137565                                                                                             | 0.05  | 0.15            |
| 13    | 3        | 100nF                                               | C0603                                                                      | https://jlcpcb.com/partdetail/1943-CL10B104KB8NNNC/C1591                                                                                                   | 0.05  | 0.15            |
| 14    | 3        | TS-1088-AR02016                                     | SW-SMD_L3.9-W3.0-P4.45                                                     | https://jlcpcb.com/partdetail/XUNPU-TS_1088AR02016/C720477                                                                                                 | 0.06  | 0.18            |
| 15    | 6        | M1.4x 6mm Phillips head screw                       | \-                                                                         | https://onlyscrews.in/products/m1-4-x-6mm-phillips-round-head-laptop-and-mobile-screw-dia-1-4mm-length-6mm                                                 | 0.05  | 0.3             |
| 16    | 6        | M1.2x 3mm Phillips head screw                       | \-                                                                         | https://onlyscrews.in/products/m1-2-x-3mm-phillips-round-head-laptop-screw-dia-1-2mm-length-3mm                                                            | 0.05  | 0.3             |
| 17    | 5        | PCB                                                 | \-                                                                         | https://cart.jlcpcb.com/quote                                                                                                                              | 7     | 7               |
| Total |          |                                                     |                                                                            |                                                                                                                                                            |       | 28.738 USD      |


## PCB and Schematic
I designed it in EasyEDA. You can find the Gerber files in the repo. The schematic is:

<img width="764" height="329" alt="image" src="https://github.com/user-attachments/assets/bb1c616f-7533-46ef-b747-939c7186fe08" />



And the PCB is a 4-layer PCB:

<img width="1027" height="489" alt="image" src="https://github.com/user-attachments/assets/98eafb37-c526-47ea-a1bb-c2b7a000e1bc" />



3D Render of the PCB:

<img width="555" height="459" alt="image" src="https://github.com/user-attachments/assets/97492e1c-5766-490d-95a7-97fe62e12bb7" />


## Case
Top and bottom view of the Case:

<img width="551" height="471" alt="image" src="https://github.com/user-attachments/assets/649b2e46-0262-4bf3-95b8-32e4835f0b29" />


## Assembly 

1. Solder all the components onto the PCB. Using the pictures above as a reference, if you want, you can order a stencil and hot-air solder your MCU
2. Put the LiPo into the bottom case and connect it to the JST on the bottom of the PCB
3. Screw the PCB into the Case using an M1.2 x 3 mm Phillips head screw 
4. Put on the Top case, aligning the Screen and Rotary Encoder
5. Connect to the USB Port, and  press the switch in the middle of the Case, which turns it on
6. Flash the firmware file onto the microcontroller

Note: Setup your currency, conversion rate, QR code in the firmware :)




## Credits

the fallout huddle

## Zine

<img width="598" height="856" alt="image" src="https://github.com/user-attachments/assets/b00e91b8-bed5-4238-9df4-6835463c2161" />





