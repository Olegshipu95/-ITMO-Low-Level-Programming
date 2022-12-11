ASM=nasm
ASMFLAGS=-felf64
LD=ld

main: main.o lib.o dict.o
	$(LD) -o $@ $^
	rm *.o
%.o: %.asm
	$(ASM) $(ASMFLAGS) -o $@ $<
.PNONY: clean
clean:
	rm *.o
	rm main
