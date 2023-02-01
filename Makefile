release: BUILDTYPE=release
debug: BUILDTYPE=debug
release: main-build
debug: main-build

main-build:
	mkdir -p build/$(BUILDTYPE)
	cd build/$(BUILDTYPE) && \
	cmake -S ../../ -B . -DCMAKE_BUILD_TYPE=$(BUILDTYPE) && \
	make && \
	cp -r ../../src/pypkg . && \
	mv _pyfe*.so pypkg/pyfe/_pyfe.so && \
	cd pypkg && \
	python setup.py install --user --force && \
	cd ../ && \
	rm -r pypkg
	
clean:
	rm -rf build
