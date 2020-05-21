#include <map>
#include <iostream>

#include "zetasql/public/analyzer.h"
#include "zetasql/public/type.h"
#include "zetasql/public/simple_catalog.h"
#include "zetasql/resolved_ast/resolved_ast_visitor.h"

std::string read_all(std::istream& in) {
    std::istreambuf_iterator<char> begin(in), end;
    return {begin, end};
}

void init_dummy_catalog(zetasql::SimpleCatalog *catalog, zetasql::TypeFactory *types) {
    std::map<std::string, std::vector<std::pair<std::string, const zetasql::Type*>>> tables = {
        {"users", {{"id", types->get_int64()}}}
    };
    for (auto&& [table_name, columns] : tables) {
        std::unique_ptr<const zetasql::Table> table = std::make_unique<zetasql::SimpleTable>(table_name, columns);
        catalog->AddOwnedTable(table_name, std::move(table));
    }
}


class JoinStatsAggregateVisitor : public zetasql::ResolvedASTVisitor {
  public:
    absl::Status VisitResolvedJoinScan(const zetasql::ResolvedJoinScan *join) {
        std::cout << "join" << std::endl;
        auto left_scan = join->left_scan();
        if (left_scan->Is<zetasql::ResolvedTableScan>()) {
            std::cout << "left: " << left_scan->GetAs<zetasql::ResolvedTableScan>()->table()->FullName() << std::endl;
        }
        auto right_scan = join->right_scan();
        if (right_scan->Is<zetasql::ResolvedTableScan>()) {
            std::cout << "right: " << right_scan->GetAs<zetasql::ResolvedTableScan>()->table()->FullName() << std::endl;
        }
        return {};
    }
};

int main() {
    const std::string query = read_all(std::cin);

    zetasql::AnalyzerOptions analyzer_options;
    analyzer_options.mutable_language()->SetSupportsAllStatementKinds();
    zetasql::TableNamesSet table_names_set;

    zetasql::TypeFactory type_factory;
    zetasql::SimpleCatalog catalog("project");
    init_dummy_catalog(&catalog, &type_factory);
    catalog.AddZetaSQLFunctions(zetasql::ZetaSQLBuiltinFunctionOptions(analyzer_options.language()));

    std::unique_ptr<const zetasql::AnalyzerOutput> analyzer_output;
    auto status = zetasql::AnalyzeStatement(query, analyzer_options, &catalog, &type_factory, &analyzer_output);
    if (!status.ok()) {
        std::cout << "status: " << status.ToString() << std::endl;
        return 1;
    }

    const zetasql::ResolvedStatement* resolved_statement = analyzer_output->resolved_statement();
    JoinStatsAggregateVisitor visitor;
    status = resolved_statement->Accept(&visitor);
    if (!status.ok()) {
        std::cerr << "status: " << status.ToString() << std::endl;
    }

    return 0;
}
