#include "funkcijos.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <sstream>

std::string readTextFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::unordered_map<std::string, int> countWordOccurrences(const std::string& text) {
    std::unordered_map<std::string, int> wordCounts;
    std::istringstream iss(text);
    std::string word;
    while (iss >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
            return std::ispunct(c) || c == '–';
            }), word.end());

        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (std::any_of(word.begin(), word.end(), [](char c) {
            return std::isalpha(c);
            })) {
            wordCounts[word]++;
        }
    }
    return wordCounts;
}

std::unordered_map<std::string, int> findRepeatedWords(const std::unordered_map<std::string, int>& wordCounts) {
    std::unordered_map<std::string, int> repeatedWords;

    for (const auto& pair : wordCounts) {
        if (pair.second > 1) {
            repeatedWords[pair.first] = pair.second;
        }
    }

    return repeatedWords;
}

std::unordered_map<std::string, std::set<int>> createCrossReference(const std::string& text) {
    std::unordered_map<std::string, std::set<int>> crossReference;
    std::istringstream iss(text);
    std::string line;
    int lineNumber = 1;
    while (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        std::string word;
        while (lineStream >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
                return std::ispunct(c) || c == '–';
                }), word.end());

            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (std::any_of(word.begin(), word.end(), [](char c) {
                return std::isalpha(c);
                })) {
                crossReference[word].insert(lineNumber);
            }
        }
        lineNumber++;
    }
    return crossReference;
}

std::vector<std::string> extractUrls(const std::string& text) {
    std::vector<std::string> urls;

    std::regex url_regex(R"((https?://)?([a-zA-Z]+[a-zA-Z0-9.-]*\.[a-zA-Z]{2,})(/\S*)?)",
        std::regex::icase);

    auto words_begin = std::sregex_iterator(text.begin(), text.end(), url_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        urls.push_back(match.str());
    }

    return urls;
}

void writeWordCountsToFile(const std::unordered_map<std::string, int>& repeatedWords, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Neiseina atidaryti output failo: " + filename);
    }

    outFile << std::left
        << std::setw(20) << "Zodis"
        << std::setw(15) << "Pasikartojimu skaicius" << "\n";
    outFile << std::string(35, '-') << "\n";

    std::vector<std::pair<std::string, int>> sortedWords(repeatedWords.begin(), repeatedWords.end());
    std::sort(sortedWords.begin(), sortedWords.end());

    for (const auto& pair : sortedWords) {
        std::string countStr = std::to_string(pair.second) + " kartus";

        outFile << std::left
            << std::setw(20) << pair.first
            << std::setw(15) << countStr
            << "\n";
    }

    outFile.close();
}

void writeCrossReferenceToFile(const std::unordered_map<std::string, std::set<int>>& crossReference, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw std::runtime_error("Neiseina atidaryti output failo: " + filename);
    }

    outFile << std::left
        << std::setw(20) << "Zodis"
        << std::setw(25) << "Eiluciu numeriai" << "\n";
    outFile << std::string(45, '-') << "\n";

    std::vector<std::pair<std::string, std::set<int>>> sortedReference(crossReference.begin(), crossReference.end());
    std::sort(sortedReference.begin(), sortedReference.end());

    for (const auto& pair : sortedReference) {
        if (pair.second.size() > 1) {
            std::ostringstream lineNumbers;
            for (auto it = pair.second.begin(); it != pair.second.end(); ++it) {
                lineNumbers << *it;
                if (std::next(it) != pair.second.end()) {
                    lineNumbers << ", ";
                }
            }

            outFile << std::left
                << std::setw(20) << pair.first
                << std::setw(25) << lineNumbers.str()
                << "\n";
        }
    }

    outFile.close();
}


void writeUrlsToFile(const std::vector<std::string>& urls, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        throw std::runtime_error("Neiseina atidaryti output failo: " + filename);
    }

    for (const auto& url : urls) {
        outFile << url << "\n";
    }

    outFile.close();
}

