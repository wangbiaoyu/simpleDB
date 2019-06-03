#!/bin/bash


#sudo mv "*.ata" SimpleDB/
#find . -name "*.cpp" | xargs cp -rf ./SimpleDB/
for f in *
do 
 echo $f
 if[ $f=="*.cpp" ]
   mv $f ../
done
