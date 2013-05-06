all:
	g++ -std=c++11 -DNDEBUG -O3 -pthread -lrt bench.cpp simplethread.cpp systemtime.cpp -o nixbench
	
debug:
	g++ -std=c++11 -DDEBUG -pthread -lrt bench.cpp simplethread.cpp systemtime.cpp -o nixbench -g
	
release-dbg:
	g++ -std=c++11 -DNDEBUG -O3 -pthread -lrt bench.cpp simplethread.cpp systemtime.cpp -o nixbench -g
