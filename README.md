Super Simple AnalysisBase package
=================================

This is to run some simple things in an AnalysisBase release

To compile the code, do something like:

```bash
source setup.sh
./build.sh
```

Then to run a test (on a file which currently lives on AFS) you can use

```bash
./run.sh
```

This won't do much right now, but it will compile and test the program in

```text
BTagTrainingPreprocessing/utils/dump-test.cxx
```

which is a minimal working example to read an xAOD.
