#!/bin/bash
cd ./visits_module/build 
cmake -DCMAKE_VERBOSE_MAKEFILE=TRUE -DCMAKE_BUILD_TYPE=Release ../src/
make
cd ../../
./popf3-clp -x ./visits_domain/dom1.pddl ./visits_domain/prob1.pddl ./visits_module/build/libVisits.so region_poses
