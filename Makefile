JBUILDER?=jbuilder

OS:=$(shell uname -s)

build: src/jbuild.flags
	$(JBUILDER) build @lang_ppx
	cp _build/default/src/lang_ppx.exe .

test:
	(cd tests && bsb -clean-world && bsb -make-world && ./lib/bs/native/indexnative.native)

ifeq ($(OS),Linux)
src/jbuild.flags:
	echo '(-ccopt -static)' > $@
else
src/jbuild.flags:
	echo '()' > $@
endif

clean:
	$(JBUILDER) clean
	rm -rf _build lang_ppx.exe tests/lib

.PHONY: build test clean