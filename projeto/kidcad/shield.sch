EESchema Schematic File Version 4
LIBS:shield-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Galileo Gen2 Shield - Interface with Quanser 2DSFJ"
Date "2019-10-17"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Crystal_Small Y1
U 1 1 5DA970E9
P 2500 1550
F 0 "Y1" V 2454 1638 50  0000 L CNN
F 1 "30MHz" V 2545 1638 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 2500 1550 50  0001 C CNN
F 3 "~" H 2500 1550 50  0001 C CNN
	1    2500 1550
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R1
U 1 1 5DA97C4B
P 2950 1550
F 0 "R1" H 3018 1596 50  0000 L CNN
F 1 "1M" H 3018 1505 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 2950 1550 50  0001 C CNN
F 3 "~" H 2950 1550 50  0001 C CNN
	1    2950 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5DA988D9
P 2200 1300
F 0 "C1" V 1948 1300 50  0000 C CNN
F 1 "22pF" V 2039 1300 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.8mm_W2.6mm_P2.50mm" H 2238 1150 50  0001 C CNN
F 3 "~" H 2200 1300 50  0001 C CNN
	1    2200 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 1650 2500 1800
Wire Wire Line
	2950 1800 2950 1650
Wire Wire Line
	2950 1450 2950 1300
Wire Wire Line
	2950 1300 3200 1300
Wire Wire Line
	3200 1300 3200 1500
Wire Wire Line
	3200 1500 3750 1500
Wire Wire Line
	3750 1650 3200 1650
Wire Wire Line
	3200 1650 3200 1800
Wire Wire Line
	3200 1800 2950 1800
Connection ~ 2950 1800
Wire Wire Line
	2050 1300 1900 1300
Wire Wire Line
	1900 1300 1900 1800
Wire Wire Line
	2350 1800 2500 1800
Connection ~ 2500 1800
Wire Wire Line
	2500 1800 2950 1800
Wire Wire Line
	2950 1300 2500 1300
Connection ~ 2950 1300
Wire Wire Line
	2500 1450 2500 1300
Connection ~ 2500 1300
Wire Wire Line
	2500 1300 2350 1300
Wire Wire Line
	1900 1800 2050 1800
$Comp
L Device:C C2
U 1 1 5DA991A5
P 2200 1800
F 0 "C2" V 2452 1800 50  0000 C CNN
F 1 "22pF" V 2361 1800 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.8mm_W2.6mm_P2.50mm" H 2238 1650 50  0001 C CNN
F 3 "~" H 2200 1800 50  0001 C CNN
	1    2200 1800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3500 2650 3500 1800
Wire Wire Line
	3500 1800 3750 1800
$Comp
L power:GND #PWR0102
U 1 1 5DAAA2BE
P 3500 2650
F 0 "#PWR0102" H 3500 2400 50  0001 C CNN
F 1 "GND" H 3505 2477 50  0000 C CNN
F 2 "" H 3500 2650 50  0001 C CNN
F 3 "" H 3500 2650 50  0001 C CNN
	1    3500 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2100 3750 2100
Wire Wire Line
	3750 2250 3150 2250
Wire Wire Line
	3750 2400 3150 2400
Wire Wire Line
	4550 1500 4750 1500
Wire Wire Line
	4750 1500 4750 1300
Text GLabel 3150 1950 0    50   Input ~ 0
SS_ENC1
Text GLabel 3150 2100 0    50   Input ~ 0
SCK
Text GLabel 3150 2250 0    50   Input ~ 0
MISO
Text GLabel 3150 2400 0    50   Input ~ 0
MOSI
Text GLabel 4950 1800 2    50   Input ~ 0
A_ENC1
Text GLabel 4950 1950 2    50   Input ~ 0
B_ENC1
Text GLabel 4950 1650 2    50   Input ~ 0
EN_ENC1
$Comp
L micros:LS7366R U1
U 1 1 5DA9333B
P 4150 1250
F 0 "U1" H 4150 1265 50  0000 C CNN
F 1 "LS7366R" H 4150 1174 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 4150 -50 50  0001 C CNN
F 3 "" H 4150 -50 50  0001 C CNN
	1    4150 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1650 4950 1650
Wire Wire Line
	4550 1800 4950 1800
Wire Wire Line
	4550 1950 4950 1950
