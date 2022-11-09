target = main.exe

build_dir = build

srcs = main.c gmllib.c

objs = $(srcs:%=$(build_dir)/%.o)
deps = $(objs:%.o=%.d)

cflags = -g -O3 -Wall  -Wno-unused -I . -MMD -MP
ldflags = -lpthread -lm

all: $(target)
	./$(target)

$(target): $(objs)
	gcc $^ -o $@ $(ldflags)

$(build_dir)/%.c.o: %.c
	mkdir -p $(build_dir)
	gcc $(cflags) -c $< -o $@

.PHONY : clean

clean:
	rm -rf build
	rm -f $(target)

-include $(deps)
