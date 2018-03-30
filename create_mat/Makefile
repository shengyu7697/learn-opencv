TARGET = create_mat

CXX = g++
CXXFLAGS = -O0 -g -std=c++11 # for Debug
#CXXFLAGS = -W -Wall -O3 -std=c++11 # for Release
LDFLAGS =
RM = rm -rf
HEADERS = $(wildcard *.h)
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)

LIBS = opencv
ifneq ($(LIBS),)
CXXFLAGS += $(shell pkg-config --cflags $(LIBS))
LDFLAGS += $(shell pkg-config --libs $(LIBS))
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(OBJS) $(TARGET)

