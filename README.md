# KNSS Recruitment project

Measuring low frequency analog signal using STM32F103
  - ADC captures 2000 samples at 600kSPS 20 times
  - Trying to synchronize the twenty measurements (no hardware triggering circuit)
  - Measuring amplitude and frequency of the averaged signal
  - Sending the results over UART

Most of the magic happens in src/main.c and the could *should* be self-explainatory, but just in case:
  - Initialize all the peripherals
  - Capture 2000 samples and take the average to guess what the DC offset is - used for software triggering
  - Do this 20 times: capture 2000 samples, add all of them that were taken after a positive edge to the buffer
  - Try to find the second positive egde in the buffer - we are only interested in one period of the signal
  - Compute max and min values of the buffer
  - Output results over UART and go back to step 2

The *trigger()* function iterates over the buffer until buffer value goes below DC offset, skips another couple of samples ahead (to neutralize jitter without implementing hysteresis) then continues until buffer goes above DC offset and returns the position. It works pretty well if the number of samples taken during one wave period is sufficiently high (tested with 600 samples per period)

Notice the two 'ugly' functions near the end of main.c, namely *PeriodToString()* and *VppToString()*. They were quickly implemented to avoid using sprintf, which is too heavy of a function for my taste. One could argue that it's better to use what's more comfortable and only optimize after the binary is too large for a given µC and I'd be willing to agree, but I didn't realy think of that until it was brought up to me. So yeah, 128kB is a lot of memory and spending ~20kB to eliminate the 'ugliness' of those two functions is an acceptable tradeoff.
