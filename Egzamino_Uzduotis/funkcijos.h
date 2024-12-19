#pragma once
#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <regex>

using namespace std;

string readTextFromFile(const string& filename);

unordered_map<string, int> countWordOccurrences(const string& text);

unordered_map<string, int> findRepeatedWords(const unordered_map<string, int>& wordCounts);

unordered_map<string, set<int>> createCrossReference(const string& text);

vector<string> extractUrls(const string& text);

void writeWordCountsToFile(const unordered_map<string, int>& repeatedWords, const string& filename);

void writeCrossReferenceToFile(const unordered_map<string, set<int>>& crossReference, const string& filename);

void writeUrlsToFile(const vector<string>& urls, const string& filename);

#endif // FUNKCIJOS_H
