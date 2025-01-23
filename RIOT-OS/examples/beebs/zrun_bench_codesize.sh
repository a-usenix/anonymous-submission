#!/bin/bash

bench_dir=`ls`

for i in $bench_dir; do
  echo "current module is ${i}"
  echo "cd ${i}"
  cd ${i}
  echo "cur directory is `pwd`"
  echo "Build and Excuting ${i}"
  #make flash
  make flash >> /home/kbhetrr/workspace/Temporal-Safety/exp/250123_beebs_soversion_codesize.log 2>&1
  #sleep 2m
  cd ../
  echo "done!"
done
