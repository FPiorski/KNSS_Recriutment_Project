# DDS.c
I had to generate the test signal somehow and the only thing I had was a poorly soldered R2R ladded made with 1k 1% resistors, so I coded this little AVR program to act as my signal source. The wave table is hardcoded for 1Vpp 1kHz sine wave with (3.3 / 2) V DC offset (assuming 5V Vcc)
