#include "funkcijos.h"
#include <iostream>
#include <stdexcept>

using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    try {
        #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        #endif

        string filename = "_input_text.txt";
        string text = readTextFromFile(filename);
        auto wordCounts = countWordOccurrences(text);

        auto repeatedWords = findRepeatedWords(wordCounts);
        writeWordCountsToFile(repeatedWords, "__word_counts.txt");
        auto crossReference = createCrossReference(text);
        writeCrossReferenceToFile(crossReference, "__cross_reference.txt");
        auto urls = extractUrls(text);
        writeUrlsToFile(urls, "__urls.txt");
        cout << "Teksto perziura ivykdyta. Patikrinkite output failus:\n";
        cout << "- _word_counts.txt\n";
        cout << "- _cross_reference.txt\n";
        cout << "- _urls.txt\n";
        return 0;
    }
    catch (const exception& e) {
        cerr << "Klaida: " << e.what() << endl;
        return 1;
    }
}
