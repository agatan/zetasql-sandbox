#include <iostream>

#include "zetasql/public/analyzer.h"

int main() {
    std::istreambuf_iterator<char> begin(std::cin), end;
    const std::string query(begin, end);

    const zetasql::AnalyzerOptions analyzer_options;
    zetasql::TableNamesSet table_names_set;

    auto status = zetasql::ExtractTableNamesFromScript(query, analyzer_options, &table_names_set);
    std::cout << "status: " << status.ToString() << std::endl;
    for (std::vector<std::string> const& table_name : table_names_set) {
        size_t i = 0;
        for (const std::string& path : table_name) {
            if (i != 0) {
                std::cout << ".";
            }
            std::cout << path;
            i++;
        }
        std::cout << std::endl;
    }
    return 0;
}
