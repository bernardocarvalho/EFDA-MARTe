# EFDA-MARTe
Forked from https://vcis-gitlab.f4e.europa.eu/aneto/EFDA-MARTe
EFDA-MARTe is licenced with EUPL (http://ec.europa.eu/idabc/eupl.html). See the file Licence-EUPL

### For convenience some 3rd party libraries, with versions which are known to work with MARTe, are also included in this distribution:
- RTAI
- flot
- RGraph
If you wish to use them, you must accept their original licences.

## Compile
To compile all, run:
```bash
./compile.MARTe linux config.MARTe all
```
### Extra compilations
You nay need to compile manually the modules:
    * IOGAMs/GenericTimerDriver
    * MARTe/MARTeSupportLib
    * Interfaces/HTTP/CFGUploader
    * Interfaces/HTTP/SignalHandler
    * Interfaces/HTTP/FlotPlot
    * Interfaces/HTTP/MATLABHandler
    * GAMs/PlottingGAM
    * GAMs/DataCollectionGAM
    * GAMs/WebStatisticGAM
    * GAMs/PIDGAM
    * GAMs/WaterTank
    * IOGAMs
    * IOGAMs/GenericTimerDriver
Got each folder and run:

```bash
make -f Makefile.linux
```

## Run JTLogger
```bash
 cd Interfaces/Logger/JTLogger
./JTLogger.sh
 ```
## Run WaterTank Example

```bash
 cd Examples/WaterTank
./MARTe-WaterTank.sh MARTe-WaterTank.cfg
```
