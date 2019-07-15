<p align="center">
    <img src="https://i.imgur.com/KzcpiDq.png" alt="" width=370 height=195>
  </a>

  <h2 align="center">Hardware acceleration of FAISS framework</h2>

  <p align="center">
    Approximate Similarity Search using <a href="https://github.com/facebookresearch/faiss/"><strong>FAISS</strong></a> framework on cloud FPGAs.
    <br>
    <br>
    <a href="https://github.com/dimdano/faiss-fpga/issues/new?labels=bug">Report a bug</a>
    ·
    <a href="https://github.com/dimdano/faiss-fpga/issues/new?labels=question">Ask a question</a>
    ·
    <a href="https://github.com/dimdano/faiss-fpga/issues/new?labels=enhancement">Request feature</a>
    </p>
</p>

<br>



## Overview

FAISS-FPGA is built upon FAISS framework which is a a popular library for efficient similarity search and clustering of dense vectors. It contains algorithms that search in sets of vectors of any size and is written in C++ with complete wrappers for Python. It is developed by Facebook AI Research. 
FAISS is based on an approximate KNN (k-nearest neighbors) algorithm which is built around an index type that stores the input vectors of a dataset, and provides a function to search in them with L2 and/or dot product vector comparison. By building an index (IVF) it trains the distribution of the input vectors into cells and at search time only specific cells are searched, thus doing more efficient queries.
Most of the available indexing structures correspond to various trade-offs with respect to search time, memory, accuracy, etc.

In the FAISS-FPGA project we chose to focus on IVFFlat index structure because it performs well overall and is good for high accuracy regimes. The search is already very fast, however the building of the index involves many MAC operations. So, we designed a hardware accelerator for OpenCL-FPGAs using SDAccel that accelerates the Index creation which takes up a substancial time. The new FAISS-FPGA framework works as a unified hardware-accelerated library with the FPGA-OpenCL API being hidden under the framework. The user can seamlessy select between the default CPU implementation of FAISS or the FPGA accelerated one.

#### Link to youtube video: [https://www.youtube.com/watch?v=a7iEHEheDxs](https://www.youtube.com/watch?v=a7iEHEheDxs)

## Installation

The project was designed with SDAccel v2018.2.xdf targeting the Xilinx Alveo U200 board. First make sure to check the dependencies before proceeding to the quick start guide .


#### Dependencies 

* GNU Make
* A C,C++ compiler
* A Fortran compiler (for LAPACK)
* SDAccel v2018.2.xdf environment and env. paths set (i.e. XILINX_SDX and XILINX_XRT)
* An Alveo U200 and board files installed on your system 
* OpenBlas/LAPACK package (required for FAISS)
  * On Ubuntu:
      ```sh
       sudo apt-get install libopenblas-dev libblas-dev liblapack-dev
       ```
      * If you installed them in custom folder:
      ```sh
       export BLAS_LIBS = path/to/blas/libraries/
      ```
      
#### Quick start 

The project includes the default CPU FAISS and the FPGA-accelerated one in unified static libraries (libfaiss_sw.a, libfaiss_hw.a). The user can switch between each implementation easily:

* To run the approximate similarity search example (IVVFlat) <br/>
  Go to ```/example/``` folder and run ```make TARGET=sw``` or ```make TARGET=hw``` <br/>
  Make sure to run ```make clean``` when changing builds.

For more information see  [docs](https://github.com/dimdano/faiss-fpga/tree/master/docs)

## HW specs

* Device used: Xilinx Alveo U200
* Kernel number: 4
* DDRs used: 4 
* Kernel freq: 300MHz

#### Resource utilization for a single FPGA kernel 

Resource	|	Used	|	Total	|	% Utilization
:----------:|----------:|----------:|:----------:|
DSP	|	1004	|	6840	|	  14|
BRAM	|	502	|	4320	|	  11|
LUT	|	89206	|	1182240	|  	7|
FF	|	156137	|	2364480	|  	6| 

## References

#### Publication

If you use any part of this work, we would love to hear about it and would very much appreciate a citation:

```
@misc{
  author =       "Dimitrios Danopoulos, Christoforos Kachris, and Dimitrios Soudris",
  title =        "FPGA Acceleration of Approximate KNN Indexing on High-Dimensional Vectors",
  conference =   "14th International Symposium on Reconfigurable Communication-centric Systems-on-Chip (ReCoSoC)",
  year =         "2019",
  month =        "July",
}
```
#### Contact 

* Contributor <br/>
`Dimitrios Danopoulos`: dimdano@microlab.ntua.gr

* Supervisor <br/>
`Christoforos Kachris`: kachris@microlab.ntua.gr



