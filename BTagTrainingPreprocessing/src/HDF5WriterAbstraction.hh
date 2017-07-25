#ifndef HDF5_WRITER_ABSTRACTION_HH
#define HDF5_WRITER_ABSTRACTION_HH

#include "Track.hh"
#include "Jet.hh"

#include <vector>

// forward declare the writer classes. We can't currently use them in
// the same compilation unit as the xAOD classes because of ABI
// mismatch issues.
class TrackWriter;
class JetWriter;

namespace H5 {
  class H5File;
}

class HDF5WriterAbstraction
{
public:
  HDF5WriterAbstraction(const char* output_file_name);
  ~HDF5WriterAbstraction();
  HDF5WriterAbstraction(HDF5WriterAbstraction&) = delete;
  HDF5WriterAbstraction operator=(HDF5WriterAbstraction&) = delete;
  void add_tracks(std::vector<Track>);
  void add_jet(const Jet&);
  void flush();
  void close();
private:
  H5::H5File* m_file;
  TrackWriter* m_track_writer;
  JetWriter* m_jet_writer;
};

#endif
