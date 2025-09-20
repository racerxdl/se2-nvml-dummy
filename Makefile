# x86_64-w64-mingw32-gcc -c nvml.c -o nvml.o
# x86_64-w64-mingw32-gcc -shared -o nvml.dll nvml.o -Wl,--out-implib,nvml.dll.a


all: nvml.dll
	@echo "Build complete"

nvml.dll: nvml.o
	@echo "Linking..."
	@x86_64-w64-mingw32-gcc -shared -o nvml.dll nvml.o -Wl,--out-implib,nvml.dll.a

nvml.o: nvml.c
	@echo "Compiling..."
	@x86_64-w64-mingw32-gcc -c nvml.c -o nvml.o

clean:
	@echo "Cleaning up..."
	@rm -f nvml.o nvml.dll nvml.dll.a