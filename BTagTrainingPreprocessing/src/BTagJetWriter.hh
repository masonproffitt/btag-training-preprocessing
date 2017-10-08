#ifndef BTAG_JET_WRITER_HH
#define BTAG_JET_WRITER_HH

// Local includes
#include "HdfTuple.hh"

// Less Standard Libraries (for atlas)
#include "H5Cpp.h"

// ATLAS things
#include "xAODJet/JetContainer.h"

// Standard Library things
#include <string>
#include <vector>


struct BTagJetWriterConfig {
  std::vector<std::string> btag_double_variables;
};

class BTagJetWriter
{
public:
  BTagJetWriter(
    H5::CommonFG& output_file,
    const BTagJetWriterConfig&);
  ~BTagJetWriter();
  BTagJetWriter(BTagJetWriter&) = delete;
  BTagJetWriter operator=(BTagJetWriter&) = delete;
  void write_jet(const xAOD::Jet& jet);
private:
  const xAOD::Jet* m_current_jet;
  WriterXd* m_hdf5_writer;
};


#endif
