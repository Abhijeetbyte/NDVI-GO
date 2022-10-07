# NDVI-GO

## Getting Started

Upload this [file](main.ino) to your arduino board, and open Serial monitor to see the result. <br/>


### Wirring connection
<br/>

**NDVI sensor Module**

* RED Led  ->  D2 (_digital Pin 2_)
* IR Module ->  A1 (_analog Pin A1_)
* LDR Module ->  A0 (_analog pin A0_)

**OLED Screen**

* SDA  ->  A4 (_analog Pin A4_)
* SCL ->  A5 (_analog Pin A5_)
 
 Make a comman _GND_ and _VCC/+5V_
 
 **Note**: IR & LDR module must have analog output
 
<br/>



### Schematics

![img1](/Assets/Schematic_NDVI-GO_2022-10-08.png)

<br/>

#

![img1](/Assets/components.png)

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

