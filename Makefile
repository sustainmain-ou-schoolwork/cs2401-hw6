CXX = g++
CFLAGS = -g -Wall -std=c++11
NOMAIN = othello.o game.o
MAINOBJ = samplemain.o
TESTOBJ = test.o
OBJS = $(MAINOBJ) $(NOMAIN)
TESTOBJS = $(TESTOBJ) $(NOMAIN)


a.out: $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) -o $@

$(MAINOBJ): samplemain.cc othello.h game.h colors.h
	$(CXX) $(CFLAGS) -c samplemain.cc -o $@

othello.o: othello.cc othello.h game.h colors.h
	$(CXX) $(CFLAGS) -c othello.cc -o $@

game.o: game.cc game.h
	$(CXX) $(CFLAGS) -c game.cc -o $@


test: $(TESTOBJS)
	$(CXX) $(CFLAGS) $(TESTOBJS) -o $@

$(TESTOBJ): test.cc othello.h
	$(CXX) $(CFLAGS) -c test.cc -o $@


.PHONY: clean
clean:
	rm -rf $(NOMAIN) $(MAINOBJ) $(TESTOBJ) a.out test
