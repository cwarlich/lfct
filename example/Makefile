.PHONY: all
all: factorial ; ./factorial 4; ../lfct ./factorial 4
factorial: factorial.c ; gcc -finstrument-functions -g -O0 $< -o $@
