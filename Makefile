steaminit: src/steaminit.cpp
	echo "build .o files"
	clang++ -std=c++20 src/steaminit.cpp -c -Isteamassets/public
	echo "build a.out file"
	clang++ -std=c++20 steaminit.o -Lsteamassets/osx -lsteam_api -o ./steamassets/osx/steaminit.out
	rm steaminit.o