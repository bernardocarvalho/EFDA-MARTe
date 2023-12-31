#!/bin/sh

if [ -z "$1" ]; then
	echo "Please specify the location of the configuration file"
	exit
else
	echo "Going to start MARTe with the configuration specified in: " $1
fi

CODE_DIRECTORY=../..
LD_LIBRARY_PATH=.:$CODE_DIRECTORY/BaseLib2/linux
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/MARTe/MARTeSupportLib/linux
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/Interfaces/HTTP/CFGUploader/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/Interfaces/HTTP/SignalHandler/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/Interfaces/HTTP/MATLABHandler/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/IOGAMS/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/IOGAMS/FakeATCAAdc/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/IOGAMS/LinuxTimer/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/IOGAMS/GenericTimerDriver/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/GAMs/WebStatisticGAM/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/GAMs/WaveformGenerator2009/linux
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/GAMs/DataCollectionGAM/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/GAMs/NoiseGAM/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/GAMs/WaterTank/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/GAMs/PIDGAM/linux/
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CODE_DIRECTORY/IOGAMS/StreamingDriver/linux/

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH

$CODE_DIRECTORY/MARTe/linux/MARTe.ex $1

#cgdb --args $CODE_DIRECTORY/MARTe/linux/MARTe.ex $1

