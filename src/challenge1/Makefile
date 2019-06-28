include ../../target.mk


vpath %.c $(UTILS)
vpath %.o $(TMP)
vpath %.d $(TMP)


OBJS := base64.o main.o
OBJS := $(addprefix $(TMP)/, $(OBJS))


.PHONY: all
all: solve

.PHONY : solve
solve: build
	# $(TARGET) < input1 | tee result1
	# @$(ECHO_NE)

build: build_dir $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN)/challenge1