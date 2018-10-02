.PHONY:clean
INPUT_FILE=main.c
OUTPUT_FILE=copyFile

all:main.c
	gcc	-o	main	main.c

built:
	./main	$(INPUT_FILE)	$(OUTPUT_FILE)

strace:
	strace	./main	$(INPUT_FILE)	$(OUTPUT_FILE)

clean:
	rm -f main $(OUTPUT_FILE)