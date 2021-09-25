##########################################
#		Static Library Build Makefile
############################################
CC = g++7
SAMPLE_HOME = ../../..
SRC_FILE_PATH = $(SAMPLE_HOME)/src

CFLAGS = -m64 -O2 -c -Wall -fmessage-length=0 -I$(SAMPLE_HOME)/includes
LDFLAGS = -ldl 

include $(SRC_FILE_PATH)/sources.txt
OBJS = $(SOURCES:.cpp=.o)

EXEC = sample.exe

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: $(SRC_FILE_PATH)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXEC)

