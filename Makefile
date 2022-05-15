TARGET=conv
CXX=c++
LD=c++
OBJS=main.cpp utils/*.cpp
conv:$(OBJS)
	$(LD) -g -o $(TARGET) $(OBJS) -lpthread
clean:
	rm -rf *.o