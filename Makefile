OUTPUT=code_detector

${OUTPUT}:${OUTPUT}.cpp
	g++ $^ -o $@ `pkg-config --libs --cflags opencv` -lzbar

.PHONY: clean
clean:
	rm ${OUTPUT}
