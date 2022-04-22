EXECS = test
OBJS = test.o Animator.o VehicleBase.o Tile.o TrafficLight.o Road.o Intersection.o MoveVehicle.o

#### use next two lines for Mac
CC = g++
CCFLAGS = -std=c++17

#### use next two lines for mathcs* machines:
#CC = g++
#CCFLAGS = -std=c++17

all: $(EXECS)

test: $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

%.o: %.cpp %.h
	$(CC) $(CCFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CCFLAGS) -c $<

clean:
	/bin/rm -f a.out $(OBJS) $(EXECS)