#ifndef BTAG_TRACK_WRITER_HH
#define BTAG_TRACK_WRITER_HH

// Standard Library things
#include <string>
#include <vector>

namespace H5 {
  class CommonFG;
}
namespace xAOD {
  class TrackParticle_v1;
  typedef TrackParticle_v1 TrackParticle;
}

class VariableFillers;
class BTagWriterConfig;
class WriterXd;

class BTagTrackWriter
{
public:
  typedef std::vector<const xAOD::TrackParticle*> Tracks;
  BTagTrackWriter(
    H5::CommonFG& output_file,
    const BTagWriterConfig&);
  ~BTagTrackWriter();
  BTagTrackWriter(BTagTrackWriter&) = delete;
  BTagTrackWriter operator=(BTagTrackWriter&) = delete;
  void write(const BTagTrackWriter::Tracks& tracks);
private:
  template<typename I, typename O = I>
  void add_track_fillers(VariableFillers&, const std::vector<std::string>&,
                         O def_value);
  const Tracks* m_current_tracks;
  std::vector<size_t> m_track_index;
  WriterXd* m_hdf5_track_writer;
};

#endif
