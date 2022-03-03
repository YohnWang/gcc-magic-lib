srcs=main.c
objs=$(srcs:%.c=%.o)
cflags = -O3 -Wall -Wextra -I .
ldflags = -lpthread

all: main.exe
	./main.exe

bgn: bgn.exe
	./bgn.exe | grep -o "2824229407960347874293421578024535518477494926091224850578918086542"

bgn.exe: test/bgn_boost.o
	gcc $^ -o $@ $(ldflags)

main.exe: main.o
	gcc $^ -o $@ $(ldflags)

%.o: %.c
	gcc $(cflags) -c $< -o $@

sinclude $(srcs:.c=.d)

%.d: %.c
	gcc -MM $(cflags) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY: clean run

run: main.exe 
	./main.exe

clean:
	find . '(' -name "*.o" -or -name "*.d" -or -name "*.exe" ')' -delete