#pragma once  // _S2


//#include "../../../../developer/kmcompx/include/kmcompx.h"        // added S

#include "../../../../developer/kmcompx/include/pch.h"            // added S
//#include "pch.h"                                                // removed S

//#include "../../../../developer/kmcompx/include/compfile.h"       // added S
//#include <compfile.h>                                           // removed S

//#include "../../../../developer/kmcompx/include/compiler.h"       // added S
//#include <compiler.h>                                           // removed S

#include "../../../../developer/kmcompx/include/comperr.h"        // added S
//#include <comperr.h>                                            // removed S

//#include "../../../../developer/kmcompx/include/vkeys.h"          // added S
//#include <vkeys.h>                                              // removed S

#include "../../../../developer/kmcompx/include/kmcmpdll.h"       // added S
//#include <kmcmpdll.h>                                           // removed S

#include "../../../../developer/kmcompx/include/CharToKeyConversion.h"      // added S
//#include "CharToKeyConversion.h"                                          // removed S

#include "../../../../developer/kmcompx/include/kmx_u16.h"

extern KMX_BOOL FMnemonicLayout; // TODO: these globals should be consolidated one day

KMX_DWORD ExpandCapsRule(PFILE_GROUP gp, PFILE_KEY kpp, PFILE_STORE sp);

KMX_DWORD VerifyCasedKeys(PFILE_STORE sp) {
  assert(sp != NULL);

  if (FMnemonicLayout) {
    // The &CasedKeys system store is not supported for
    // mnemonic layouts in 14.0
    return CERR_CasedKeysNotSupportedWithMnemonicLayout;
  }

  // We will rewrite this store with virtual keys

  PKMX_WCHAR p = sp->dpString;
  
  //PKMX_WSTR buf = new KMX_WCHAR[std::u16string(p).length() * 5 + 1];  // extended keys are 5 units long, so this is the max length
  PKMX_WCHAR buf = new KMX_WCHAR[u16len(p) * 5 + 1];  // extended keys are 5 units long, so this is the max length
  PKMX_WCHAR q = buf;

  while (*p) {
    KMX_UINT key = 0, shift = 0;
    if (*p != UC_SENTINEL) {
      if (!MapUSCharToVK(*p, &key, &shift)) {
        return CERR_CasedKeysMustContainOnlyVirtualKeys;
      }
      if (shift & K_SHIFTFLAG) {
        return CERR_CasedKeysMustNotIncludeShiftStates;
      }
    }
    else {
      if (*(p + 1) != CODE_EXTENDED) {
        return CERR_CasedKeysMustContainOnlyVirtualKeys;
      }
      shift = *(p + 2);
      key = *(p + 3);
      if (shift != ISVIRTUALKEY) {
        return CERR_CasedKeysMustNotIncludeShiftStates;
      }
    }
    *q++ = UC_SENTINEL;
    *q++ = CODE_EXTENDED;
    *q++ = shift;
    *q++ = key;
    *q++ = UC_SENTINEL_EXTENDEDEND;
    *q = 0;

    p = incxstr(p);
  }

  delete[] sp->dpString;
  sp->dpString = buf;

  return CERR_None;
}

KMX_DWORD ExpandCapsRulesForGroup(PFILE_KEYBOARD fk, PFILE_GROUP gp) {
  assert(fk != NULL);
  assert(gp != NULL);

  if (FMnemonicLayout) {
    // The &CasedKeys system store is not supported for
    // mnemonic layouts in 14.0
    return CERR_None;
  }

  PFILE_STORE sp = FindSystemStore(fk, TSS_CASEDKEYS);
  if (!sp) {
    // If there is no &CasedKeys system store, then we do not
    // process the key
    return CERR_None;
  }

  KMX_DWORD msg;
  // ExpandCapsRule may add extra rules at the end of gp->dpKeyArray,
  // reallocating it, so we (a) cache the original length, and (b)
  // dereference the array every call
  int cxKeyArray = gp->cxKeyArray;
  for (int i = 0; i < cxKeyArray; i++) {
    if ((msg = ExpandCapsRule(gp, &gp->dpKeyArray[i], sp)) != CERR_None) {
      return msg;
    }
  }  
  return CERR_None; 
}

