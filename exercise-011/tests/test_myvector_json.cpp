#include <catch2/catch_all.hpp>
#include "myvector.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

using json = nlohmann::json;

TEST_CASE("JSON-driven test cases for mystd::myvector<int>", "[json][myvector]") {
    // Pfad ggf. in CTest via WORKING_DIRECTORY setzen
    std::ifstream in("tests/test_vectors.json");
    CHECK(in);
    if (!in) {
        FAIL("tests/test_vectors.json not found");
        return;
    }
    json doc;
    in >> doc;
    REQUIRE(doc.contains("cases"));
    for (const auto& tc : doc["cases"]) {
        const std::string name = tc.value("name", "<unnamed>");
        DYNAMIC_SECTION(name) {
            mystd::myvector<int> v;

            if (tc.contains("initial_capacity"))
                v.reserve(tc["initial_capacity"].get<size_t>());

            if (tc.contains("initial_values")) {
                const auto& arr = tc["initial_values"];
                v.resize(arr.size());
                for (size_t i = 0; i < arr.size(); ++i) v[i] = arr[i].get<int>();
            } else if (tc.contains("initial_size")) {
                v.resize(tc["initial_size"].get<size_t>());
            }

            json reads = json::array();
            json errors = json::array();

            if (tc.contains("operations")) {
                for (const auto& op : tc["operations"]) {
                    try {
                        const std::string op_name = op.value("op", "");
                        if (op_name == "push_back") {
                            v.push_back(op.at("value").get<int>());
                        } else if (op_name == "resize") {
                            v.resize(op.at("new_size").get<size_t>());
                        } else if (op_name == "at") {
                            size_t idx = op.at("index").get<size_t>();
                            int value = v.at(idx);
                            reads.push_back({{"index", idx}, {"value", value}});
                        } else if (op_name == "clear") {
                            v.clear();
                        } else if (op_name == "reserve") {
                            v.reserve(op.at("new_cap").get<size_t>());
                        } else {
                            errors.push_back({{"op", op_name}, {"error", "unknown_operation"}});
                        }
                    } catch (const std::out_of_range&) {
                        json e = op;
                        e["error"] = "out_of_range";
                        errors.push_back(e);
                    } catch (const std::exception& e) {
                        json eobj = op;
                        eobj["error"] = std::string("exception: ") + e.what();
                        errors.push_back(eobj);
                    }
                }
            }

            REQUIRE(tc.contains("expect"));
            const auto& expect = tc["expect"];

            // final_size (exakt)
            REQUIRE(v.size() == expect.at("final_size").get<size_t>());

            // capacity (nur prüfen, wenn min_capacity angegeben)
            if (expect.contains("min_capacity")) {
                CHECK(v.capacity() >= expect["min_capacity"].get<size_t>());
            }

            // reads (optional, Reihenfolge muss stimmen)
            if (expect.contains("reads")) {
                CHECK(reads == expect["reads"]);
            }

            // errors (optional, Reihenfolge entspricht Ausführung)
            if (expect.contains("errors")) {
                CHECK(errors == expect["errors"]);
            }

            // final_values (optional)
            if (expect.contains("final_values")) {
                const auto& vals = expect["final_values"];
                REQUIRE(vals.size() == v.size());
                for (size_t i = 0; i < vals.size(); ++i) {
                    INFO("Mismatch at index " << i);
                    CHECK(v[i] == vals[i].get<int>());
                }
            }
        }
    }
}
