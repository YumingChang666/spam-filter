# Set kernel name
KERNEL_NAME = SgdLR

# Set host source and headers
HOST_SRC_CPP = ./src/host/spam_filter.c ./src/host/utils.c ./src/host/check_result.c
HOST_SRC_H   = ./src/host/utils.h ./src/host/check_result.h ./src/host/typedefs.h 
DATA         = ./data/*.dat

# Set kernel file
SW_KERNEL_SRC = ./src/sw/sgd_sw.c
SW_KERNEL_H = ./src/host/typedefs.h

#-------------------------
# Leave the rest to harness
#-------------------------
include ./harness/harness.mk

# run with "./SgdLR_sw.exe -p ./data "(After "make")

