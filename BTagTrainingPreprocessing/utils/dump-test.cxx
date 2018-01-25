/// @file dump-test.cxx
/// @brief Test reading the main calo cluster and track particle container
///
/// This test simply reads in the static payload of the track particle
/// container of a primary xAOD. And checks how fast this can actually
/// be done.

// local inclues
#include "Track.hh"
#include "Jet.hh"

// new way to do local things
#include "BTagWriterConfig.hh"
#include "BTagJetWriter.hh"
#include "BTagTrackWriter.hh"

// System include(s):
#include <memory>

// ROOT include(s):
#include <TFile.h>
#include <TError.h>
#include <TLorentzVector.h>

// HDF includes
#include "H5Cpp.h"

// AnalysisBase tool include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/ReturnCheck.h"

// EDM include(s):
#include "xAODCore/tools/PerfStats.h"
#include "xAODCore/tools/IOStats.h"
#include "xAODCore/tools/ReadStats.h"
#include "JetCalibTools/JetCalibrationTool.h"
#include "JetSelectorTools/JetCleaningTool.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "JetMomentTools/JetVertexTaggerTool.h"
#include "JetJvtEfficiency/JetJvtEfficiency.h"
#include "InDetTrackSelectionTool/InDetTrackSelectionTool.h"
#include "xAODJet/JetContainer.h"
#include "xAODTruth/TruthEventContainer.h"

