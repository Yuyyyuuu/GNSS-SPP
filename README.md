# GNSS-SPP: Real-time GNSS Data Acquisition and PVT Solution

GNSS-SPP is a project implemented in standard C/C++ that allows for real-time acquisition of pseudoranges, Doppler frequency shifts, and broadcast ephemeris data from an OEM719 board card on a PC platform. It performs navigation, positioning, and velocity (PVT) calculations and outputs the results along with accuracy statistics, providing real-time navigation under the Windows command line.

## Features

- **Real-time Data Acquisition**: Collects pseudoranges, Doppler shifts, and ephemeris data.
- **PVT Calculation**: Computes position, velocity, and time from GNSS signals.
- **Accuracy Statistics**: Provides detailed statistics on the accuracy of the positioning.
- **Windows Command Line Interface**: Offers a real-time interface for navigation output.

## System Requirements

- A PC running Windows OS.
- A compatible GNSS receiver with OEM719 board card.
- C/C++ compiler (e.g., GCC, MSVC).

## Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/Yuyyyuuu/GNSS-SPP.git
   ```
2. Navigate to the project directory.
3. Compile the source code using your preferred C/C++ compiler.

## Usage

1. Ensure your GNSS receiver is connected and recognized by the system.
2. Run the compiled executable.
3. Observe the real-time data and statistics in the command line output.
