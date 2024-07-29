all: prog1 prog2 run clean
prog1: PCBv1.c
        gcc -std=c99 -o PCBv1 PCBv1.c
prog2: PCBv2.c
        gcc -std=c99 -o PCBv2 PCBv2.c
run:
        @echo "Running Version 1..."
        @./PCBv1
        @echo "Running Version 2..."
        @./PCBv2
clean:
        rm PCBv1 PCBv2
