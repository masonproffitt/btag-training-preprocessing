Flavor Tagging Ntuple Dumper
============================

This is to dump b-tagging info from an AnalysisBase release

To compile the code, go to a clean directory and run run:

```bash
git clone --recursive ssh://git@gitlab.cern.ch:7999/mproffit/btag-training-preprocessing.git proj
mkdir build
cd build
source ../proj/setup.sh
../proj/build.sh
```

Then to run a test (on a file which currently lives on AFS) you can use

```bash
../proj/run.sh
```

This won't do much right now, but it will compile and test the program in

```text
BTagTrainingPreprocessing/utils/dump-test.cxx
```

which is a minimal working example to read an xAOD and write some
information to HDF5.

Package Layout
--------------

The code lives under `BTagTrainingPreprocessing`. All the top-level
executables live in `utils/`, whereas various private internal classes
are defined in `src/`.

How to add variables
--------------------

To add a new variable, you first have to add it to the relevant
`struct`. There are currently two of these: `Track` and `Jet` which
are defined in the correspondingly named header files.

Once you've added a variable, you'll have to tell HDF5 that you want
to save it. This happens in `src/HDF5Defs.cxx`, and should be as
simple as adding a line like

```C++
INSERT(variable_name);
```

under the appropriate type (jet, track, etc).

Working document
----------------
See [here](https://docs.google.com/document/d/1i954ZC0ZX1NIc4t9K1sKhOXkjRRObpK9ANIPCjcqlvA/edit?usp=sharing)
