# Faiss-FPGA

## General Info
FAISS-FPGA is a library for efficient similarity search and clustering of dense vectors built upon FAISS.
It contains algorithms that search in sets of vectors of any size and is written in C++. 
It is developed by [Facebook AI Research](https://research.fb.com/category/facebook-ai-research-fair/).

## Background

Faiss is built around the Index object. It encapsulates the set of database vectors, and optionally preprocesses them to make searching efficient by partioning the data into ncells (or nlist) cells. Then it searches in a reduced space selecting only nprobe cells out of ncells. There are many types of indexes but in this work we focused on accelerating the IVFFlat index because it generally performs well with high accuracy regimes.

All indexes need to know when they are built which is the dimensionality of the vectors they operate on, d in our case. Then, most of the indexes also require a training phase, to analyze the distribution of the vectors. 
When the index is built and trained using the FPGA, then searching is performed on CPU.

## Running the example IVFFlat

FAISS-FPGA handles collections of vectors of a fixed dimensionality d, specifically 192 as the binary in this repo was synthesized for that, so avoid changing it. These collections can be stored in matrices given in the IVFFlat C++ source code. We assume row-major storage, ie. the j'th component of vector number i is stored in row i, column j of the matrix. Faiss-FPGA uses only 32-bit floating point matrices just like FAISS in order to keep maximum accuracy and not append another layer of approximation to the problem.

Before compiling and running IVFFlat you can modify several variables for your own test scenarios:
  * We generally need two matrices:
    xb for the database, that contains all the vectors that must be indexed, and that we are going to search in. Its size is nb-by-d
    xq for the query vectors, for which we need to find the nearest neighbors. Its size is nq-by-d. If we have a single query vector, nq=1.
  * You can select the number of cells to cluster data by changing the nlist parameter (up to 1024). Bigger numbers give better query results but need longer training.
  * You can also modify nprobe to select the number of cells to visit in order to have better accuracy.
