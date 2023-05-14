# NDVI-GO

NDVI stands for "Normalized Difference Vegetation Index". It is a numerical indicator of the health of vegetation, based on the 
reflectance of light in the near-infrared and visible portions of the electromagnetic spectrum.

The project is designed to use an NDVI sensor module connected to an Arduino board to calculate and display NDVI values on an OLED screen. The schematic and wiring connections are provided below, along with a description of the components used.
It also includes an explanation of the NDVI formula and a scale for interpreting NDVI values.
The project will hopefully useful tool for those interested in measuring the health of vegetation using NDVI.

## Getting Started

Upload this [file](main.ino) to your arduino board, and open Serial monitor to see the result. <br/>


### Wirring connection
<br/>

**NDVI sensor Module**

* IR Led  ->  D9 (_digital Pin 9_)
* RED Led  ->  D10 (_digital Pin 10_)
* IR Sensor ->  A1 (_analog Pin A1_)
* LDR Sensor ->  A0 (_analog pin A0_)

**OLED Screen**

* SDA  ->  A4 (_analog Pin A4_)
* SCL ->  A5 (_analog Pin A5_)
 
 Make a comman _GND_ and _VCC/+5V_
 
 **Note**: IR & LDR module must have analog output
 
<br/>



### Schematics

![img1](/Assets/Schematic_NDVI-GO_2022-10-21.png)

<br/>

#

![img1](/Assets/components.jpg)

<br/>

#

### Working Layout

<br/>

![img1](/Assets/NDV-Sensor-demo.png)


<br/>


### Comparison

![img1](/Assets/NDVi-plant-illustration-comparison.jpg)

<br/>


### Expression

<br/>

<!-- using MathJax library -->

$$NDVI = { NIR  -  Red \over NIR  +  Red}$$

<br/>

* Reflectance of near-infrared (NIR) and red (RED)
* NDVI value ranges from -1.0 to +1.0

NDVI is a mathematical function of the reflectance values of two wavelengths regions, near-infrared (NIR) and visable (commonly red).


**Scale**

<br/>

![img1](/Assets/NDVI-scale.jpg)

<br/>

## Reporting Issues & Contributions

Feel free to report <b>[issues](https://github.com/Abhijeetbyte/NDVI-GO/issues/new)</b> and <b>contribute</b> to this repository

<br/>

