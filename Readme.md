# LED Blink Driver for Raspberry Pi

This Linux kernel module enables blinking of three LEDs connected to GPIO pins on a Raspberry Pi. The module is designed to work with threads for efficient LED control.

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/alichlaifa/blinkLed_driver_kthread.git
    ```
2. Navigate to the module directory:
    ```bash
    cd blinkLed_driver_kthread
    ```
3. Build the module:
    ```bash
    make
    ```
4. Install the module:
    ```bash
    sudo insmod ledBlink.ko
    ```

## Usage

1. Check if the module loaded successfully:
    ```bash
    lsmod | grep ledBlink
    ```
2. The LEDs should start blinking.

## Working with Threads

The module utilizes kernel threads for parallel LED control. Each LED is controlled by a separate thread to optimize performance and responsiveness.
