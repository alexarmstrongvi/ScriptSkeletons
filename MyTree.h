////////////////////////////////////////////////////////////////////////////////
/// Copyright (c) <TODO: year> by Alex Armstrong
///
/// @file MyTree.h
/// @author Alex Armstrong <alarmstr@cern.ch>
/// @date <TODO: 1 Jan 1111>
/// @brief <TODO: file description>
///
/// This is a TTree with all branches and adminstrative work contained in a
/// single file. After defining the TTree branches as desired, implementation
/// is as easy as 
/// 1)  MyTree my_tree("MyTreeName","MyTreeTitle");
/// 2)  my_tree.initialize();
/// 3a) my_tree.var_branch = var;
/// 3b) my_tree.vec_branch.push_back(vec_element);
/// 4)  my_tree.clear();
////////////////////////////////////////////////////////////////////////////////

#include <TTree.h>
#include <vector>

using std::vector;

class MyTree : public TTree
{
public:
  // Constructor
  MyTree(const char* name, const char* title)
    : TTree(name, title) {}

  //////////////////////////////////////////////////////////////////////////////
  // Define variables for branches
  unsigned int runNumber = 0; ///< Run number for the current event
  unsigned long long eventNumber = 0; ///< Event number
  /// Jet 4-momentum variables
  vector<float> *jetEta = nullptr;
  vector<float> *jetPhi = nullptr;
  vector<float> *jetPt = nullptr;
  vector<float> *jetE = nullptr;

  //////////////////////////////////////////////////////////////////////////////
  // Assignment operator (if needed)
  MyTree& operator=(const MyTree& rhs) {
    this->runNumber = rhs.runNumber;
    this->eventNumber = rhs.eventNumber;
    *this->jetEta = *rhs.jetEta; // Copy object not pointer
    *this->jetPhi = *rhs.jetPhi;
    *this->jetPt = *rhs.jetPt;
    *this->jetE = *rhs.jetE;
    return *this;
  }

  //////////////////////////////////////////////////////////////////////////////
  // Attach variables to branches
  void initialize() {
    this->Branch ("RunNumber", &runNumber);
    this->Branch ("EventNumber", &eventNumber);
    jetEta = new vector<float>();
    this->Branch ("JetEta", &jetEta);
    jetPhi = new vector<float>();
    this->Branch ("JetPhi", &jetPhi);
    jetPt = new vector<float>();
    this->Branch ("JetPt", &jetPt);
    jetE = new vector<float>();
    this->Branch ("JetE", &jetE);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Clear
  void clear() {
    jetEta->clear();
    jetPhi->clear();
    jetPt->clear();
    jetE->clear();
  }

  //////////////////////////////////////////////////////////////////////////////
  // Destructor
  ~MyTree() {
    delete jetEta;
    delete jetPhi;
    delete jetPt;
    delete jetE;
  }

};
