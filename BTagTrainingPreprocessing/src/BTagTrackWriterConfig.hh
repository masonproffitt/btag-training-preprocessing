#ifndef BTAG_TRACK_WRITER_CONFIG_HH
#define BTAG_TRACK_WRITER_CONFIG_HH

#include <vector>
#include <string>

struct BTagTrackWriterConfig {
  std::vector<std::string> double_variables;
  std::vector<std::string> float_variables;
  std::vector<std::string> int_variables;
  std::string name;
  std::vector<size_t> output_size;
};


#endif
