build:
	g++ -ldl -Wall -g -std=c++17 -o main main.cpp
libs:
	gcc -Wall -g -fPIC -shared -o ./plugins/libc.so ./libc.c
	g++ -Wall -g -fPIC -shared -o ./plugins/libcpp.so ./libcpp.cpp

buildwin:
	i686-w64-mingw32-g++ -Wall -g -std=c++17 -static -o ./win/main main.cpp
libswin:
	i686-w64-mingw32-gcc -Wall -g -fPIC -shared -o ./win/plugins/libclang.dll ./libc.c
	i686-w64-mingw32-g++ -Wall -g -fPIC -shared -static -o ./win/plugins/libcpp.dll ./libcpp.cpp

