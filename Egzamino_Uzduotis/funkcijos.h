#pragma once
#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <regex>

std::string readTextFromFile(const std::string& filename);

std::unordered_map<std::string, int> countWordOccurrences(const std::string& text);

std::unordered_map<std::string, int> findRepeatedWords(const std::unordered_map<std::string, int>& wordCounts);

std::unordered_map<std::string, std::set<int>> createCrossReference(const std::string& text);

std::vector<std::string> extractUrls(const std::string& text);

void writeWordCountsToFile(const std::unordered_map<std::string, int>& repeatedWords, const std::string& filename);

void writeCrossReferenceToFile(const std::unordered_map<std::string, std::set<int>>& crossReference, const std::string& filename);

void writeUrlsToFile(const std::vector<std::string>& urls, const std::string& filename);


#endif // FUNKCIJOS_H
