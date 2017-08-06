#include "Jet.hh"

void fillFlavorTaggingVariables(const xAOD::Jet &jet, Jet &out_jet)
{
	const xAOD::BTagging *btagging = jet.btagging();

	out_jet.mv2c10_discriminant = btagging->auxdata<double>("MV2c10_discriminant");

	btagging->taggerInfo(out_jet.jf_nvtx, xAOD::BTagInfo::JetFitter_nVTX);
	btagging->taggerInfo(out_jet.jf_nvtx1t, xAOD::BTagInfo::JetFitter_nSingleTracks);
	btagging->taggerInfo(out_jet.jf_ntrkAtVx, xAOD::BTagInfo::JetFitter_nTracksAtVtx);
	btagging->taggerInfo(out_jet.jf_n2tv, xAOD::BTagInfo::JetFitter_N2Tpair);
	btagging->taggerInfo(out_jet.jf_efrc, xAOD::BTagInfo::JetFitter_energyFraction);
	btagging->taggerInfo(out_jet.jf_mass, xAOD::BTagInfo::JetFitter_mass);
	btagging->taggerInfo(out_jet.jf_sig3d, xAOD::BTagInfo::JetFitter_significance3d);
	btagging->taggerInfo(out_jet.jf_dphi, xAOD::BTagInfo::JetFitter_deltaphi);
	btagging->taggerInfo(out_jet.jf_deta, xAOD::BTagInfo::JetFitter_deltaeta);
	btagging->variable<float>("JetFitter", "massUncorr" , out_jet.jf_mass_uncor);
	btagging->variable<float>("JetFitter", "dRFlightDir", out_jet.jf_dR_flight);

	out_jet.ip2d_pb = btagging->IP2D_pb();
	out_jet.ip2d_pc = btagging->IP2D_pc();
	out_jet.ip2d_pu = btagging->IP2D_pu();

	out_jet.ip3d_pb = btagging->IP3D_pb();
	out_jet.ip3d_pc = btagging->IP3D_pc();
	out_jet.ip3d_pu = btagging->IP3D_pu();

	btagging->taggerInfo(out_jet.sv1_mass, xAOD::BTagInfo::SV1_masssvx);
	btagging->taggerInfo(out_jet.sv1_efrc, xAOD::BTagInfo::SV1_efracsvx);
	btagging->taggerInfo(out_jet.sv1_n2t, xAOD::BTagInfo::SV1_N2Tpair);
	btagging->taggerInfo(out_jet.sv1_ntrkv, xAOD::BTagInfo::SV1_NGTinSvx);
	btagging->taggerInfo(out_jet.sv1_sig3d, xAOD::BTagInfo::SV1_normdist);
	btagging->variable<float>("SV1", "dstToMatLay" , out_jet.sv1_distmatlay);
	btagging->variable<float>("SV1", "deltaR", out_jet.sv1_dR);
	btagging->variable<float>("SV1", "Lxy", out_jet.sv1_Lxy);
	btagging->variable<float>("SV1", "L3d", out_jet.sv1_L3d);

	out_jet.rnnip_pu = btagging->auxdata<double>("rnnip_pu");
	out_jet.rnnip_pc = btagging->auxdata<double>("rnnip_pc");
	out_jet.rnnip_pb = btagging->auxdata<double>("rnnip_pb");
	out_jet.rnnip_ptau = btagging->auxdata<double>("rnnip_ptau");
}
