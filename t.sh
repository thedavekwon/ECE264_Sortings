#!/bin/bash
./a.out < input1.txt
diff output.txt sample_o1.txt
./a.out < input2.txt
diff output.txt sample_o2.txt
./a.out < input3.txt
diff output.txt sample_o3.txt
./a.out < input4.txt
diff output.txt sample_o4.txt