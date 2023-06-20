/*
	OrderChecker.cpp
	Very simple class designed to test whether or not a root file is time ordered.
	Meant to be used with newly converted from binary data. Only for development.

	Written by G.W. McCann Oct. 2020
*/
#include "OrderChecker.h"

namespace EventBuilder {

	OrderChecker::OrderChecker() {}
	
	OrderChecker::~OrderChecker() {}
	
	bool OrderChecker::IsOrdered(const std::string& filename) 
	{
		TFile* file = TFile::Open(filename.c_str(), "READ");
		TTree* tree = (TTree*) file->Get("Data");
	
		uint64_t ts;
		tree->SetBranchAddress("Timestamp", &ts);
		uint64_t prevStamp = 0;
	
		for(int64_t i=0; i<tree->GetEntries(); i++)
		{
			tree->GetEntry(i);
			if(prevStamp >= ts)
			{
				std::cerr<<"Bad order at entry "<<i<<" out of "<<tree->GetEntries()<<std::endl;
				return false;
			}
		}
	
		file->Close();
		return true;
	}

}