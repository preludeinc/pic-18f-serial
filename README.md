## Simple Microcontroller-Based Computer

### Hardware Setup
- Wired an external circuit using a Matrix 4x4 keypad, a Hitachi LCD, and an eight-bit PIC18F4685. 
- User entered data (via the 4x4 Matrix keypad) is sent serially through the PIC's built-in transmit (TX) and receive (RX) functionality. 
- Keypad keys provide functionality for scrolling, for a back-space, and to clear the LCD. 

### Code Related Notes
- Initializing the LCD was a more difficult fundamental requirement of the labs involving the PIC, and needed to be done according to specifications mentioned in the the PIC's datasheet.
- The initialization code can be found [here](./lcd18f.c).

### Hardware and Wiring
![Simple Computer](https://github.com/user-attachments/assets/423e4db4-d801-46b2-ad69-5dec0d61e083)