NoConn ~ 4550 2100
NoConn ~ 4550 2250
NoConn ~ 4550 2400
$Comp
L Device:Crystal_Small Y2
U 1 1 5DABFDF8
P 2500 3650
F 0 "Y2" V 2454 3738 50  0000 L CNN
F 1 "30MHz" V 2545 3738 50  0000 L CNN
F 2 "Crystal:Crystal_HC49-U_Vertical" H 2500 3650 50  0001 C CNN
F 3 "~" H 2500 3650 50  0001 C CNN
	1    2500 3650
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R2
U 1 1 5DABFE02
P 2950 3650
F 0 "R2" H 3018 3696 50  0000 L CNN
F 1 "1M" H 3018 3605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" H 2950 3650 50  0001 C CNN
F 3 "~" H 2950 3650 50  0001 C CNN
	1    2950 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5DABFE0C
P 2200 3400
F 0 "C3" V 1948 3400 50  0000 C CNN
F 1 "22pF" V 2039 3400 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.8mm_W2.6mm_P2.50mm" H 2238 3250 50  0001 C CNN
F 3 "~" H 2200 3400 50  0001 C CNN
	1    2200 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	2500 3750 2500 3900
Wire Wire Line
	2950 3900 2950 3750
Wire Wire Line
	2950 3550 2950 3400
Wire Wire Line
	2950 3400 3200 3400
Wire Wire Line
	3200 3400 3200 3600
Wire Wire Line
	3200 3600 3750 3600
Wire Wire Line
	3750 3750 3200 3750
Wire Wire Line
	3200 3750 3200 3900
Wire Wire Line
	3200 3900 2950 3900
Connection ~ 2950 3900
Wire Wire Line
	2050 3400 1900 3400
Wire Wire Line
	1900 3400 1900 3900
$Comp
L power:GND #PWR0104
U 1 1 5DABFE22
P 1900 3900
F 0 "#PWR0104" H 1900 3650 50  0001 C CNN
F 1 "GND" H 1905 3727 50  0000 C CNN
F 2 "" H 1900 3900 50  0001 C CNN
F 3 "" H 1900 3900 50  0001 C CNN
	1    1900 3900
	1    0    0    -1  
$EndComp
Connection ~ 1900 3900
Wire Wire Line
	2350 3900 2500 3900
Connection ~ 2500 3900
Wire Wire Line
	2500 3900 2950 3900
Wire Wire Line
	2950 3400 2500 3400
Connection ~ 2950 3400
Wire Wire Line
	2500 3550 2500 3400
Connection ~ 2500 3400
Wire Wire Line
	2500 3400 2350 3400
Wire Wire Line
	1900 3900 2050 3900
$Comp
L Device:C C4
U 1 1 5DABFE36
P 2200 3900
F 0 "C4" V 2452 3900 50  0000 C CNN
F 1 "22pF" V 2361 3900 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.8mm_W2.6mm_P2.50mm" H 2238 3750 50  0001 C CNN
F 3 "~" H 2200 3900 50  0001 C CNN
	1    2200 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3150 4200 3750 4200
Wire Wire Line
	3750 4350 3150 4350
Wire Wire Line
	3750 4500 3150 4500
Wire Wire Line
	3150 4050 3750 4050
Wire Wire Line
	4550 3600 4750 3600
Wire Wire Line
	4750 3600 4750 3400
Text GLabel 3150 4050 0    50   Input ~ 0
SS_ENC2
Text GLabel 3150 4200 0    50   Input ~ 0
SCK
Text GLabel 3150 4350 0    50   Input ~ 0
MISO
Text GLabel 3150 4500 0    50   Input ~ 0
MOSI
Text GLabel 4950 3900 2    50   Input ~ 0
A_ENC2
Text GLabel 4950 4050 2    50   Input ~ 0
B_ENC2
Text GLabel 4950 3750 2    50   Input ~ 0
EN_ENC2
$Comp
L micros:LS7366R U2
U 1 1 5DABFE63
P 4150 3350
F 0 "U2" H 4150 3365 50  0000 C CNN
F 1 "LS7366R" H 4150 3274 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm" H 4150 2050 50  0001 C CNN
F 3 "" H 4150 2050 50  0001 C CNN
	1    4150 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3750 4950 3750
Wire Wire Line
	4550 3900 4950 3900
Wire Wire Line
	4550 4050 4950 4050
NoConn ~ 4550 4200
NoConn ~ 4550 4350
NoConn ~ 4550 4500
$Comp
L power:+5V #PWR0103
U 1 1 5DAD29EB
P 4750 3400
F 0 "#PWR0103" H 4750 3250 50  0001 C CNN
F 1 "+5V" H 4765 3573 50  0000 C CNN
F 2 "" H 4750 3400 50  0001 C CNN
F 3 "" H 4750 3400 50  0001 C CNN
	1    4750 3400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 5DAD3F03
