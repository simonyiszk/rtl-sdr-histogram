# rtl-sdr-histogram
Hisztogramrajzoló RTL-SDR szoftverrádióhoz az I és Q komponensek előfordulási gyakoriságának vizsgálatára egy mintában, raw fájlban vagy valósidejű adatfolyamban, linux és gnuplot használatával.

![alt text](https://github.com/simonyiszk/rtl-sdr-histogram/blob/main/histogram_demo.jpg?raw=true)

### Fordítás
<code>
gcc rtl-sdr-histogram.c -o histogram
</code>

### Valósidejű adatfolyam feldolgozása
<code>
rtl_sdr -f [frekvencia Herz-ben] (további opciók ízlés szerint...) | ./histogram
</code>

### Adatfájl feldolgozása
<code>
./histogram [fájlnév]
</code>
