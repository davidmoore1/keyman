(function() {
  'use strict';
  var definitions = {
    defaults: {
      version: "16.0.138",
      applyCasing: function defaultApplyCasing(casing, text) {
      switch (casing) {
          case 'lower':
              return text.toLowerCase();
          case 'upper':
              return text.toUpperCase();
          case 'initial':
              var headCode = text.charCodeAt(0);
              // The length of the first code unit, as measured in code points.
              var headUnitLength = 1;
              // Is the first character a high surrogate, indicating possible use of UTF-16
              // surrogate pairs?  Also, is the string long enough for there to BE a pair?
              if (text.length > 1 && headCode >= 0xD800 && headCode <= 0xDBFF) {
                  // It's possible, so now we check for low surrogates.
                  var lowSurrogateCode = text.charCodeAt(1);
                  if (lowSurrogateCode >= 0xDC00 && lowSurrogateCode <= 0xDFFF) {
                      // We have a surrogate pair; this pair is the 'first' character.
                      headUnitLength++;
                  }
              }
              // Capitalizes the first code unit of the string, leaving the rest intact.
              return text.substring(0, headUnitLength).toUpperCase() // head - uppercased
                  .concat(text.substring(headUnitLength)); // tail - lowercased
      }
  }
    },  model: {
      searchTermToKey: function (wordform, applyCasing) {
          // Refer to ${KEYMAN_ROOT}/developer/src/kmc-model/src/model-defaults.ts for
          // the original version.
          return Array.from(wordform
              .normalize('NFKD')
              // Remove any combining diacritics (if input is in NFKD)
              .replace(/[\u0300-\u036F]/g, '')) // end of `Array.from`
              .map(function (c) { return applyCasing('lower', c); })
              .join('')
              // Strip out all apostrophes and quotation marks; they are not distinct letters in English.
              // Is of particular relevance for apostrophes due to English contractions; lazy typers
              // often expect the apostrophe to be "filled in".
              .replace(/['"‘’“”]/g, '');
      }
    },
    applyCasing: function(caseToApply, text) {
          return definitions.defaults.applyCasing(caseToApply, text);
        },
    searchTermToKey: function(text) {
        return definitions.model.searchTermToKey(text, definitions.applyCasing);
      }
  };
    wordBreaker: wordBreakers['default'],
    searchTermToKey: definitions.searchTermToKey,
    languageUsesCasing: true,
    applyCasing: definitions.applyCasing,
  }));
  })();