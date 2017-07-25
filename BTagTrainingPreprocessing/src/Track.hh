#ifndef TRACK_HH
#define TRACK_HH

// track struct
struct Track {
  float pt;
  bool mask;
  // mask just keeps track of if the track is defined we set it to
  // true by default, but the HDF5 writer allocates tracks where mask
  // is set to false
  Track(): mask(true) {}
};

#endif // TRACK
