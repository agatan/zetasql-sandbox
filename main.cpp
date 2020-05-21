#include <iostream>

#include "zetasql/public/analyzer.h"
#include "zetasql/public/simple_catalog.h"

std::string read_all(std::istream& in) {
    std::istreambuf_iterator<char> begin(in), end;
    return {begin, end};
}

int main() {
    const std::string query = read_all(std::cin);

    const zetasql::AnalyzerOptions analyzer_options;
    zetasql::TableNamesSet table_names_set;

    auto status = zetasql::ExtractTableNamesFromScript(query, analyzer_options, &table_names_set);
    if (!status.ok()) {
        std::cout << "status: " << status.ToString() << std::endl;
        return 1;
    }
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
