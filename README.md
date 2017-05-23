AnalysisBase xAOD I/O Test(s)
=============================

This is some code to run I/O tests using the xAOD EDM, using the
AnalysisBase release.

To compile the code, do something like:

```bash
git clone https://:@gitlab.cern.ch:8443/akraszna/AnalysisBaseIOTests.git
asetup AnalysisBase,21.2,r22
mkdir build
cd build/
cmake ../AnalysisBaseIOTests/
make
```
