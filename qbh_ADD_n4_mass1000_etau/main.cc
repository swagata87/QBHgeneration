//TOF
#include <climits>

#include "Pythia8/Pythia.h"
using namespace Pythia8; 

#include "qbh.h"
using namespace QBH; 

/*****************************************************************************/
/* Event generator code (main program).                                      */
/*****************************************************************************/
int main()
{
  bool status;

  // Output LHEF file.
  const bool OUTPUT = true;

  // Declare Pythia object.
  Pythia* pythia = new Pythia();

  // Declare and initialize quantum black hole object.
  bool initialize = true;
  QuantumBlackHole* qbh = new QuantumBlackHole(pythia,initialize);

  // Decalare derived LHA user process object.
  dLHAup* lhaPtr = new dLHAup;

  pythia->setLHAupPtr(lhaPtr);  
  pythia->readString("Beams:frameType = 5");

  // Number of event, black hole charge, and inital state.
  pythia->readString("Main:NumberOfEvents = 50000");

  /// QCD scale definition
  qbh->setQscale(false); /// Definition of QCD scale for PDFs false(= QBH mass), true (= inverse gravitational radius) (Default = true)

  qbh->setYRform(false); /// Use YR-factors (Default = false)
  qbh->setTrap(false); /// User YR trapped surface calculation (Default = false)

  /// SM symmetries
  qbh->setSM(false); /// Conserve global symmetries (Default = true)

  /// Majorana neutrinos
  qbh->setMajorana(false); /// neutrinos are majorana (true) or dirac (false) (Default = false) 

  /// Neutrino handedness
  qbh->setChiral(true); /// neutrinos are left-handed only (false) or left and right-handed (true) (Default = true)

  /// Higgs
  qbh->setHiggs(false); /// Include Higgs as allowed particle (Default = true)

  /// Graviton
  qbh->setGraviton(false); /// Include Graviton as allowed particle (Default = true)

  /// Totel number of dimensions
  qbh->setTotdim(4 + 4); /// Total number of spacetime dimensions 5-11 allowed (Default = 10)

  /// Planck scale definition
  /// RS or ADD black hole
  qbh->setPlanckdef(3); /// Definition of the planck scale 1 (= Randall-Sundrum), 2 (= Dimopoulos-Landsberg), 3 (= PDG), else (= Giddings-Thomas definition) (Default = 3)
  qbh->setRS1(false); /// false (= ADD black hole), true (= Randall-Sundrum type-1 black hole) (Default = false)
  
  /// Planck mass
  qbh->setMplanck(1000); /// fundamental planck scale (Default = 1000)    

  /// Electric charge
  qbh->setQstate(0); /// Three time electric charge [-4,-3,-2,-1,0,1,2,3,4] allowed, 9 for all partons (Default = 9)

  /// Initial state
  qbh->setIstate(0); /// Initial state 0 (q-q), 1 (q-g), 2 (g-g), 3 (all) (Default = 3)

  /// Min QBH mass
  qbh->setMinmass(1000); /// Minimum quantum black hole mass (Default = 1000)

  /// Max QBH mass
  qbh->setMaxmass(13000); /// Maximum qunatum black hole mass (Default = 14000)
  
  /// Center of mass energy
  qbh->setEcm(13000); /// Proton-proton center of mass energy (Default = 14000)



  // Initialize PDFs.
  qbh->setLHAglue(10042);  //CTEQ6L1
  // qbh->setLHAglue(192800); //NNPDF21_100
  // qbh->setLHAglue(10800);  //CT10
  // qbh->setLHAglue(10550);  //CTEQ6.6
  // qbh->setLHAglue(19050);  //CTEQ5M
  // qbh->setLHAglue(21000);  //MSTW2008lo
  // qbh->setLHAglue(29041);  //MRST98lo fit
  // qbh->setLHAglue(0);      //PYTHIA internal

  // Set some PYTHIA switches.
  (void)pythia->readString("SoftQCD:nonDiffractive = off");
  (void)pythia->readString("SoftQCD:all       = off");
  (void)pythia->readString("PartonLevel:ISR   = off");
  (void)pythia->readString("PartonLevel:FSR   = off");
  (void)pythia->readString("PartonLevel:MPI    = off");
  (void)pythia->readString("HadronLevel:all   = off");
  (void)pythia->readString("Check:history     = on");
  (void)pythia->readString("Check:nErrList    = 10");

  if (OUTPUT) (void)lhaPtr->openLHEF("QBH_ADD_M1000_nDim4_LHEFfile_etau.lhe");

  // Initialize Pythia object.
  status = pythia->init();

  if (OUTPUT) (void)lhaPtr->initLHEF();  
  delete qbh;

  // Loop over events.
  if (status) {
    for (int iEvent=0;iEvent<pythia->mode("Main:numberOfEvents"); ++iEvent) {
      //std::cout << "\n evt " << iEvent << std::endl;
      // Generate event.
      status = pythia->next();
      if (!status) continue;

      // Event listing.
      //      if (iEvent < pythia->mode("Next:numberShowEvent")) {
      if (iEvent < 2) {
        //pythia->info.list();
        pythia->process.list();
        //pythia->event.list();
      }


      // Process analysis.
      //      for (int i=0;i<pythia->process.size();i++) {
        // Black hole.
	///std::cout << "process no " << i << " id " << pythia->process[i].id() << std::endl; 
        //if (pythia->process[i].id() == 40) {
        //  double px = pythia->process[3].px() + pythia->process[4].px();
        //  double py = pythia->process[3].py() + pythia->process[4].py();
        //  double pz = pythia->process[3].pz() + pythia->process[4].pz();
        //  double e  = pythia->process[3].e()  + pythia->process[4].e();
        //  fprintf(stream,"%f %f %f %f %f\n",px,py,pz,e,pythia->process[i].m());
      // }
      //}
      // PDG ID codes.
      //fprintf(stream,"%d %d\n",pythia->process[5].id(),pythia->process[6].id());
      // Particle kinematics.
      //fprintf(stream,"%f %f %f %f %f\n",
      //               pythia->process[5].px(),
      //               pythia->process[5].py(),
      //               pythia->process[5].pz(),
      //               pythia->process[5].e(),
      //               pythia->process[5].m());
      //   fprintf(stream,"%f %f %f %f %f\n",
      //               pythia->process[6].px(),
      //               pythia->process[6].py(),
      //               pythia->process[6].pz(),
      //               pythia->process[6].e(),
      //               pythia->process[6].m());


      if ((abs(pythia->process[5].id()) == 11 and abs(pythia->process[6].id()) == 15) or (abs(pythia->process[5].id()) == 15 and abs(pythia->process[6].id()) == 11)) {

        pythia->process.list();

      if (OUTPUT) (void)lhaPtr->eventLHEF(false);
      }
    } // End of event loop.
  }
   
  // Termination.
  pythia->stat();
  
  if (OUTPUT) {
    (void)lhaPtr->closeLHEF();
    // Write QBH banner information to QBHfile.lhe
    qbh->trailer("QBHfile.lhe");
  }

  // Time job exectution.
  long t = clock();
  double dt = (double)t;
  if (t < 0) dt += 2.0 * (double)LONG_MAX;
  long min = (long)((dt/(double)CLOCKS_PER_SEC) / 60.0);
  long sec = (long)(dt/(double)CLOCKS_PER_SEC) % 60;
  printf("\nProcessing time %ld min %ld sec\n",min,sec);

  if (status) {
    printf("Normal sucessful completion.\n\n");
  }
  else {
    printf("Possible execution problem.\n\n");
  }
  return status;
}
/*****************************************************************************/
//EOF

