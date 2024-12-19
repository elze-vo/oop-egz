#include "funkcijos.h"
#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::string filename = "_input_text.txt";

        std::string text = readTextFromFile(filename);

        auto wordCounts = countWordOccurrences(text);

        auto repeatedWords = findRepeatedWords(wordCounts);

        writeWordCountsToFile(repeatedWords, "__word_counts.txt");

        auto crossReference = createCrossReference(text);

        writeCrossReferenceToFile(crossReference, "__cross_reference.txt");

        auto urls = extractUrls(text);

        writeUrlsToFile(urls, "__urls.txt");

        std::cout << "Teksto perziura ivykdyta. Patikrinkite output failus:\n";
        std::cout << "- _word_counts.txt\n";
        std::cout << "- _cross_reference.txt\n";
        std::cout << "- _urls.txt\n";

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl;
        return 1;
    }
}
