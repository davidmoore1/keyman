(function() {
'use strict';
var definitions = {
  defaults: {
    version: "1.0.0",
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
    searchTermToKey: function defaultCasedSearchTermToKey(wordform, applyCasing) {
    // While this is a bit WET, as the basic `defaultSearchTermToKey` exists and performs some of
    // the same functions, repetition is the easiest way to allow the function to be safely compiled
    // with ease by use of `.toString()`.
    return Array.from(wordform
        .normalize('NFKD')
        // Remove any combining diacritics (if input is in NFKD)
        .replace(/[\u0300-\u036F]/g, '')) // end of `Array.from`
        .map(function (c) { return applyCasing('lower', c); })
        .join('');
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