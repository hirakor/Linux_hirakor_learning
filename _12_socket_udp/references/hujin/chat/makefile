srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%.o,$(srcs))
out:=$(srcs:%.c=%)
all:$(out)
%:%.c
	gcc $< -o $@ -lpthread
clean:
	  rm -rf $(out)
