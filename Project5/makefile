CC	= gcc
CFLAGS	= -g
TARGETS	= master worker

all: $(TARGETS)

$(TARGETS): %: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	/bin/rm -f $(TARGETS)
