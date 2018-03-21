HDRS = $(shell find . -name "*.h")
SRCS = $(shell find . -name "*.c")
OBJS = $(patsubst %.c, %.o, $(SRCS))

all: $(HDRS) $(OBJS)
	@echo $(OBJS)
	gcc -o sea $(OBJS) -lm

$(OBJS): %.o: %.c $(HDRS)
	gcc -O3 -c -o $@ $< 

clean: 
	rm -rf src/*.o 
