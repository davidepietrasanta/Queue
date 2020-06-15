# MODE = -DNDEBUG #per compilare in modalita' release

 MODE =  # per compilare in modalita' debug

queue: main.cpp
	g++ $(MODE) -std=c++0x main.cpp -o queue

.PHONY: clean

clean:
	rm *.exe *.o
