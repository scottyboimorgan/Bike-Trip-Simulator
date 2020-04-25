#Makefile for Project 2
#Scott Morgan
CC = gcc

CFLAGS=-Wall -g
TARGET = Project2_smorga_205
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 
clean:
	rm $(TARGET)
