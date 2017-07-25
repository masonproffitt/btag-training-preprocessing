Flavor Tagging Ntuple Dumper
============================

This is to dump b-tagging info from an AnalysisBase release

To compile the code, run:

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
