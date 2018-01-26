#include "BTagTrackWriter.hh"
#include "BTagTrackWriterConfig.hh"
#include "HdfTuple.hh"

// Less Standard Libraries (for atlas)
#include "H5Cpp.h"

// ATLAS things
#include "xAODTracking/TrackParticle.h"

BTagTrackWriter::BTagTrackWriter(
  H5::CommonFG& output_file,
  const BTagTrackWriterConfig& config):
  m_current_tracks()
{

  VariableFillers fillers;
  // add the variables passed as strings
  add_track_fillers<float>(fillers, config.float_variables, NAN);
  // We can convert the doubles to floats to save space. Change the
  // float below to a double if you want to save with full precision.
  add_track_fillers<double, float>(fillers, config.double_variables, NAN);
  add_track_fillers<int>(fillers, config.int_variables, -1);

  // hard coded 4 momentum fillers
  std::function<float(void)> pt = [this]() -> float {
    size_t index = this->m_track_index.at(0);
    if (index >= m_current_tracks->size()) return NAN;
    return m_current_tracks->at(index)->pt();
  };
  fillers.add("pt", pt);
  std::function<float(void)> eta = [this]() -> float {
    size_t index = this->m_track_index.at(0);
    if (index >= m_current_tracks->size()) return NAN;
    return m_current_tracks->at(index)->eta();
  };
  fillers.add("eta", eta);

  // build the output dataset
  assert(config.name.size() > 0);
  assert(config.output_size.size() == 1);
  std::vector<hsize_t> size(config.output_size.begin(),
                            config.output_size.end());
  m_hdf5_track_writer = new WriterXd(output_file, config.name,
                                     fillers, size);
}

BTagTrackWriter::~BTagTrackWriter() {
  m_hdf5_track_writer->flush();
  delete m_hdf5_track_writer;
}

void BTagTrackWriter::write(const BTagTrackWriter::Tracks& tracks) {
  m_current_tracks = &tracks;
  m_hdf5_track_writer->fill_while_incrementing(m_track_index);
}

template<typename I, typename O>
void BTagTrackWriter::add_track_fillers(VariableFillers& vars,
                                      const std::vector<std::string>& names,
                                      O def_value) {

  for (const auto& btag_var: names) {
    std::function<O(void)> filler = [this, btag_var, def_value]() -> O {
      size_t index = this->m_track_index.at(0);
      if (index >= m_current_tracks->size()) {
        return def_value;
      }
      const xAOD::TrackParticle *trk = m_current_tracks->at(index);
      return trk->auxdata<I>(btag_var);
    };
    vars.add(btag_var, filler);
  }
}
