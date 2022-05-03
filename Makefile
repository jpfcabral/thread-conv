TARGET=conv
CXX=c++
LD=c++
OBJS=main.cpp utils/image.cpp
conv:$(OBJS)
	$(LD) -o $(TARGET) $(OBJS)
clean:
	rm -rf *.o