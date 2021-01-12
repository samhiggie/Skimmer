////////////////////////////////////////////////////////////////////
/*
/ Author: Sam Higginbotham
/ Date: January 12,2021
/ Purpose: container for light, fast c++ skimming code
/
////////////////////////////////////////////////////////////////////*/
#ifndef inTuple_h
#define inTuple_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>


class inTuple{
  public:
    TTree       *_tree;
    Int_t       treeNum;

    Float_t     *event;
    TBranch     *b_event;


    // function methods and inheritance
    inTuple (TTree* tree);
    ~inTuple();

    void Init(TTree* tree);
    Int_t GetEntry(int entry);
    Long64_t GetEntries();
    TTree* GetTree();
    //other containers
};

//constructors
inTuple::inTuple(TTree* tree){
  Init(tree);
}
inTuple::~inTuple(){}

// Functions


void inTuple::Init(TTree* tree){

  _tree = tree;
  _tree->SetMakeClass(1);
  _tree->SetBranchAddress("event",&event,&b_event);
}

Int_t inTuple::GetEntry(int entry)
{
    return _tree->GetEntry(entry);
}

Long64_t inTuple::GetEntries()
{
    return _tree->GetEntries();
}

TTree* inTuple::GetTree()
{
    return _tree;
}


#endif
