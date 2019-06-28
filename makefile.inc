TARGET       = sw
CXX          = ${XILINX_SDX}/bin/xcpp -std=c++14
CXXCPP       = ${XILINX_SDX}/bin/xcpp -std=c++14 -E
CPPFLAGS     = -DFINTEGER=int  -fopenmp
CXXFLAGS     = -fPIC -m64 -Wno-sign-compare -g -O3 -Wall -Wextra -DSDX_PLATFORM=xilinx_u200_xdma_201820_1 -D__USE_XOPEN2K8 -I${XILINX_XRT}/include/ -I${XILINX_SDX}/runtime/include/1_2 -I"${HOME}/faiss_fpga" -std=c++14 -fpermissive
CPUFLAGS     = -msse4 -mpopcnt
LDFLAGS      = -fopenmp -L${BLAS_LIBS} -lxilinxopencl -lrt -lpthread -L${XILINX_SDX}/runtime/lib/x86_64 -L${XILINX_XRT}/lib/
LIBS         = -lopenblas
PYTHONCFLAGS =  -I/usr/local/include/python2.7 -I/usr/local/include/python2.7 -I

NVCC         =
CUDA_ROOT    =
CUDA_ARCH    = default
NVCCFLAGS    = -I $(CUDA_ROOT)/targets/x86_64-linux/include/ \
-Xcompiler -fPIC \
-Xcudafe --diag_suppress=unrecognized_attribute \
$(CUDA_ARCH) \
-lineinfo \
-ccbin $(CXX) -DFAISS_USE_FLOAT16

OS = $(shell uname -s)

SHAREDEXT   = so
SHAREDFLAGS = -shared

ifeq ($(OS),Darwin)
        SHAREDEXT   = dylib
        SHAREDFLAGS = -dynamiclib -undefined dynamic_lookup
endif

MKDIR_P      = /bin/mkdir -p
PYTHON       = python
SWIG         =
AR          ?= ar

prefix      ?= /usr/local
exec_prefix ?= ${prefix}
libdir       = ${exec_prefix}/lib
includedir   = ${prefix}/include

