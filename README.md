PSTk-Classifier
===============

Software for classyfing DNA sequences based on oligomer frequencies

PSTk-Classifier is a software written in C++ for classifying DNA using a Bayesian approach.
Different underlying models can be selected—Naive (Nk), Markov (Mk) and
Variable Length Markov (VLMK). The classifier works by first constructing profiles
for all groups using fasta-files directly. The profiles are kept in a directory. Then sample
sequences (in a multifasta file) can be scored against the profiles and a high-score
list will be presented.

If you use this software in any work of research, please cite:

Dalevi D, Dubhashi D, Hermansson M. (2006)
Bayesian classifiers for detecting HGT using fixed and variable order markov models of genomic signatures.
Bioinformatics. 2006 Mar 1;22(5):517-22. 
http://www.ncbi.nlm.nih.gov/pubmed/16403797 

How to install:
To create the binary "classifier" do the following,

1. cd common; make install; cd ..;
2. cd random; make install; cd ..;
3. cd trees; make install; cd ..;
4. cd classifier; make

The binary will be found in the pstk_classifier/classifier directory.

Once installed you may test that the Classifier is proper built by typing
./Classifier -h


