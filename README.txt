T* Semileptonic analysis

23Sep2016 Setup to analyse 2016 data 

1) Module to study GenParticles and there kinematic distributions

2) Preselection Module: First selection to reject background events and enrich signal events
   			
			Selections:
			Luminosity selections (Data only);
  			Common Modules: (For more details see UHH2/common/include/CommonModules.h)
                               MCPileupReweight (MC only);
                               JetCorrector (Summer16_23Sep2016_AK4PFchs);
                               JER;
                               MET filters (https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2);
                               good PV;
                               JetLepton Cleaning;
                               ID cleaner for: Muons(Tight ID, pT>53 GeV);
                               	  	       Electrons(Spring16 Tight ID, pT>50 GeV);
                               		       Jets(WP_LOOSE, pT>30 GeV));
  
			TopJetCorrector (Summer16_23Sep2016_AK8PFchs);
                	TopJetLeptonCleaner (0.8) ;
  			TopJetCleaner (PtEtaCut(200., 2.4), Type2TopTag(105,220,Type2TopTag::MassType::groomed), Tau32());
 
			Lepton selection:
  			Muon channel:     exactly one muon (Tight ID, pT>53 GeV)
			Electron channel: exactly one electron (Spring16 Tight ID, pT>50 GeV)
 			
			Jet selection:
				at least 4 jets (WP_LOOSE, pT>50 GeV) 


