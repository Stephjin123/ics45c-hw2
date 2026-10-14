#include <gtest/gtest.h>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include "word_count.hpp"
using namespace std;

// ---------- to_lowercase ----------
TEST(StudentToLowercase, MixedCase) {
    string s = "HeLLo WORLD";
    to_lowercase(s);
    EXPECT_EQ(s, "hello world");
}
TEST(StudentToLowercase, NonLettersUnchanged) {
    string s = "ABC-123!z";
    to_lowercase(s);
    EXPECT_EQ(s, "abc-123!z");
}
TEST(StudentToLowercase, AllUpper) {
    string s = "XYZ";
    to_lowercase(s);
    EXPECT_EQ(s, "xyz");
}
TEST(StudentToLowercase, Empty) {
    string s;
    to_lowercase(s);
    EXPECT_EQ(s, "");
}

// ---------- load_stopwords ----------
TEST(StudentLoadStopwords, LowercasesMixedCase) {
    istringstream in("The AND\nOf");
    set<string> expected{"the", "and", "of"};
    EXPECT_EQ(load_stopwords(in), expected);
}
TEST(StudentLoadStopwords, DuplicatesCollapse) {
    istringstream in("the THE The");
    set<string> expected{"the"};
    EXPECT_EQ(load_stopwords(in), expected);
}
TEST(StudentLoadStopwords, EmptyFile) {
    istringstream in("");
    EXPECT_TRUE(load_stopwords(in).empty());
}

// ---------- count_words ----------
TEST(StudentCountWords, CaseInsensitiveDocument) {
    istringstream doc("Apple apple APPLE");
    map<string, int> expected{{"apple", 3}};
    EXPECT_EQ(count_words(doc, {}), expected);
}
TEST(StudentCountWords, StopWordLeftOut) {
    istringstream doc("the cat and the dog");
    set<string> stop{"the", "and"};
    map<string, int> expected{{"cat", 1}, {"dog", 1}};
    EXPECT_EQ(count_words(doc, stop), expected);
}
TEST(StudentCountWords, UppercaseWordMatchesStopWord) {
    istringstream doc("The THE the bird");
    set<string> stop{"the"};
    map<string, int> expected{{"bird", 1}};
    EXPECT_EQ(count_words(doc, stop), expected);
}
TEST(StudentCountWords, MixedCaseStopFileEndToEnd) {
    istringstream stopIn("ThE");
    auto stop = load_stopwords(stopIn);
    istringstream doc("the The cat");
    map<string, int> expected{{"cat", 1}};
    EXPECT_EQ(count_words(doc, stop), expected);
}
TEST(StudentCountWords, EmptyDocument) {
    istringstream doc("");
    EXPECT_TRUE(count_words(doc, {"the"}).empty());
}
TEST(StudentCountWords, AllStopWords) {
    istringstream doc("the and the of");
    EXPECT_TRUE(count_words(doc, {"the", "and", "of"}).empty());
}
TEST(StudentCountWords, SingleWordOnce) {
    istringstream doc("zebra");
    map<string, int> expected{{"zebra", 1}};
    EXPECT_EQ(count_words(doc, {}), expected);
}
TEST(StudentCountWords, WhitespaceVariety) {
    istringstream doc("  a\tb\n\na   c  ");
    map<string, int> expected{{"a", 2}, {"b", 1}, {"c", 1}};
    EXPECT_EQ(count_words(doc, {}), expected);
}
TEST(StudentCountWords, ManyRepeats) {
    istringstream doc("x x x x x x x x x x x x");
    map<string, int> expected{{"x", 12}};
    EXPECT_EQ(count_words(doc, {}), expected);
}
TEST(StudentCountWords, NoStopWordsCountsEverything) {
    istringstream doc("b a c a");
    map<string, int> expected{{"a", 2}, {"b", 1}, {"c", 1}};
    EXPECT_EQ(count_words(doc, {}), expected);
}

// ---------- output_word_counts ----------
TEST(StudentOutput, SortedFormat) {
    map<string, int> m{{"banana", 2}, {"apple", 7}, {"cherry", 10}};
    ostringstream out;
    output_word_counts(m, out);
    EXPECT_EQ(out.str(), "apple 7\nbanana 2\ncherry 10\n");
}
TEST(StudentOutput, EmptyMapWritesNothing) {
    ostringstream out;
    output_word_counts({}, out);
    EXPECT_EQ(out.str(), "");
}
TEST(StudentOutput, SingleEntry) {
    ostringstream out;
    output_word_counts({{"word", 1}}, out);
    EXPECT_EQ(out.str(), "word 1\n");
}

// ---------- end to end ----------
TEST(StudentEndToEnd, FullPipeline) {
    istringstream stopIn("A the");
    auto stop = load_stopwords(stopIn);
    istringstream doc("The Zebra saw a zebra and THE apple");
    auto counts = count_words(doc, stop);
    ostringstream out;
    output_word_counts(counts, out);
    EXPECT_EQ(out.str(), "and 1\napple 1\nsaw 1\nzebra 2\n");
}