KMX_DWORD ExpandCapsRule(PFILE_GROUP gp, PFILE_KEY kpp, PFILE_STORE sp) {
  KMX_UINT key = kpp->Key;
  KMX_UINT shift = kpp->ShiftFlags;

  if (shift == 0) {
    // Convert US key cap to a virtual key
    if (!MapUSCharToVK(kpp->Key, &key, &shift)) {
      return CERR_None;
    }
  }

  if (shift & (CAPITALFLAG | NOTCAPITALFLAG)) {
    // Don't attempt expansion if either Caps Lock flag is specified in the key rule
    return CERR_None;
  }

  PKMX_WCHAR p = sp->dpString;
  for (; *p; p = incxstr(p)) {
    // We've already verified that the store contains only virtual keys in VerifyCasedKeys
    if (*(p + 3) == key) {
      break;
    }
  }
 
  if (!*p) {
    // This key is not modified by Caps Lock
    return CERR_None;
  }

  // This key is modified by Caps Lock, so we need to duplicate this rule
  PFILE_KEY k = new FILE_KEY[gp->cxKeyArray + 1];
  if (!k) return CERR_CannotAllocateMemory;
  memcpy(k, gp->dpKeyArray, gp->cxKeyArray * sizeof(FILE_KEY));

  kpp = &k[(INT_PKMX)(kpp - gp->dpKeyArray)];

  delete gp->dpKeyArray;
  gp->dpKeyArray = k;
  gp->cxKeyArray++;

  k = &k[gp->cxKeyArray - 1];
  
  k->dpContext = new KMX_WCHAR[u16len(kpp->dpContext) + 1];
  k->dpOutput  = new KMX_WCHAR[u16len(kpp->dpOutput) + 1];
  
  // copy the output.
  u16cpy(k->dpContext, kpp->dpContext );
  u16cpy(k->dpOutput, kpp->dpOutput );
  
  k->Key = key;
  k->Line = kpp->Line;
  // Add the CAPITAL FLAG, invert shift flag for the rule
  k->ShiftFlags = shift ^ K_SHIFTFLAG | CAPITALFLAG;
  kpp->Key = key;
  kpp->ShiftFlags = shift | NOTCAPITALFLAG;

  return CERR_None;
}



//***old **************************************************************************************************
//KMX_DWORD ExpandCapsRule(PFILE_GROUP gp, PFILE_KEY kpp, PFILE_STORE sp);

/*KMX_DWORD VerifyCasedKeys(PFILE_STORE sp) {
  assert(sp != NULL);

  if (FMnemonicLayout) {
    // The &CasedKeys system store is not supported for
    // mnemonic layouts in 14.0
    return CERR_CasedKeysNotSupportedWithMnemonicLayout;
  }

  // We will rewrite this store with virtual keys

  PWSTR p = sp->dpString;
  PWSTR buf = new WCHAR[wcslen(p) * 5 + 1];  // extended keys are 5 units long, so this is the max length
  PWSTR q = buf;

  while (*p) {
    KMX_UINT key = 0, shift = 0;
    if (*p != UC_SENTINEL) {
      if (!MapUSCharToVK(*p, &key, &shift)) {
        return CERR_CasedKeysMustContainOnlyVirtualKeys;
      }
      if (shift & K_SHIFTFLAG) {
        return CERR_CasedKeysMustNotIncludeShiftStates;
      }
    }
    else {
      if (*(p + 1) != CODE_EXTENDED) {
        return CERR_CasedKeysMustContainOnlyVirtualKeys;
      }
      shift = *(p + 2);
      key = *(p + 3);
      if (shift != ISVIRTUALKEY) {
        return CERR_CasedKeysMustNotIncludeShiftStates;
      }
    }
    *q++ = UC_SENTINEL;
    *q++ = CODE_EXTENDED;
    *q++ = shift;
    *q++ = key;
    *q++ = UC_SENTINEL_EXTENDEDEND;
    *q = 0;

    p = incxstr(p);
  }

  delete[] sp->dpString;
  sp->dpString = buf;

  return CERR_None;
}*/

