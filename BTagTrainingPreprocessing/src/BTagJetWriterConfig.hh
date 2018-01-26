#ifndef BTAG_JET_WRITER_CONFIG_HH
#define BTAG_JET_WRITER_CONFIG_HH

#include <vector>
#include <string>

struct BTagJetWriterConfig {
  std::vector<std::string> double_variables;
  std::vector<std::string> float_variables;
  std::vector<std::string> int_variables;
  std::vector<std::string> truth_labels;
  std::string name;
};


#endif
