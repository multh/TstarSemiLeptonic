// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME objdISUHH2TstarSemiLeptonic_dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/TstarReconstructionHypothesis.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *TstarReconstructionHypothesis_Dictionary();
   static void TstarReconstructionHypothesis_TClassManip(TClass*);
   static void *new_TstarReconstructionHypothesis(void *p = 0);
   static void *newArray_TstarReconstructionHypothesis(Long_t size, void *p);
   static void delete_TstarReconstructionHypothesis(void *p);
   static void deleteArray_TstarReconstructionHypothesis(void *p);
   static void destruct_TstarReconstructionHypothesis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TstarReconstructionHypothesis*)
   {
      ::TstarReconstructionHypothesis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::TstarReconstructionHypothesis));
      static ::ROOT::TGenericClassInfo 
         instance("TstarReconstructionHypothesis", "include/TstarReconstructionHypothesis.h", 18,
                  typeid(::TstarReconstructionHypothesis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &TstarReconstructionHypothesis_Dictionary, isa_proxy, 4,
                  sizeof(::TstarReconstructionHypothesis) );
      instance.SetNew(&new_TstarReconstructionHypothesis);
      instance.SetNewArray(&newArray_TstarReconstructionHypothesis);
      instance.SetDelete(&delete_TstarReconstructionHypothesis);
      instance.SetDeleteArray(&deleteArray_TstarReconstructionHypothesis);
      instance.SetDestructor(&destruct_TstarReconstructionHypothesis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TstarReconstructionHypothesis*)
   {
      return GenerateInitInstanceLocal((::TstarReconstructionHypothesis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::TstarReconstructionHypothesis*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *TstarReconstructionHypothesis_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::TstarReconstructionHypothesis*)0x0)->GetClass();
      TstarReconstructionHypothesis_TClassManip(theClass);
   return theClass;
   }

   static void TstarReconstructionHypothesis_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_TstarReconstructionHypothesis(void *p) {
      return  p ? new(p) ::TstarReconstructionHypothesis : new ::TstarReconstructionHypothesis;
   }
   static void *newArray_TstarReconstructionHypothesis(Long_t nElements, void *p) {
      return p ? new(p) ::TstarReconstructionHypothesis[nElements] : new ::TstarReconstructionHypothesis[nElements];
   }
   // Wrapper around operator delete
   static void delete_TstarReconstructionHypothesis(void *p) {
      delete ((::TstarReconstructionHypothesis*)p);
   }
   static void deleteArray_TstarReconstructionHypothesis(void *p) {
      delete [] ((::TstarReconstructionHypothesis*)p);
   }
   static void destruct_TstarReconstructionHypothesis(void *p) {
      typedef ::TstarReconstructionHypothesis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TstarReconstructionHypothesis

namespace ROOT {
   static TClass *vectorlETstarReconstructionHypothesisgR_Dictionary();
   static void vectorlETstarReconstructionHypothesisgR_TClassManip(TClass*);
   static void *new_vectorlETstarReconstructionHypothesisgR(void *p = 0);
   static void *newArray_vectorlETstarReconstructionHypothesisgR(Long_t size, void *p);
   static void delete_vectorlETstarReconstructionHypothesisgR(void *p);
   static void deleteArray_vectorlETstarReconstructionHypothesisgR(void *p);
   static void destruct_vectorlETstarReconstructionHypothesisgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TstarReconstructionHypothesis>*)
   {
      vector<TstarReconstructionHypothesis> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TstarReconstructionHypothesis>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TstarReconstructionHypothesis>", -2, "vector", 214,
                  typeid(vector<TstarReconstructionHypothesis>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlETstarReconstructionHypothesisgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<TstarReconstructionHypothesis>) );
      instance.SetNew(&new_vectorlETstarReconstructionHypothesisgR);
      instance.SetNewArray(&newArray_vectorlETstarReconstructionHypothesisgR);
      instance.SetDelete(&delete_vectorlETstarReconstructionHypothesisgR);
      instance.SetDeleteArray(&deleteArray_vectorlETstarReconstructionHypothesisgR);
      instance.SetDestructor(&destruct_vectorlETstarReconstructionHypothesisgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TstarReconstructionHypothesis> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TstarReconstructionHypothesis>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETstarReconstructionHypothesisgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TstarReconstructionHypothesis>*)0x0)->GetClass();
      vectorlETstarReconstructionHypothesisgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETstarReconstructionHypothesisgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETstarReconstructionHypothesisgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TstarReconstructionHypothesis> : new vector<TstarReconstructionHypothesis>;
   }
   static void *newArray_vectorlETstarReconstructionHypothesisgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<TstarReconstructionHypothesis>[nElements] : new vector<TstarReconstructionHypothesis>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETstarReconstructionHypothesisgR(void *p) {
      delete ((vector<TstarReconstructionHypothesis>*)p);
   }
   static void deleteArray_vectorlETstarReconstructionHypothesisgR(void *p) {
      delete [] ((vector<TstarReconstructionHypothesis>*)p);
   }
   static void destruct_vectorlETstarReconstructionHypothesisgR(void *p) {
      typedef vector<TstarReconstructionHypothesis> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TstarReconstructionHypothesis>

namespace ROOT {
   static TClass *vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR_Dictionary();
   static void vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(void *p = 0);
   static void *newArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(Long_t size, void *p);
   static void delete_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(void *p);
   static void deleteArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(void *p);
   static void destruct_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >*)
   {
      vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >", -2, "vector", 214,
                  typeid(vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >) );
      instance.SetNew(&new_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR);
      instance.SetNewArray(&newArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR);
      instance.SetDelete(&delete_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR);
      instance.SetDestructor(&destruct_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >*)0x0)->GetClass();
      vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > > : new vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >;
   }
   static void *newArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >[nElements] : new vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(void *p) {
      delete ((vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >*)p);
   }
   static void deleteArray_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(void *p) {
      delete [] ((vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >*)p);
   }
   static void destruct_vectorlEROOTcLcLMathcLcLLorentzVectorlEROOTcLcLMathcLcLPtEtaPhiE4DlEDouble32_tgRsPgRsPgR(void *p) {
      typedef vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<Double32_t> > >

namespace ROOT {
   static TClass *vectorlEJetgR_Dictionary();
   static void vectorlEJetgR_TClassManip(TClass*);
   static void *new_vectorlEJetgR(void *p = 0);
   static void *newArray_vectorlEJetgR(Long_t size, void *p);
   static void delete_vectorlEJetgR(void *p);
   static void deleteArray_vectorlEJetgR(void *p);
   static void destruct_vectorlEJetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Jet>*)
   {
      vector<Jet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Jet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Jet>", -2, "vector", 214,
                  typeid(vector<Jet>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEJetgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Jet>) );
      instance.SetNew(&new_vectorlEJetgR);
      instance.SetNewArray(&newArray_vectorlEJetgR);
      instance.SetDelete(&delete_vectorlEJetgR);
      instance.SetDeleteArray(&deleteArray_vectorlEJetgR);
      instance.SetDestructor(&destruct_vectorlEJetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Jet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Jet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEJetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Jet>*)0x0)->GetClass();
      vectorlEJetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEJetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEJetgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Jet> : new vector<Jet>;
   }
   static void *newArray_vectorlEJetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<Jet>[nElements] : new vector<Jet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEJetgR(void *p) {
      delete ((vector<Jet>*)p);
   }
   static void deleteArray_vectorlEJetgR(void *p) {
      delete [] ((vector<Jet>*)p);
   }
   static void destruct_vectorlEJetgR(void *p) {
      typedef vector<Jet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Jet>

namespace ROOT {
   static TClass *maplEstringcOfloatgR_Dictionary();
   static void maplEstringcOfloatgR_TClassManip(TClass*);
   static void *new_maplEstringcOfloatgR(void *p = 0);
   static void *newArray_maplEstringcOfloatgR(Long_t size, void *p);
   static void delete_maplEstringcOfloatgR(void *p);
   static void deleteArray_maplEstringcOfloatgR(void *p);
   static void destruct_maplEstringcOfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,float>*)
   {
      map<string,float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,float>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,float>", -2, "map", 96,
                  typeid(map<string,float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,float>) );
      instance.SetNew(&new_maplEstringcOfloatgR);
      instance.SetNewArray(&newArray_maplEstringcOfloatgR);
      instance.SetDelete(&delete_maplEstringcOfloatgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOfloatgR);
      instance.SetDestructor(&destruct_maplEstringcOfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,float>*)0x0)->GetClass();
      maplEstringcOfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,float> : new map<string,float>;
   }
   static void *newArray_maplEstringcOfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,float>[nElements] : new map<string,float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOfloatgR(void *p) {
      delete ((map<string,float>*)p);
   }
   static void deleteArray_maplEstringcOfloatgR(void *p) {
      delete [] ((map<string,float>*)p);
   }
   static void destruct_maplEstringcOfloatgR(void *p) {
      typedef map<string,float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,float>

namespace {
  void TriggerDictionaryInitialization_SUHH2TstarSemiLeptonic_dict_Impl() {
    static const char* headers[] = {
"include/TstarReconstructionHypothesis.h",
0
    };
    static const char* includePaths[] = {
"/nfs/dust/cms/user/multh/SFrame_9_2_4",
"/nfs/dust/cms/user/multh/CMSSW_9_2_4/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc530/lcg/root/6.08.07/include",
"/nfs/dust/cms/user/multh/CMSSW_9_2_4/src/UHH2/TstarSemiLeptonic/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "SUHH2TstarSemiLeptonic_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$include/TstarReconstructionHypothesis.h")))  TstarReconstructionHypothesis;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "SUHH2TstarSemiLeptonic_dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/TstarReconstructionHypothesis.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"TstarReconstructionHypothesis", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("SUHH2TstarSemiLeptonic_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_SUHH2TstarSemiLeptonic_dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_SUHH2TstarSemiLeptonic_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_SUHH2TstarSemiLeptonic_dict() {
  TriggerDictionaryInitialization_SUHH2TstarSemiLeptonic_dict_Impl();
}
