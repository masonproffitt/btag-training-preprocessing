#include "HDF5WriterAbstraction.hh"

#include "HDF5Writer.hh"
#include "HDF5Defs.hh"
#include "Track.hh"

// HDF5
#include "H5Cpp.h"

// system includes
#include <string>

namespace {
  const int CHUNK_SIZE = 256;
  const int N_TRACKS = 100;     // <-- max number of tracks to store
}

// Define the writer classes. These are simple classes that inherit
// from the Writer template.
class TrackWriter: public h5::Writer<Track>
{
public:
  TrackWriter(H5::CommonFG& file):
    h5::Writer<Track>(file, "track", N_TRACKS, CHUNK_SIZE)
    {}
};
class JetWriter: public h5::Writer1d<Jet>
{
public:
  JetWriter(H5::CommonFG& file):
    h5::Writer1d<Jet>(file, "jet", CHUNK_SIZE)
    {}
};


// Writer abstraction
HDF5WriterAbstraction::HDF5WriterAbstraction(const char* output_file_name):
  m_file(new H5::H5File(output_file_name, H5F_ACC_TRUNC)),
  m_track_writer(new TrackWriter(*m_file)),
  m_jet_writer(new JetWriter(*m_file))
{
}

HDF5WriterAbstraction::~HDF5WriterAbstraction() {
  delete m_file;
  delete m_track_writer;
  delete m_jet_writer;
}

void HDF5WriterAbstraction::add_tracks(std::vector<Track> tracks) {
  m_track_writer->add(tracks);
}

void HDF5WriterAbstraction::add_jet(const Jet& jet) {
  m_jet_writer->add(jet);
}

void HDF5WriterAbstraction::flush() {
  m_track_writer->flush();
  m_jet_writer->flush();
}

void HDF5WriterAbstraction::close() {
  m_track_writer->close();
  m_jet_writer->close();
}
