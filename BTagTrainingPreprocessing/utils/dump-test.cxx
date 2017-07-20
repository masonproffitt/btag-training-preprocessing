/// @file dump-test.cxx
/// @brief Test reading the main calo cluster and track particle container
///
/// This test simply reads in the static payload of the track particle
/// container of a primary xAOD. And checks how fast this can actually
/// be done.

// local inclues
#include "SomeTool.h"

// System include(s):
#include <memory>

// ROOT include(s):
#include <TFile.h>
#include <TError.h>

// AnalysisBase tool include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/tools/ReturnCheck.h"

// EDM include(s):
#include "xAODCore/tools/PerfStats.h"
#include "xAODCore/tools/IOStats.h"
#include "xAODCore/tools/ReadStats.h"
#include "xAODCaloEvent/CaloClusterContainer.h"
#include "xAODTracking/TrackParticleContainer.h"
#include "xAODJet/JetContainer.h"

int main( int argc, char* argv[] ) {

  // test the added tool in SomeTool.hh
  std::cout << "SomeTool gives: " << getANumber() << std::endl;

   // The name of the application:
   static const char* APP_NAME = "BTagTestDumper";

   // Check that at least one input file was provided:
   if( argc < 2 ) {
      Error( APP_NAME, "Usage: %s <file1> [file2] ...", APP_NAME );
      return 1;
   }

   // Set up the environment:
   RETURN_CHECK( APP_NAME, xAOD::Init() );

   // Set up the event object:
   xAOD::TEvent event( xAOD::TEvent::kClassAccess );

   // Start the measurement:
   auto& ps = xAOD::PerfStats::instance();
   ps.start();

   // Dummy variable:
   double dummy = 0.0;

   // Loop over the specified files:
   for( int i = 1; i < argc; ++i ) {

      // Open the file:
      std::unique_ptr< TFile > ifile( TFile::Open( argv[ i ], "READ" ) );
      if( ( ! ifile.get() ) || ifile->IsZombie() ) {
         Error( APP_NAME, "Couldn't open file: %s", argv[ i ] );
         return 1;
      }
      Info( APP_NAME, "Opened file: %s", argv[ i ] );

      // Connect the event object to it:
      RETURN_CHECK( APP_NAME, event.readFrom( ifile.get() ) );

      // Loop over its events:
      const Long64_t entries = event.getEntries();
      for( Long64_t entry = 0; entry < entries; ++entry ) {

         // Load the event:
         if( event.getEntry( entry ) < 0 ) {
            Error( APP_NAME, "Couldn't load entry %lld from file: %s",
                   entry, argv[ i ] );
            return 1;
         }

         // Print some status:
         if( ! ( entry % 500 ) ) {
            Info( APP_NAME, "Processing entry %lld / %lld", entry, entries );
         }

         // Read the track particles:
         const xAOD::TrackParticleContainer *tpc = 0;
         RETURN_CHECK( APP_NAME, event.retrieve(tpc, "InDetTrackParticles") );

         // Read in its core variables:
         for (const xAOD::TrackParticle *tp : *tpc) {
            dummy += tp->pt();
         }

         const xAOD::JetContainer *jets = 0;
         RETURN_CHECK( APP_NAME, event.retrieve(jets, "AntiKtVR30Rmax4Rmin02TrackJets") );

         for (const xAOD::Jet *jet : *jets) {
            Info( APP_NAME, "MV2c10 discriminant: %g", jet->btagging()->auxdata<double>("MV2c10_discriminant") );
         }
      }
   }

   // Make a dummy printout just to make sure that C++ optimisations don't
   // remove the file reading commands:
   Info( APP_NAME, "dummy = %g", dummy );

   // Stop the measurement:
   ps.stop();
   xAOD::IOStats::instance().stats().Print( "Summary" );

   // Return gracefully:
   return 0;
}