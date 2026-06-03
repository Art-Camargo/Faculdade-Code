CC = gcc
CFLAGS = -Wall -Wextra -pedantic
TARGET = csql
SOURCES = main.c database.c parser.c utils.c csql.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
