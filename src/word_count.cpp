#include "word_count.hpp"
#include <cctype>
#include <iostream>
using namespace std;

// char& so we change the real characters, not copies
void to_lowercase(string& str) {
    for (char& c : str) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
}

// >> skips spaces, tabs and newlines; set ignores duplicates
set<string> load_stopwords(istream& stopwords) {
    set<string> result;
    string word;
    while (stopwords >> word) {
        to_lowercase(word);
        result.insert(word);
    }
    return result;
}

// lowercase FIRST, then check the stop word set
map<string, int> count_words(istream& document, const set<string>& stopwords) {
    map<string, int> counts;
    string word;
    while (document >> word) {
        to_lowercase(word);
        if (stopwords.count(word) == 0) {
            ++counts[word];   // a new key starts at 0
        }
    }
    return counts;
}

// map iterates in ascending key order, so no sorting needed
void output_word_counts(const map<string, int>& word_counts, ostream& output) {
    for (const auto& [word, count] : word_counts) {
        output << word << ' ' << count << '\n';
    }
}