P 4750 1300
F 0 "#PWR0106" H 4750 1150 50  0001 C CNN
F 1 "+5V" H 4765 1473 50  0000 C CNN
F 2 "" H 4750 1300 50  0001 C CNN
F 3 "" H 4750 1300 50  0001 C CNN
	1    4750 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1950 3750 1950
$Comp
L power:GND #PWR0105
U 1 1 5DB4D80C
P 3500 4750
F 0 "#PWR0105" H 3500 4500 50  0001 C CNN
F 1 "GND" H 3505 4577 50  0000 C CNN
F 2 "" H 3500 4750 50  0001 C CNN
F 3 "" H 3500 4750 50  0001 C CNN
	1    3500 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 3900 3500 3900
Wire Wire Line
	3500 3900 3500 4750
$Comp
L power:GND #PWR0101
U 1 1 5DB92F56
P 1900 1800
F 0 "#PWR0101" H 1900 1550 50  0001 C CNN
F 1 "GND" H 1905 1627 50  0000 C CNN
F 2 "" H 1900 1800 50  0001 C CNN
F 3 "" H 1900 1800 50  0001 C CNN
	1    1900 1800
	1    0    0    -1  
$EndComp
Connection ~ 1900 1800
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5DB93A9F
P 6450 1600
F 0 "#FLG0101" H 6450 1675 50  0001 C CNN
F 1 "PWR_FLAG" H 6450 1773 50  0000 C CNN
F 2 "" H 6450 1600 50  0001 C CNN
F 3 "~" H 6450 1600 50  0001 C CNN
	1    6450 1600
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5DB93F29
P 6900 1700
F 0 "#FLG0102" H 6900 1775 50  0001 C CNN
F 1 "PWR_FLAG" H 6900 1873 50  0000 C CNN
F 2 "" H 6900 1700 50  0001 C CNN
F 3 "~" H 6900 1700 50  0001 C CNN
	1    6900 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	6900 1700 6900 1600
Wire Wire Line
	6450 1600 6450 1700
$Comp
L power:GND #PWR0112
U 1 1 5DB99A2C
P 6450 1700
F 0 "#PWR0112" H 6450 1450 50  0001 C CNN
F 1 "GND" H 6455 1527 50  0000 C CNN
F 2 "" H 6450 1700 50  0001 C CNN
F 3 "" H 6450 1700 50  0001 C CNN
	1    6450 1700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 5DB9A00E
P 6900 1600
F 0 "#PWR0113" H 6900 1450 50  0001 C CNN
F 1 "+5V" H 6915 1773 50  0000 C CNN
F 2 "" H 6900 1600 50  0001 C CNN
F 3 "" H 6900 1600 50  0001 C CNN
	1    6900 1600
	1    0    0    -1  
$EndComp
Text GLabel 8250 1550 2    50   Input ~ 0
B_ENC1
Text GLabel 8250 1650 2    50   Input ~ 0
A_ENC1
Text GLabel 8250 1750 2    50   Input ~ 0
GND
Text GLabel 9100 1550 2    50   Input ~ 0
B_ENC2
Text GLabel 9100 1650 2    50   Input ~ 0
A_ENC2
Text GLabel 9100 1750 2    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 5DC8B140
P 9750 1650
F 0 "J3" H 9858 1931 50  0000 C CNN
F 1 "Conn_01x03_Male" H 9858 1840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9750 1650 50  0001 C CNN
F 3 "~" H 9750 1650 50  0001 C CNN
	1    9750 1650
	1    0    0    -1  
$EndComp
Text GLabel 9950 1550 2    50   Input ~ 0
LIMIT_1
Text GLabel 9950 1650 2    50   Input ~ 0
LIMIT_2
Text GLabel 9950 1750 2    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5DC9D2F8
P 8050 1650
F 0 "J1" H 8158 1931 50  0000 C CNN
F 1 "Conn_01x04_Male" H 8158 1840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8050 1650 50  0001 C CNN
F 3 "~" H 8050 1650 50  0001 C CNN
	1    8050 1650
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5DC9E500
P 8900 1650
F 0 "J2" H 9008 1931 50  0000 C CNN
F 1 "Conn_01x04_Male" H 9008 1840 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8900 1650 50  0001 C CNN
F 3 "~" H 8900 1650 50  0001 C CNN
	1    8900 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1850 9100 2100
Wire Wire Line
	8250 2100 8250 1850
Wire Wire Line
	9100 2100 8650 2100
