# SamTest
Minimal setup of SAM E70 microcontroller

## Compile
```
mkdir build
cd build
cmake ..
make
```

## Program
Make sure the run from flash bit is set:
```
openocd -f ../openocd.cfg -c init -c "reset halt" -c "atsamv gpnvm set 1" -c shutdown
```

Program samtest.elf
```
openocd -f ../openocd.cfg init -c "program samtest.elf verify reset exit"
```
