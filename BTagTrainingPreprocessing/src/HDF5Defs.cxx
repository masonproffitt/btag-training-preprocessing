// this next line is magic so we can use the local version of
// HDF5, see here: https://stackoverflow.com/a/33395489
#define _GLIBCXX_USE_CXX11_ABI 0

#include "HDF5Defs.hh"
#include "HDF5Writer.hh"

namespace h5 {

  // ======= jet type ============
  template<>
  H5::DataType get_type<Jet>() {
    H5::CompType type(sizeof(Jet));
#define INSERT(name) H5_INSERT(type, Jet, name)

    // this is where you add new jet variables
	INSERT(mv2c10_discriminant);

	INSERT(jf_nvtx);
	INSERT(jf_nvtx1t);
	INSERT(jf_ntrkAtVx);
	INSERT(jf_n2tv);
	INSERT(jf_efrc);
	INSERT(jf_mass);
	INSERT(jf_sig3d);
	INSERT(jf_dphi);
	INSERT(jf_deta);
	INSERT(jf_mass_uncor);
	INSERT(jf_dR_flight);

	INSERT(ip2d_pb);
	INSERT(ip2d_pc);
	INSERT(ip2d_pu);

	INSERT(ip3d_pb);
	INSERT(ip3d_pc);
	INSERT(ip3d_pu);

	INSERT(sv1_n2t);
	INSERT(sv1_ntrkv);
	INSERT(sv1_mass);
	INSERT(sv1_efrc);
	INSERT(sv1_sig3d);
	INSERT(sv1_distmatlay);
	INSERT(sv1_dR);
	INSERT(sv1_Lxy);
	INSERT(sv1_L3d);

#undef INSERT
    return type;
  }

  // ======= track type ===========
  template<>
  H5::DataType get_type<Track>() {
    H5::CompType type(sizeof(Track));
#define INSERT(name) H5_INSERT(type, Track, name)

    // This is where you add new variables
    INSERT(pt);
    INSERT(mask);

#undef INSERT
    return type;
  }

  template<>
  Track get_empty<Track>() {
    Track cl;

    // make sure you zero all the new track variables here
    cl.pt = 0;

    // mask is to tell whoever reads it that this track was not
    // defined. The constructor sets it to true by default, so tracks
    // that are added by the variable dumper (and not by the
    // HDF5Writer) will have this set to true by default.
    cl.mask = false;
    return cl;
  }

}
