int External() {
  std::string path{"o2sim_Kine.root"};

  TFile file(path.c_str(), "READ");
  if (file.IsZombie()) {
    std::cerr << "Cannot open ROOT file " << path << "\n";
    return 1;
  }

  auto tree = (TTree *)file.Get("o2sim");
  if (!tree) {
    std::cerr << "Cannot find tree o2sim in file " << path << "\n";
    return 1;
  }
  std::vector<o2::MCTrack> *tracks{};
  tree->SetBranchAddress("MCTrack", &tracks);

  auto nK0 = tree->Scan("MCTrack.GetPdgCode()", "TMath::Abs(MCTrack.GetPdgCode()) == 310");
  auto nLambda = tree->Scan("MCTrack.GetPdgCode()", "TMath::Abs(MCTrack.GetPdgCode()) == 3122");
  auto nXi = tree->Scan("MCTrack.GetPdgCode()", "TMath::Abs(MCTrack.GetPdgCode()) == 3312");
  auto nOmega = tree->Scan("MCTrack.GetPdgCode()", "TMath::Abs(MCTrack.GetPdgCode()) == 3334");
  auto nStr = nK0+nLambda+nXi+nOmega;
    
  if (nStr == 0) {
    std::cerr << "No event of interest\n";
    return 1;
  }
  return 0;
}
