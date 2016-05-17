SOURCES := test.c snprintf_minimal.c
# Objs are all the sources, with .c replaced by .o
OBJS := $(SOURCES:.c=.o)

all: test

# Compile the binary 'test' by calling the compiler with cflags, lflags, and any libs (if defined) and the list of objects.
test: $(OBJS)
	$(CC) $(CFLAGS) -o test $(OBJS) $(LFLAGS) $(LIBS)

# Get a .o from a .c by calling compiler with cflags and includes (if defined)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

