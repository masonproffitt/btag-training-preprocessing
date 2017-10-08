#include "BTagJetWriter.hh"
#include "HdfTuple.hh"

BTagJetWriter::BTagJetWriter(
  H5::CommonFG& output_file,
  const BTagJetWriterConfig& config) {

  // We can cast the doubles to floats to save space. This typedef
  // controls what type we end up saving.
  typedef float outdouble_t;

  VariableFillers fillers;
  for (const auto& btag_var: config.btag_double_variables) {
    std::function<outdouble_t(void)> filler = std::bind(
      [this, btag_var]() {
        return m_current_jet->btagging()->auxdata<double>(btag_var);
      });
    fillers.add(btag_var, filler);
  }
  m_hdf5_writer = new WriterXd(output_file, "high_level", fillers, {});
}

BTagJetWriter::~BTagJetWriter() {
  m_hdf5_writer->flush();
  delete m_hdf5_writer;
}

void BTagJetWriter::write_jet(const xAOD::Jet& jet) {
  m_current_jet = &jet;
  m_hdf5_writer->fill_while_incrementing();
}