$Comp
L power:+5V #PWR0107
U 1 1 5DD0B46D
P 8650 2100
F 0 "#PWR0107" H 8650 1950 50  0001 C CNN
F 1 "+5V" H 8665 2273 50  0000 C CNN
F 2 "" H 8650 2100 50  0001 C CNN
F 3 "" H 8650 2100 50  0001 C CNN
	1    8650 2100
	1    0    0    -1  
$EndComp
Connection ~ 8650 2100
Wire Wire Line
	8650 2100 8250 2100
Text Notes 3650 6800 2    50   ~ 0
MOTOR_GND
Text Notes 3650 6650 2    50   ~ 0
MOTOR_VDD
Text Notes 3650 6500 2    50   ~ 0
PWR_VDD
Text Notes 3650 6350 2    50   ~ 0
PWR_GND
$Comp
L power:GND #PWR0111
U 1 1 5DB8B5E6
P 4750 6800
F 0 "#PWR0111" H 4750 6550 50  0001 C CNN
F 1 "GND" H 4755 6627 50  0000 C CNN
F 2 "" H 4750 6800 50  0001 C CNN
F 3 "" H 4750 6800 50  0001 C CNN
	1    4750 6800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5DB8AEF7
P 4750 6650
F 0 "#PWR0110" H 4750 6500 50  0001 C CNN
F 1 "+5V" H 4765 6823 50  0000 C CNN
F 2 "" H 4750 6650 50  0001 C CNN
F 3 "" H 4750 6650 50  0001 C CNN
	1    4750 6650
	1    0    0    -1  
$EndComp
Text GLabel 4750 5750 2    50   Input ~ 0
EN_PWM_R
Text GLabel 4750 5900 2    50   Input ~ 0
EN_PWM_L
Wire Wire Line
	4500 6800 4750 6800
Wire Wire Line
	4500 6650 4750 6650
Text GLabel 4750 6200 2    50   Input ~ 0
PWM
Wire Wire Line
	4500 5900 4750 5900
$Comp
L micros:IBT-2 U4
U 1 1 5DB6BC25
P 5350 5800
F 0 "U4" V 5035 4575 50  0000 C CNN
F 1 "IBT-2" V 5126 4575 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x04_P2.54mm_Horizontal" H 5050 4550 50  0001 C CNN
F 3 "" H 5050 4550 50  0001 C CNN
	1    5350 5800
	0    1    1    0   
$EndComp
Wire Notes Line
	2950 7150 5300 7150
Wire Notes Line
	5300 7150 5300 5300
Wire Notes Line
	2950 5300 2950 7150
Wire Notes Line
	2950 5300 5300 5300
Wire Notes Line
	1550 5000 1550 3050
Wire Notes Line
	1550 3050 5550 3050
Wire Notes Line
	1550 5000 5550 5000
Wire Notes Line
	5550 3050 5550 5000
Wire Notes Line
	5550 2900 1550 2900
Wire Notes Line
	1550 2900 1550 850 
Wire Notes Line
	5550 850  5550 2900
Wire Notes Line
	1550 850  5550 850 
Connection ~ 7100 5100
Wire Wire Line
	7100 5000 7100 5100
Wire Wire Line
	7200 5000 7100 5000
Wire Wire Line
	7100 5200 7200 5200
Connection ~ 7100 5200
Wire Wire Line
	7100 5100 7100 5200
Wire Wire Line
	7200 5100 7100 5100
Wire Wire Line
	6700 5200 7100 5200
Wire Wire Line
	6700 5200 6700 5350
Wire Wire Line
	7100 5650 7100 5800
Connection ~ 7100 5650
Wire Wire Line
	7100 5400 7100 5650
Wire Wire Line
	7200 5400 7100 5400
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5DC82E5E
P 7100 5650
F 0 "#FLG0103" H 7100 5725 50  0001 C CNN
F 1 "PWR_FLAG" H 7100 5823 50  0000 C CNN
F 2 "" H 7100 5650 50  0001 C CNN
F 3 "~" H 7100 5650 50  0001 C CNN
	1    7100 5650
	1    0    0    1   
$EndComp
Wire Wire Line
	7200 5500 6950 5500
$Comp
L power:+5V #PWR0109
U 1 1 5DB373F9
P 6950 5500
F 0 "#PWR0109" H 6950 5350 50  0001 C CNN
F 1 "+5V" H 6965 5673 50  0000 C CNN
F 2 "" H 6950 5500 50  0001 C CNN
F 3 "" H 6950 5500 50  0001 C CNN
	1    6950 5500
	1    0    0    -1  
