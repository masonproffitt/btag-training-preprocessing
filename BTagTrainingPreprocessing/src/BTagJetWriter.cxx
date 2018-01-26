#include "BTagJetWriter.hh"
#include "BTagJetWriterConfig.hh"
#include "HdfTuple.hh"


BTagJetWriter::BTagJetWriter(
  H5::CommonFG& output_file,
  const BTagJetWriterConfig& config)
{

  // create the variable fillers
  VariableFillers fillers;
  // in this case we convert doubles to floats to save space, note
  // that you can change the second parameter to a double to get full
  // precision.
  add_btag_fillers<double, float>(fillers, config.double_variables);
  add_btag_fillers<float>(fillers, config.float_variables);
  add_btag_fillers<int>(fillers, config.int_variables);
  add_truth_labels(fillers, config.truth_labels);

  // some things like 4 momenta have to be hand coded
  std::function<float(void)> pt = [this]() {
    return this->m_current_jet->pt();
  };
  fillers.add("pt", pt);
  std::function<float(void)> eta = [this]() {
    return this->m_current_jet->eta();
  };
  fillers.add("eta", eta);

  // now create the writer
  assert(config.name.size() > 0);
  m_hdf5_jet_writer = new WriterXd(output_file, config.name, fillers,{});
  assert(config.output_size.size() == 0);
}

BTagJetWriter::~BTagJetWriter() {
  m_hdf5_jet_writer->flush();
  delete m_hdf5_jet_writer;
}

void BTagJetWriter::write(const xAOD::Jet& jet) {
  m_current_jet = &jet;
  m_hdf5_jet_writer->fill_while_incrementing();
}

template<typename I, typename O>
void BTagJetWriter::add_btag_fillers(VariableFillers& vars,
                                     const std::vector<std::string>& names) {
  for (const auto& btag_var: names) {
    std::function<O(void)> filler = [this, btag_var]() {
      return this->m_current_jet->btagging()->auxdata<I>(btag_var);
    };
    vars.add(btag_var, filler);
  }
}

void BTagJetWriter::add_truth_labels(VariableFillers& vars,
                                     const std::vector<std::string>& names) {
  for (const auto& label: names) {
    std::function<int(void)> filler = [this, label]() {
      return this->m_current_jet->auxdata<int>(label);
    };
    vars.add(label, filler);
  }
}
