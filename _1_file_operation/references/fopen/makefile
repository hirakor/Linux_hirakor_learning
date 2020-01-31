CC:=gcc
srcs:=$(wildcard *.c)
objs:=$(patsubst %.c,%,$(srcs))
#匹配模板,替换后的内容,查找的来源
#LINKERFLAG:=-lpthread
all:$(objs)
%:%.c
	$(CC) -o $@ $<
.PHONY:clean rebuild print
rebuild:clean all 
clean:
	rm -rf $(out) $(objs)
print:
	@echo $(objs)