$EndComp
$Comp
L arduino:Arduino_Uno_Shield XA1
U 1 1 5DBC481F
P 8500 4450
F 0 "XA1" H 8500 5837 60  0000 C CNN
F 1 "Galileo_Gen2_Shield" H 8500 5731 60  0000 C CNN
F 2 "Arduino:Arduino_Uno_Shield" H 10300 8200 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-uno-rev3" H 10300 8200 60  0001 C CNN
	1    8500 4450
	1    0    0    -1  
$EndComp
NoConn ~ 7200 4600
NoConn ~ 7200 3400
NoConn ~ 7200 4500
NoConn ~ 7200 3500
NoConn ~ 7200 4400
Wire Wire Line
	9800 3400 9950 3400
NoConn ~ 7200 4300
Wire Wire Line
	9800 3500 9950 3500
NoConn ~ 7200 4200
Wire Wire Line
	9800 3600 9950 3600
NoConn ~ 7200 4100
Wire Wire Line
	9800 3700 9950 3700
Wire Wire Line
	9800 3800 9950 3800
Wire Wire Line
	9800 3900 9950 3900
Wire Wire Line
	9800 4000 9950 4000
Wire Wire Line
	9800 4100 9950 4100
Wire Wire Line
	9800 4200 9950 4200
Wire Wire Line
	9800 4300 9950 4300
Wire Wire Line
	9800 4400 9950 4400
NoConn ~ 9800 5000
Wire Wire Line
	9800 4500 9950 4500
NoConn ~ 7200 5300
NoConn ~ 7200 3800
NoConn ~ 9800 4900
NoConn ~ 7200 3700
NoConn ~ 9800 5400
NoConn ~ 9800 5200
NoConn ~ 9800 5100
NoConn ~ 7200 4700
NoConn ~ 9800 5500
NoConn ~ 9800 4800
NoConn ~ 9800 4700
Text GLabel 9950 3800 2    50   Input ~ 0
LIMIT_2
Text GLabel 9950 3700 2    50   Input ~ 0
LIMIT_1
Text GLabel 9950 3400 2    50   Input ~ 0
EN_PWM_R
Text GLabel 9950 3600 2    50   Input ~ 0
EN_PWM_L
Text GLabel 9950 3500 2    50   Input ~ 0
PWM
Text GLabel 9950 4200 2    50   Input ~ 0
EN_ENC1
Text GLabel 9950 4000 2    50   Input ~ 0
EN_ENC2
Text GLabel 9950 4100 2    50   Input ~ 0
SS_ENC1
Text GLabel 9950 3900 2    50   Input ~ 0
SS_ENC2
Text GLabel 9950 4300 2    50   Input ~ 0
MOSI
Text GLabel 9950 4400 2    50   Input ~ 0
MISO
Text GLabel 9950 4500 2    50   Input ~ 0
SCK
$Comp
L power:GND #PWR0108
U 1 1 5DB04E0C
P 6700 5350
F 0 "#PWR0108" H 6700 5100 50  0001 C CNN
F 1 "GND" H 6705 5177 50  0000 C CNN
F 2 "" H 6700 5350 50  0001 C CNN
F 3 "" H 6700 5350 50  0001 C CNN
	1    6700 5350
	1    0    0    -1  
$EndComp
Wire Notes Line
	7700 1150 10450 1150
Wire Notes Line
	10450 1150 10450 2200
Wire Notes Line
	10450 2200 7700 2200
Wire Notes Line
	7700 2200 7700 1150
Wire Notes Line
	6250 2700 10700 2700
Wire Notes Line
	10700 2700 10700 6050
Wire Notes Line
	10700 6050 6250 6050
Wire Notes Line
	6250 6050 6250 2700
Text Notes 10650 2800 2    50   ~ 0
GALILEO GEN2 SHIELD
Text Notes 10400 1250 2    50   ~ 0
INTERFACE CONNECTORS
Text Notes 5500 950  2    50   ~ 0
ENCODER/COUNTER 1
Text Notes 5500 3150 2    50   ~ 0
ENCODER/COUNTER 2
Text Notes 5250 5400 2    50   ~ 0
H-BRIDGE
Wire Wire Line
	4500 5750 4750 5750
Wire Wire Line
	4500 6200 4600 6200
Wire Wire Line
	4500 6050 4600 6050
Wire Wire Line
	4600 6050 4600 6200
Connection ~ 4600 6200
Wire Wire Line
	4600 6200 4750 6200
$EndSCHEMATC
