#ifndef DIGITASKSND_H_
#define DIGITASKSND_H_

#include <Rtypes.h>             // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>         // for Double_t, Int_t, Option_t
#include <TClonesArray.h> 
#include "FairTask.h"           // for FairTask, InitStatus
#include "FairMCEventHeader.h"  // for FairMCEventHeader
#include "Scifi.h"              // for Scifi detector
#include "SNDLHCEventHeader.h"  // for EventHeader
class TBuffer;
class TClass;
class TClonesArray;
class TMemberInspector;

class DigiTaskSND : public FairTask
{
  public:
    /** Default constructor **/
    DigiTaskSND();

    /** Destructor **/
    ~DigiTaskSND();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);
    
    /** Set flag for Scifi cluster making  **/
    void withScifiClusters(bool flag){ fMakeClusterScifi = flag; }

    /** Set flag to copy emulsion points to output file **/
    void set_copy_emulsion_points(bool flag) { fCopyEmulsionPoints = flag; }

  private:
    void digitizeMuFilter();
    void digitizeScifi();
    void clusterScifi();

    Scifi* scifi;
    std::map<Int_t, std::map<Int_t, std::array<float, 2>>> fibresSiPM;
    std::map<Int_t, std::map<Int_t,std:: array<float, 2>>> siPMFibres;

    // Input
    FairMCEventHeader* fMCEventHeader;
    TClonesArray* fMuFilterPointArray; // MC points
    TClonesArray* fScifiPointArray;
    TClonesArray* fScifiClusterArray;
    // Output
    SNDLHCEventHeader* fEventHeader;
    TClonesArray* fMuFilterDigiHitArray; // hit class (digitized!)
    TClonesArray* fScifiDigiHitArray;
    TClonesArray* fMuFilterHit2MCPointsArray; // link to MC truth
    TClonesArray* fScifiHit2MCPointsArray;
    TClonesArray* fvetoPointArray;
    TClonesArray* fEmulsionPointArray;
    TClonesArray* fMCTrackArray;

    /** Flags **/
    bool fMakeClusterScifi;
    bool fCopyEmulsionPoints;

    DigiTaskSND(const DigiTaskSND&);
    DigiTaskSND& operator=(const DigiTaskSND&);

    ClassDef(DigiTaskSND, 6);
};

#endif /* DIGITASKSND_H_ */
