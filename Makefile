LIBRARY := SUHH2TstarSemiLeptonic
USERLDFLAGS := -lSUHH2core -lSUHH2common -lGenVector -lMinuit
DICT := include/TstarReconstructionHypothesis.h include/SUHH2tstar_LinkDef.h
# enable par creation; this is necessary for all packages containing AnalysisModules
# to be loaded from by AnalysisModuleRunner.
PAR := 1
include ../Makefile.common
