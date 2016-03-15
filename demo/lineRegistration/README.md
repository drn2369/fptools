#Scanline Registration

This is an example of how the scanline registration function can be used. It is used as follows:

```
./demoReg inputUnregistered.pgm outputRegistered.pgm
```

Where the input PGM image is a full set of scanlines stacked in one image. The pixel length of the scanline is hard coded and must be passed to the registration function, here it is set to 8 pixels.
