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
#include <TMath.h>
#include <TChain.h>
#include <TFile.h>

#include "inTuple.h"


class outTuple {
  public:
    TTree       *_tree;
    Int_t       treeNum;

    //current variables - make this into a class later
    //datatype
    unsigned int     value;

    //branch
    TBranch     b_value;

    //new variables
    float  newvar;

    //new branch
    TBranch b_newvar;

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
  //_tree->SetMakeClass(1);

  //current variables
  _tree->Branch("value",&value,"value/I");

  //new variables
  _tree->Branch("newvar",&newvar,"newvar/F");

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
  std::cout<<" event number "<<iTuple->event<<std::endl;
  newvar =  3.1415926534 * (value);

  //newvar = value;

  _tree->Fill();

}

#endif
