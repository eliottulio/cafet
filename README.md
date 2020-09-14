cat transactions/* | sed 's/^.*; //' | tr '\n' '+' | sed 's/$/0\n/' | bc
