# =============================================== Tools Used in Rosetta =========================================================== #
# default sw compiler
SW_CXX = gcc

# =============================================== Pure Software Compilation Settings ============================================== #

# compiler flags
SW_FLAGS = -DSW -O3

# sw executable
SW_EXE = $(KERNEL_NAME)_sw.exe

# ========================================================= Rules ================================================================= #

# we will have 2 top-level rules:  sw and clean
# default to sw

.PHONY: all sw clean

all: sw

# software rules
sw: $(HOST_SRC_CPP) $(HOST_SRC_H) $(SW_KENREL_SRC) $(SW_KERNEL_H) $(DATA)
	$(SW_CXX) $(SW_FLAGS) -o $(SW_EXE) $(HOST_SRC_CPP) $(SW_KERNEL_SRC)

# cleanup
clean:
	rm -rf *.exe *.elf *.xclbin *.xo *.log *.bit *.rpt _xocc* _sds sd_card _x .run .Xil *.json *.info
	rm -rf ./src/host/*.d
	rm -rf ./src/host/*.o