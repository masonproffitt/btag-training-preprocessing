#include "BTagJetWriter.hh"
#include "HdfTuple.hh"


BTagJetWriter::BTagJetWriter(
  H5::CommonFG& output_file,
  const BTagJetWriterConfig& config):
  m_track_associator_name(config.track_associator_name)
{

  // We can cast the doubles to floats to save space. This typedef
  // controls what type we end up saving.
  typedef float outdouble_t;

  VariableFillers fillers;
  add_btag_fillers<double, float>(fillers, config.btag_double_variables);
  add_btag_fillers<float, float>(fillers, config.btag_float_variables);
  add_btag_fillers<int, int>(fillers, config.btag_int_variables);
  m_hdf5_jet_writer = new WriterXd(output_file, "high_level", fillers, {});

  VariableFillers track_fillers;
  add_track_fillers<float, float>(track_fillers,
                                  config.track_float_variables, NAN);
  m_hdf5_track_writer = new WriterXd(output_file, "tracks",
                                     track_fillers, {10});
}

BTagJetWriter::~BTagJetWriter() {
  m_hdf5_jet_writer->flush();
  delete m_hdf5_jet_writer;
  m_hdf5_track_writer->flush();
  delete m_hdf5_track_writer;
}

void BTagJetWriter::write_jet(const xAOD::Jet& jet) {
  m_current_jet = &jet;
  m_hdf5_jet_writer->fill_while_incrementing();
  m_hdf5_track_writer->fill_while_incrementing(m_track_index);
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

template<typename I, typename O>
void BTagJetWriter::add_track_fillers(VariableFillers& vars,
                                      const std::vector<std::string>& names,
                                      O def_value) {
  typedef ElementLink<xAOD::TrackParticleContainer> TrackLink;
  typedef std::vector<TrackLink> TrackLinks;

  for (const auto& btag_var: names) {
    std::function<O(void)> filler = [this, btag_var, def_value]() {
      TrackLinks links = this->m_current_jet->btagging()->auxdata<TrackLinks>(
        this->m_track_associator_name);
      size_t index = this->m_track_index.at(0);
      if (index >= links.size()) {
        return def_value;
      }
      const xAOD::TrackParticle *trk = *links.at(index);
      return trk->auxdata<I>(btag_var);
    };
    vars.add(btag_var, filler);
  }
}
