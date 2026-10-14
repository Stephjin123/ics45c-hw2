#ifndef WORD_COUNT_HPP
#define WORD_COUNT_HPP

#include <iosfwd>
#include <map>
#include <set>
#include <string>

// lowercases str in place
void to_lowercase(std::string& str);

// reads the stop words from the stream, lowercased
std::set<std::string> load_stopwords(std::istream& stopwords);

// counts the words of the document, lowercased, skipping the stop words
std::map<std::string, int> count_words(std::istream& document,
                                       const std::set<std::string>& stopwords);

// writes "<word> <count>" per line, in ascending order by word
void output_word_counts(const std::map<std::string, int>& word_counts,
                        std::ostream& output);

#endif  // End of the include guard.
