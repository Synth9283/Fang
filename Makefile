target = fang
compiler = gcc
frontSrc = $(wildcard front/src/*.c)
frontObj = $(frontSrc:.c=.o)
flags = -g -O3 -static

all: $(target)

$(target): main.c $(frontObj)
	$(compiler) $^ $(flags) -o $@

%.o: %.c
	$(compiler) -c $(flags) $^ -o $@

clean:
	rm -rfv $(frontObj) $(target)
