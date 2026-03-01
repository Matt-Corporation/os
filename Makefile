.PHONY: all test libk tarinit iso run clean

rm_test:
	@rm -f ./tarinit/test

all: rm_test tarinit libk
	@chmod +x ./toolchain/build.sh
	@./toolchain/build.sh

test_preload:
	@touch ./tarinit/test
	@echo "# Empty file that starts tests when included" > ./tarinit/test

test_build: tarinit libk
	@chmod +x ./toolchain/build.sh
	@./toolchain/build.sh

test: test_preload test_build
	@chmod +x ./toolchain/iso.sh
	@./toolchain/iso.sh
	@chmod +x ./toolchain/run.sh
	@./toolchain/run.sh

libk:
	@chmod +x ./toolchain/libk.sh
	@./toolchain/libk.sh

tarinit:
	@chmod +x ./toolchain/tarinit.sh
	@./toolchain/tarinit.sh

iso: all
	@chmod +x ./toolchain/iso.sh
	@./toolchain/iso.sh

run: iso
	@chmod +x ./toolchain/run.sh
	@./toolchain/run.sh

clean:
	@chmod +x ./toolchain/clean.sh
	@./toolchain/clean.sh
