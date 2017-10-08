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
  std::vector<std::string> btag_float_variables;
  std::vector<std::string> btag_int_variables;
  // track variables
  std::string track_associator_name;
  std::vector<std::string> track_float_variables;
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
  template<typename I, typename O>
  void add_btag_fillers(VariableFillers&, const std::vector<std::string>&);
  template<typename I, typename O>
  void add_track_fillers(VariableFillers&, const std::vector<std::string>&,
                         O def_value);
  const xAOD::Jet* m_current_jet;
  std::string m_track_associator_name;
  std::vector<size_t> m_track_index;
  WriterXd* m_hdf5_jet_writer;
  WriterXd* m_hdf5_track_writer;
};


#endif
