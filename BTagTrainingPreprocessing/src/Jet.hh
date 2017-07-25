#ifndef JET_HH
#define JET_HH

#include "xAODJet/Jet.h"

typedef struct Jet
{
	double mv2c10_discriminant;

	int jf_nvtx;
	int jf_nvtx1t;
	int jf_ntrkAtVx;
	int jf_n2tv;
	float jf_efrc;
	float jf_mass;
	float jf_sig3d;
	float jf_dphi;
	float jf_deta;
	float jf_mass_uncor;
	float jf_dR_flight;

	double ip2d_pb;
	double ip2d_pc;
	double ip2d_pu;

	double ip3d_pb;
	double ip3d_pc;
	double ip3d_pu;

	int sv1_n2t;
	int sv1_ntrkv;
	float sv1_mass;
	float sv1_efrc;
	float sv1_sig3d;
	float sv1_distmatlay;
	float sv1_dR;
	float sv1_Lxy;
	float sv1_L3d;
} Jet;

void fillFlavorTaggingVariables(const xAOD::Jet &jet, Jet &out_jet);

#endif // JET_HH
