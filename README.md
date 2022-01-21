# rtl-sdr-histogram
Hisztogramrajzoló RTL-SDR szoftverrádióhoz az I és Q komponensek előfordulási gyakoriságának vizsgálatára egy mintában, raw fájlban vagy valósidejű adatfolyamban. Linux és gnuplot használatával.

![alt text](https://github.com/simonyiszk/rtl-sdr-histogram/blob/main/histogram_demo.jpg?raw=true)

### Fordítás
<code>
gcc rtl-sdr-histogram.c -o histogram
</code>

### Használat valósidejű adat megjelenítéshez
<code>
rtl-sdr -f [frekvencia Herz-ben] | ./histogram
</code>

### Raw adafájl feldolgozása
<code>
./histogram [fájlnév]
</code>
