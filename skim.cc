#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <map>
#include <string>
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TMath.h"
#include "TSystem.h"
#include "TRandom.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include "outTuple.h"
#include "inTuple.h"

#include "time.h"

int main(int argc, char** argv) {
  
  //namespaces
  using namespace std;
  using namespace ROOT; // is this a good idea?


  string in = *(argv+1);  // argv starts at 1 remember :)
  TFile* fileIn = TFile::Open(in.c_str(),"READ");
  std::cout<<"file in "<<fileIn->GetName()<<std::endl;

  string out = *(argv+2);  // argv starts at 1 remember :)
  TFile* fileOut = TFile::Open(out.c_str(),"RECREATE");

  //input tree
  TTree * inTree = (TTree*) fileIn->Get("Events");
  inTuple* intuple = new inTuple(inTree);

  //outtuple
  TTree *tree = new TTree("ntuple","data");
  outTuple* otuple = new outTuple(tree);
  fileOut->cd();

  //event loop
  for (int ent = 0;ent<inTree->GetEntries();ent++){

    float idkNumber=1.0;
    if(ent%1000==0){
      //fprintf(stdout,"\r Processed events: %8d ",ent);
      std::cout<<"processed events: "<<ent<<std::endl;
    }

    otuple->fill(intuple,ent);
  }

  otuple->write(fileOut);//check header for this

  fileOut->Close();
  return 0;
}
