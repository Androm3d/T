all: sorts.o sorst.class arrays.txt


sorts.o: sorts.cpp
	g++ -o sorts.o sorts.cpp

sorts.class: sorts.java
	javac sorts.java

arrays.txt: make_arrays.py
	python3 make_arrays.py > arrays.txt

clean:
	rm arrays.txt sorts.o sorts.class