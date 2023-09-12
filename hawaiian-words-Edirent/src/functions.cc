#include "functions.hpp"

#include <iostream>

/**
 * TODO: Implement this function
 * @param word word to change to lowercase
 * @return result of changing every character in word to lowercase
 */
std::string StringToLower(const std::string& word) {
  std::string result;
  for (char c : word) {
    result.push_back(static_cast<char>(std::tolower(c)));
  }
  return result;
}

/**
 * TODO: Implement this function
 * @param v1 first character in potential vowel group
 * @param v2 second character in potential vowel group
 * @return true if v1 and v2 form a valid vowel group
 */
bool IsVowelGroup(const char& v1, const char& v2) {
  std::string group = {v1, v2};
  return group == "ai" || group == "ae" || group == "ao" || group == "au" ||
         group == "ei" || group == "eu" || group == "iu" || group == "oi" ||
         group == "ou" || group == "ui";
}

/**
 * TODO: Complete this function
 * @param v potential vowel character
 * @return true if v is a vowel
 */
bool IsVowel(const char& v) {
  return v == 'a' || v == 'e' || v == 'i' || v == 'o' || v == 'u';
}

/**
 * TODO: Complete this function
 * @param c potential consonant character
 * @return true if c is a consonant
 */
bool IsConsonant(const char& c) {
  return c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n' ||
         c == 'w';
}
/**
 * TODO: Implement this function
 * @param c character to check validity of
 * @return true if input c is a valid character in the Hawaiian language, false
 * otherwise
 */
bool IsValidCharacter(const char& c) {
  return IsVowel(c) || IsConsonant(c) || c == ' ' || c == '\'';
}

/**
 * TODO: Implement this function
 * @param word word to check validity of
 * @return true if every character in word is a valid character in the Hawaiian
 * language, false otherwise
 */
bool IsValidWord(const std::string& word) {
  for (char c : word) {
    if (!IsValidCharacter(c)) {
      return false;
    }
  }
  return true;
}

/**
 * TODO: Implement this function
 * @param c consonant to get pronunciation of
 * @param prev character before c, used for determining w translation
 *    set to null character as default if no value is passed in
 * @return pronunciation of the consonant c as a string
 */
char ConsonantPronunciation(const char& c, const char& prev) {
  std::cout << "Input to ConsonantPronunciation() : \"" << c << "\" \"" << prev
            << "\"" << std::endl;

  if (c == 'w') {
    if (prev == 'i' || prev == 'e') {
      return 'v';
    } else
      return 'w';

  } else if (c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' ||
             c == 'n') {
    return c;
  } else {
    return '\0';
  }
}

/**
 * TODO: Implement this function
 * @param v1 first vowel in a vowel grouping
 * @param v2 second vowel in a vowel grouping
 * @return the pronunciation of the vowel grouping made up of v1 and v2
 * as a string
 */
std::string VowelGroupPronunciation(const char& v1, const char& v2) {
  std::cout << "Input to VowelGroupPronunciation() : \"" << v1 << "\" \"" << v2
            << "\"" << std::endl;
  std::string group = {v1, v2};
  if (group == "ai" || group == "ae") {
    return "eye";
  } else if (group == "ao" || group == "au" || group == "ou") {
    return "ow";
  } else if (group == "ei") {
    return "ay";
  } else if (group == "eu") {
    return "eh-oo";
  } else if (group == "iu") {
    return "ew";
  } else if (group == "oi") {
    return "oy";
  } else if (group == "ui") {
    return "ooey";
  } else {
    return "";
  }
}


/**
 * TODO: Implement this function
 * @param v single vowel to get pronunciation of
 * @return the pronunciation of v as a string
 */
std::string SingleVowelPronunciation(const char& v) {
  std::cout << "Input to SingleVowelPronunciation() : \"" << v << "\""
            << std::endl;
  if (v == 'a') {
    return "ah";
  } else if (v == 'e') {
    return "eh";
  } else if (v == 'i') {
    return "ee";
  } else if (v == 'o') {
    return "oh";
  } else if (v == 'u') {
    return "oo";
  } else {
    return "";  // This should not happen if the function is called correctly
  }
}

/**
 * TODO: Implement this function
 * @param prev first character in set of three passed to function
 * @param curr second character in set of three passed to function
 * @param next third character in set of three passed to function
 * @return pronunciation of curr using next and prev as needed to determine
 * result
 */
std::string ProcessCharacter(const char& prev,
                             const char& curr,
                             const char& next) {
  std::string result;
  if (!IsValidCharacter(curr)) {
    throw std::invalid_argument("Invalid character encountered");
  }
  if (IsConsonant(curr)) {
    result += ConsonantPronunciation(curr, prev);
    return result;
    result.clear();
  }
  if (IsVowel(curr)) {
    if (IsVowel(next) && IsVowelGroup(curr, next)) {
      return VowelGroupPronunciation(curr, next);
    } else {
      return SingleVowelPronunciation(curr);
    }
  }
  if (curr == ' ' || curr == '\'') {
    result += curr;
    return result;
    result.clear();
  }
  return "";
}

/**
 * TODO: Implement this function
 * @param word string to get pronunciation of
 * @return pronunciation of word
 */
std::string Pronunciation(const std::string& word) {
  std::cout << "Input to Pronunciation() : " << word << std::endl;
  std::string result;
  for (size_t i = 0; i < word.size(); ++i) {
    char prev = (i > 0) ? word[i - 1] : '\0';
    char curr = word[i];
    char next = (i < word.size() - 1) ? word[i + 1] : '\0';
    std::string processed_char = ProcessCharacter(prev, curr, next);
    if (!processed_char.empty() && processed_char != " " &&
        processed_char != "'" && i < word.size() - 1 && word[i + 1] != ' ' &&
        word[i + 1] != '\'' && (IsVowel(curr)|| IsVowelGroup(prev, curr))) {
      processed_char += '-';
    }
    std::cout << processed_char << std::endl;
    result += processed_char;
    if (IsVowelGroup(curr, next)) {
      i = i + 1;
    }
  }
  if (!result.empty() && result.back() == '-') {
    result.pop_back();
  }
  return result;
}
/**
 * TODO: Implement this function
 * @param hawaiian_word word to get pronunciation of
 * @return the pronunciation of hawaiian_word as a string if valid
 *  and throws an invalid_argument error if not valid
 */
std::string GetPronunciation(const std::string& hawaiian_word) {
    std::cout << "Input to GetPronunciation() : " << hawaiian_word << std::endl;
    std::string lowercase_word = StringToLower(hawaiian_word);
    if (!IsValidWord(lowercase_word)) {
      throw std::invalid_argument("Invalid Hawaiian word");
    }
    return Pronunciation(lowercase_word);
  }