
haotian:haotian.o
	clang++ haotian.o -o haotian
haotian.o:haotian.S
	clang++ -c haotian.S -o haotian.o
haotian.S:haotian.i
	clang++ -S haotian.i -o haotian.S
haotian.i:haotian.cpp
	clang++ -E haotian.cpp -o haotian.i

.PHONY:
clean:
	rm -rf haotian.i haotian.S haotian.o haotian
