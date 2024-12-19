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

using namespace std;

string readTextFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + filename);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unordered_map<string, int> countWordOccurrences(const string& text) {
    unordered_map<string, int> wordCounts;
    istringstream iss(text);
    string word;
    while (iss >> word) {
        word.erase(remove_if(word.begin(), word.end(), [](char c) {
            return ispunct(c) || c == '–';
            }), word.end());

        transform(word.begin(), word.end(), word.begin(), ::tolower);

        if (any_of(word.begin(), word.end(), [](char c) {
            return isalpha(c);
            })) {
            wordCounts[word]++;
        }
    }
    return wordCounts;
}

unordered_map<string, int> findRepeatedWords(const unordered_map<string, int>& wordCounts) {
    unordered_map<string, int> repeatedWords;

    for (const auto& pair : wordCounts) {
        if (pair.second > 1) {
            repeatedWords[pair.first] = pair.second;
        }
    }

    return repeatedWords;
}

unordered_map<string, set<int>> createCrossReference(const string& text) {
    unordered_map<string, set<int>> crossReference;
    istringstream iss(text);
    string line;
    int lineNumber = 1;
    while (getline(iss, line)) {
        istringstream lineStream(line);
        string word;
        while (lineStream >> word) {
            word.erase(remove_if(word.begin(), word.end(), [](char c) {
                return ispunct(c) || c == '–';
                }), word.end());

            transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (any_of(word.begin(), word.end(), [](char c) {
                return isalpha(c);
                })) {
                crossReference[word].insert(lineNumber);
            }
        }
        lineNumber++;
    }
    return crossReference;
}

vector<string> extractUrls(const string& text) {
    vector<string> urls;

    regex url_regex(R"((https?://)?([a-zA-Z]+[a-zA-Z0-9.-]*\.[a-zA-Z]{2,})(/\S*)?)",
        regex::icase);

    auto words_begin = sregex_iterator(text.begin(), text.end(), url_regex);
    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        urls.push_back(match.str());
    }

    return urls;
}

void writeWordCountsToFile(const unordered_map<string, int>& repeatedWords, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Neiseina atidaryti output failo: " + filename);
    }

    outFile << left
        << setw(20) << "Zodis"
        << setw(15) << "Pasikartojimu skaicius" << "\n";
    outFile << string(35, '-') << "\n";

    vector<pair<string, int>> sortedWords(repeatedWords.begin(), repeatedWords.end());
    sort(sortedWords.begin(), sortedWords.end());

    for (const auto& pair : sortedWords) {
        string countStr = to_string(pair.second) + " kartus";

        outFile << left
            << setw(20) << pair.first
            << setw(15) << countStr
            << "\n";
    }

    outFile.close();
}

void writeCrossReferenceToFile(const unordered_map<string, set<int>>& crossReference, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Neiseina atidaryti output failo: " + filename);
    }

    outFile << left
        << setw(20) << "Zodis"
        << setw(25) << "Eiluciu numeriai" << "\n";
    outFile << string(45, '-') << "\n";

    vector<pair<string, set<int>>> sortedReference(crossReference.begin(), crossReference.end());
    sort(sortedReference.begin(), sortedReference.end());

    for (const auto& pair : sortedReference) {
        if (pair.second.size() > 1) {
            ostringstream lineNumbers;
            for (auto it = pair.second.begin(); it != pair.second.end(); ++it) {
                lineNumbers << *it;
                if (next(it) != pair.second.end()) {
                    lineNumbers << ", ";
                }
            }

            outFile << left
                << setw(20) << pair.first
                << setw(25) << lineNumbers.str()
                << "\n";
        }
    }

    outFile.close();
}


void writeUrlsToFile(const vector<string>& urls, const string& filename) {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        throw runtime_error("Neiseina atidaryti output failo: " + filename);
    }

    for (const auto& url : urls) {
        outFile << url << "\n";
    }

    outFile.close();
}
