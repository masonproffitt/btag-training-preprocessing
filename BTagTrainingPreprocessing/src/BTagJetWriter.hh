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

class BTagWriterConfig;

class BTagJetWriter
{
public:
  BTagJetWriter(
    H5::CommonFG& output_file,
    const BTagWriterConfig&);
  ~BTagJetWriter();
  BTagJetWriter(BTagJetWriter&) = delete;
  BTagJetWriter operator=(BTagJetWriter&) = delete;
  void write(const xAOD::Jet& jet);
private:
  template<typename I, typename O = I>
  void add_btag_fillers(VariableFillers&, const std::vector<std::string>&);
  const xAOD::Jet* m_current_jet;
  WriterXd* m_hdf5_jet_writer;
};


#endif
