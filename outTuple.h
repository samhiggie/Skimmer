////////////////////////////////////////////////////////////////////
/*
/ Author: Sam Higginbotham
/ Date: January 12,2021
/ Purpose: container for light, fast c++ skimming code
/
////////////////////////////////////////////////////////////////////*/
#ifndef outTuple_h
#define outTuple_h


#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "inTuple.h"


class outTuple {
  public:
    TTree       *_tree;
    Int_t       treeNum;

    Float_t     *value;
    TBranch     *b_value;


    // function methods and inheritance
    outTuple (TTree* tree);

    ~outTuple();

    void Init(TTree* tree);
    Int_t GetEntry(int entry);
    Long64_t GetEntries();
    TTree* GetTree();
    void write(TFile* tfile);
    void fill(inTuple* iTuple, int entry);
    //other containers
};

//constructors
outTuple::outTuple(TTree* tree){
  Init(tree);
}
outTuple::~outTuple(){}

// Functions

void outTuple::Init(TTree* tree){
  _tree = tree;
  _tree->SetMakeClass(1);

  _tree->Branch("value",&value,"value/I");
}

Int_t outTuple::GetEntry(int entry)
{
    return _tree->GetEntry(entry);
}

Long64_t outTuple::GetEntries()
{
    return _tree->GetEntries();
}

TTree* outTuple::GetTree()
{
    return _tree;
}

void outTuple::write(TFile* tfile){
  tfile->cd();
  _tree->Write();

}
void outTuple::fill(inTuple* iTuple, int entry){
  iTuple->GetEntry(entry);
  value = iTuple->event;

  _tree->Fill();

}

#endif