int main (int argc, char *argv[])
{
	// The name of the application:
	static const char *APP_NAME = "BTagTestDumper";

	// Check that at least one input file was provided:
	if (argc < 2) {
		Error( APP_NAME, "Usage: %s <file1> [file2] ...", APP_NAME );
		return 1;
	}

	// Set up the environment:
	RETURN_CHECK( APP_NAME, xAOD::Init() );

	// Set up the event object:
	xAOD::TEvent event(xAOD::TEvent::kClassAccess);

	// Initialize JetCalibrationTool with release 21 recommendations
	JetCalibrationTool calib_tool("JetCalibToolAntiKt4EMTopo");
	calib_tool.setProperty("JetCollection", "AntiKt4EMTopo");
	calib_tool.setProperty("ConfigFile", "JES_MC16Recommendation_Aug2017.config");
	calib_tool.setProperty("CalibSequence", "JetArea_Residual_EtaJES_GSC");
	calib_tool.setProperty("IsData", false);
	RETURN_CHECK( APP_NAME, calib_tool.initialize() );

	JetCleaningTool jetcleaningtool("JetCleaningTool", JetCleaningTool::LooseBad, false);
	RETURN_CHECK( APP_NAME, jetcleaningtool.initialize() );
	
	InDet::InDetTrackSelectionTool indettrackselectiontool("InDetTrackSelectionTool", "Loose");
	RETURN_CHECK( APP_NAME, indettrackselectiontool.initialize() );
	
	JetVertexTaggerTool jvttool("JetVertexTaggerTool");
	RETURN_CHECK( APP_NAME, jvttool.initialize() );
	
	CP::JetJvtEfficiency jvtefficiencytool("JetJvtEfficiency");
	jvtefficiencytool.setProperty("WorkingPoint", "Medium");
	jvtefficiencytool.setProperty("SFFile","JetJvtEfficiency/Moriond2017/JvtSFFile_EM.root");
	RETURN_CHECK( APP_NAME, jvtefficiencytool.initialize() );

	// new way to do output files
	H5::H5File output("output.h5", H5F_ACC_TRUNC);
	// set up jet writer
	BTagWriterConfig jet_cfg;
	jet_cfg.double_variables = {"pt", "eta", "MV2c10_discriminant", "IP2D_pb", "IP2D_pc", "IP2D_pu", "IP3D_pb", "IP3D_pc", "IP3D_pu", "SV1_pu", "SV1_pb", "SV1_pc", "rnnip_pu", "rnnip_pc", "rnnip_pb", "rnnip_ptau"};
	jet_cfg.float_variables = {"JetFitter_energyFraction", "JetFitter_mass", "JetFitter_significance3d", "JetFitter_deltaphi", "JetFitter_deltaeta", "JetFitter_massUncorr", "JetFitter_dRFlightDir", "SV1_masssvx", "SV1_efracsvx", "SV1_significance3d", "SV1_dstToMatLay", "SV1_deltaR", "SV1_Lxy", "SV1_L3d"};
	jet_cfg.int_variables = {"JetFitter_nVTX", "JetFitter_nSingleTracks", "JetFitter_nTracksAtVtx", "JetFitter_N2Tpair", "SV1_N2Tpair", "SV1_NGTinSvx", "PartonTruthLabelID", "HadronConeExclTruthLabelID"};
	jet_cfg.name = "jets";
	BTagJetWriter jet_writer(output, jet_cfg);
	// set up track writer
	BTagWriterConfig track_cfg;
	track_cfg.name = "tracks";
	track_cfg.double_variables = {"pt", "eta"};
	track_cfg.float_variables = {"chiSquared", "d0"};
	track_cfg.output_size = {10};
	BTagTrackWriter track_writer(output, track_cfg);

	// Start the measurement:
	auto ps = xAOD::PerfStats::instance();
	ps.start();

	// Loop over the specified files:
	for (int i = 1; i < argc; ++i) {

		// Open the file:
		std::unique_ptr<TFile> ifile(TFile::Open(argv[i], "READ"));
		if ( ! ifile.get() || ifile->IsZombie()) {
			Error( APP_NAME, "Couldn't open file: %s", argv[i] );
			return 1;
		}
		Info( APP_NAME, "Opened file: %s", argv[i] );

		// Connect the event object to it:
		RETURN_CHECK( APP_NAME, event.readFrom(ifile.get()) );

		// Loop over its events:
		const Long64_t entries = event.getEntries();
		for (Long64_t entry = 0; entry < entries; ++entry) {

			// Load the event:
			if (event.getEntry(entry) < 0) {
				Error( APP_NAME, "Couldn't load entry %lld from file: %s", entry, argv[i] );
				return 1;
			}

			// Print some status:
			if ( ! (entry % 500)) {
				Info( APP_NAME, "Processing entry %lld / %lld", entry, entries );
			}

			const xAOD::JetContainer *jets = 0;
			RETURN_CHECK( APP_NAME, event.retrieve(jets, "AntiKt4EMTopoJets") );

			const xAOD::TruthEventContainer *truth_events = 0;
			RETURN_CHECK( APP_NAME, event.retrieve(truth_events, "TruthEvents") );

			for (const xAOD::Jet *jet : *jets) {
				xAOD::Jet *calib_jet;
				calib_tool.calibratedCopy(*jet, calib_jet);
				jvttool.updateJvt(*calib_jet);
				if ( ! jetcleaningtool.keep(*calib_jet) || ! jvtefficiencytool.passesJvtCut(*calib_jet)) {
					continue;
				}
				if (calib_jet->pt() < 20000 || fabs(calib_jet->eta()) > 2.5) {
					continue;
				}

				bool overlap_skip = false;
				for (const xAOD::TruthEvent *truth_event : *truth_events) {
					for(unsigned truth_event_index = 0; truth_event_index < truth_event->nTruthParticles(); truth_event_index++) {
						const xAOD::TruthParticle *truth_particle = truth_event->truthParticle(truth_event_index);
						if (abs(truth_particle->pdgId()) == 11) {
							if (truth_particle->pt() < 10000) {
								continue;
							}
							TLorentzVector truth_lorentz_vector;
							truth_lorentz_vector.SetPtEtaPhiM(truth_particle->pt(), truth_particle->eta(), truth_particle->phi(), truth_particle->m());
							if (calib_jet->p4().DeltaR(truth_lorentz_vector) < 0.3) {
								overlap_skip = true;
								break;
							}
						}
					}
					if (overlap_skip) {
						break;
					}
				}
				if (overlap_skip) {
					continue;
				}

				jet_writer.write(*calib_jet);

				// make a vector to store tracks to HDF5.
				std::vector<const xAOD::TrackParticle *> tracks;
				// Read the track particles:
				const xAOD::BTagging *btagging = calib_jet->btagging();
				auto links = btagging->auxdata<std::vector<ElementLink<xAOD::TrackParticleContainer> > >("BTagTrackToJetAssociator");
				for (const auto &link : links) {
					if(link.isValid()) {
						const xAOD::TrackParticle *tp = *link;
						if ( ! indettrackselectiontool.accept(tp)) {
							continue;
						}
						// do some kind of slection here, plus sorting
						tracks.push_back(tp);
					}
				}
				track_writer.write(tracks);

				delete calib_jet;
			}
		}
	}
	// jet_writer.flush();
	// track_writer.flush();

	// Stop the measurement:
	ps.stop();
	xAOD::IOStats::instance().stats().Print("Summary");

	// Return gracefully:
	return 0;
}
