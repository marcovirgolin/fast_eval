release: BUILDTYPE=release
debug: BUILDTYPE=debug
release: main-build
debug: main-build

main-build:
	mkdir -p build/$(BUILDTYPE)
	cd build/$(BUILDTYPE) && \
	cmake -S ../../ -B . -DCMAKE_BUILD_TYPE=$(BUILDTYPE) && \
	make

clean:
	rm -rf build
