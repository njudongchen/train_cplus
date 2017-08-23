CC=g++ -std=c++11
CCFLAG=-g
CPPFLAGS=-std=c++11
#OBJ=main.o querybase.o query_Interface.o textquery.o
SOURCE=$(wildcard *.cpp)
OBJ := $(patsubst %.cpp, %.o,$(SOURCE))
TARGET=main
$(TARGET):$(OBJ)
	$(CC) $(CCFLAG) -o $@ $^
#$(OBJ):%.o:%.cpp %.d
#	$(CC) $(CCFLAG) -c $< -o $@
sinclude $(SOURCE:.cpp=.d)
%.d:%.cpp
	$(CC) -MM $(CPPFLAGS) $< > $@.$$$$;\
	sed 's,\($∗\)\.o[:]*,\1.o $@ : ,g' < $@.$$$$ > $@;\
	rm -f $@.$$$$
.PHONY:clean
clean:
	rm -f *.o *.d $(TARGET)
