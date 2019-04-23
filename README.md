# TI_Hercules_Development
Embedded Device: Hercules™ Arm® Cortex®-R MCUs for functional safety

## Introduction
This project is dedicated to my experimentation with the Texas Instruments Hercules™ Arm® Cortex®-R MCUs Functional Safety development kit.

The project is broken down into 2 parts:
1. Hercules Embedded Development code
    - Contains all source code specfic to the embedded hardware. 
2. LIDAR PC Visualization Applications
    - Contains all source code for a Python and .NET data visualizer application
    
For a demostration, please view the attached video: Hecules_Lidar_&_Visualization_In_Action.MOV
  
### Hercules Embedded Development Source Code
The embedded application contains source code that configures the for FreeRTOS OS and developed device drivers for the RPLIDAR-A2 Rotating Laser Range Scanner.
- RPLIDAR Info: https://www.slamtec.com/en/Lidar/A2
- Hercules Info: http://www.ti.com/microcontrollers/hercules-safety-mcus/overview.html

### LIDAR PC Visualization Applications
The project also contains 2 PC based applications to view the processed and transmitted LIDAR from the Hercules board to the PC via UART communication.
1. Python:
    - There are 2 scripts:
      - Lidar_Animation.py, creates an animated plot of the LIDAR data as it is being transmitted in real-time.
      - Lidar_Data_Logger.py, logs and saves the LIDAR data in real-time as a csv.
 2. .NET:
    - SerialApp, is C# UI that contains an animated plot of the LIDAR data as it is being transmitted in real-time.
      - Also includes a panel where the raw data can be viewed in real-time.

  
