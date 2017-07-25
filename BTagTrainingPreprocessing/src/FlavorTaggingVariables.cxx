#include "FlavorTaggingVariables.h"

void fillFlavorTaggingVariables(FlavorTaggingVariables &vars, const xAOD::Jet &jet)
{
	const xAOD::BTagging *btagging = jet.btagging();

	vars.mv2c10_discriminant = btagging->auxdata<double>("MV2c10_discriminant");

	btagging->taggerInfo(vars.jf_nvtx, xAOD::BTagInfo::JetFitter_nVTX);
	btagging->taggerInfo(vars.jf_nvtx1t, xAOD::BTagInfo::JetFitter_nSingleTracks);
	btagging->taggerInfo(vars.jf_ntrkAtVx, xAOD::BTagInfo::JetFitter_nTracksAtVtx);
	btagging->taggerInfo(vars.jf_n2tv, xAOD::BTagInfo::JetFitter_N2Tpair);
	btagging->taggerInfo(vars.jf_efrc, xAOD::BTagInfo::JetFitter_energyFraction);
	btagging->taggerInfo(vars.jf_mass, xAOD::BTagInfo::JetFitter_mass);
	btagging->taggerInfo(vars.jf_sig3d, xAOD::BTagInfo::JetFitter_significance3d);
	btagging->taggerInfo(vars.jf_dphi, xAOD::BTagInfo::JetFitter_deltaphi);
	btagging->taggerInfo(vars.jf_deta, xAOD::BTagInfo::JetFitter_deltaeta);
	btagging->variable<float>("JetFitter", "massUncorr" , vars.jf_mass_uncor);
	btagging->variable<float>("JetFitter", "dRFlightDir", vars.jf_dR_flight);

	vars.ip2d_pb = btagging->IP2D_pb();
	vars.ip2d_pc = btagging->IP2D_pc();
	vars.ip2d_pu = btagging->IP2D_pu();

	vars.ip3d_pb = btagging->IP3D_pb();
	vars.ip3d_pc = btagging->IP3D_pc();
	vars.ip3d_pu = btagging->IP3D_pu();

	btagging->taggerInfo(vars.sv1_mass, xAOD::BTagInfo::SV1_masssvx);
	btagging->taggerInfo(vars.sv1_efrc, xAOD::BTagInfo::SV1_efracsvx);
	btagging->taggerInfo(vars.sv1_n2t, xAOD::BTagInfo::SV1_N2Tpair);
	btagging->taggerInfo(vars.sv1_ntrkv, xAOD::BTagInfo::SV1_NGTinSvx);
	btagging->taggerInfo(vars.sv1_sig3d, xAOD::BTagInfo::SV1_normdist);
	btagging->variable<float>("SV1", "dstToMatLay" , vars.sv1_distmatlay);
	btagging->variable<float>("SV1", "deltaR", vars.sv1_dR);
	btagging->variable<float>("SV1", "Lxy", vars.sv1_Lxy);
	btagging->variable<float>("SV1", "L3d", vars.sv1_L3d);
}
