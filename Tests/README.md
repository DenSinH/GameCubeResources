### Tests

I made these tests to find out if my instructions worked properly. 

### IMPORTANT NOTE:
on the single/double fuzzers, python seems to round the results in some way, I am not sure if this is the correct way. I just sort of eyeballed it to see if the results are close enough!

Dolphin acted a bit strange on these tests and did not output anything.

The way the output works:
 - the ROM outputs a memory address to the SIO buffer HW register
 - at this address starts a 0x1000 length string (or something like that)
 - in this string, results are outputted using the `output` macro.