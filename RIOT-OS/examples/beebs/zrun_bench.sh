#!/bin/bash
cd ~/workspace/Temporal-Safety/temporal-riot/examples/beebs
bench_dir=`ls`

for i in $bench_dir; do
  echo "current module is ${i}"
  echo "cd ${i}"
  cd ${i}
  echo "cur directory is `pwd`"
  echo "Build and Excuting ${i}"
  make flash
  echo "sleep 1m"
  sleep 1m
  cd ../
  echo "done!"
done

#!/bin/bash

# for c in {1..10}; do
#   cd ~/workspace/Temporal-Safety/temporal-riot/examples/beebs
#   bench_dir=`ls`

#   for i in $bench_dir; do
#     echo "current module is ${i}"
#     echo "cd ${i}"
#     cd ${i}
#     echo "cur directory is `pwd`"
#     echo "Build and Excuting ${i}"
#     make flash
#     echo "sleep 1m"
#     sleep 1m
#     cd ../
#     echo "done!"
#   done
# done