/*KMX_DWORD ExpandCapsRulesForGroup(PFILE_KEYBOARD fk, PFILE_GROUP gp) {
  assert(fk != NULL);
  assert(gp != NULL);

  if (FMnemonicLayout) {
    // The &CasedKeys system store is not supported for
    // mnemonic layouts in 14.0
    return CERR_None;
  }

  PFILE_STORE sp = FindSystemStore(fk, TSS_CASEDKEYS);
  if (!sp) {
    // If there is no &CasedKeys system store, then we do not
    // process the key
    return CERR_None;
  }

  KMX_DWORD msg;
  // ExpandCapsRule may add extra rules at the end of gp->dpKeyArray,
  // reallocating it, so we (a) cache the original length, and (b)
  // dereference the array every call
  int cxKeyArray = gp->cxKeyArray;
  for (int i = 0; i < cxKeyArray; i++) {
    if ((msg = ExpandCapsRule(gp, &gp->dpKeyArray[i], sp)) != CERR_None) {
      return msg;
    }
  }
  return CERR_None;
}
*/

/*KMX_DWORD ExpandCapsRule(PFILE_GROUP gp, PFILE_KEY kpp, PFILE_STORE sp) {
  KMX_UINT key = kpp->Key;
  KMX_UINT shift = kpp->ShiftFlags;

  if (shift == 0) {
    // Convert US key cap to a virtual key
    if (!MapUSCharToVK(kpp->Key, &key, &shift)) {
      return CERR_None;
    }
  }

  if (shift & (CAPITALFLAG | NOTCAPITALFLAG)) {
    // Don't attempt expansion if either Caps Lock flag is specified in the key rule
    return CERR_None;
  }

  PWSTR p = sp->dpString;
  for (; *p; p = incxstr(p)) {
    // We've already verified that the store contains only virtual keys in VerifyCasedKeys
    if (*(p + 3) == key) {
      break;
    }
  }

  if (!*p) {
    // This key is not modified by Caps Lock
    return CERR_None;
  }

  // This key is modified by Caps Lock, so we need to duplicate this rule
  PFILE_KEY k = new FILE_KEY[gp->cxKeyArray + 1];
  if (!k) return CERR_CannotAllocateMemory;
  memcpy(k, gp->dpKeyArray, gp->cxKeyArray * sizeof(FILE_KEY));

  kpp = &k[(INT_PTR)(kpp - gp->dpKeyArray)];

  delete gp->dpKeyArray;
  gp->dpKeyArray = k;
  gp->cxKeyArray++;

  k = &k[gp->cxKeyArray - 1];
  
  k->dpContext = new WCHAR[wcslen(kpp->dpContext) + 1];
  k->dpOutput = new WCHAR[wcslen(kpp->dpOutput) + 1];
  wcscpy_s(k->dpContext, wcslen(kpp->dpContext) + 1, kpp->dpContext);	// copy the context.
  wcscpy_s(k->dpOutput, wcslen(kpp->dpOutput) + 1, kpp->dpOutput);		// copy the output.
  k->Key = key;
  k->Line = kpp->Line;
  // Add the CAPITAL FLAG, invert shift flag for the rule
  k->ShiftFlags = shift ^ K_SHIFTFLAG | CAPITALFLAG;
  kpp->Key = key;
  kpp->ShiftFlags = shift | NOTCAPITALFLAG;

  return CERR_None;
}

*/
