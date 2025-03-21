CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gsl`
LIBS   = `pkg-config --libs gsl`

TARGET = main
SRCS   = main.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm -f $(TARGET)