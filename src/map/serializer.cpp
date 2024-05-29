//
// Created by viann on 28/05/2024.
//
#include "serializer.h"

#include "config.h"

#include <string>
#include <fstream>
#include <cassert>
#include <utility>

struct check_line_equal {
    explicit check_line_equal(std::string _what) : what(std::move(_what)) {}
    std::string what;
};

std::istream& operator>>(std::istream& is, check_line_equal const& check) {
    std::string line;
    is >> line;
    assert(line == check.what && "Assertion Failed : expected value in serialized file is not what was provided !");
    return is;
}

namespace serializer {

    static map_header read_header(std::ifstream& file) {
        map_header header;
        file >> header.width >> header.height;
        return header;
    }

    static map_row read_line(std::ifstream& file) {
        map_row row;
        file >> row.type;
        file >> row.position.x >> row.position.y;
        switch (row.type) {
            case map_row::entity_type::tile: {
                file >> row.tile.i >> row.tile.j;
                file >> row.tile.atlas_id;
            } break;

            case map_row::entity_type::animated_tile: {
                file >> row.animated_tile.animation_id;
            } break;
        }

        return row;
    }

    map deserialize(const char* filepath) {
        std::ifstream file(filepath);

        // verify that the file starts with the right prelude
        // so that we only parse what we can parse
        file >> check_line_equal(config::serializer::prelude);

        map parsed_data;
        parsed_data.header = read_header(file);
        while(!file.eof() && !file.fail()) {
            parsed_data.data.push_back(read_line(file));
        }
        return parsed_data;
    }

    std::istream& operator>>(std::istream& is, map_row::entity_type& type) {
        uint32_t val;
        is >> val;
        assert(val < (uint32_t)map_row::entity_type::count && "Assertion Failed : value is not a valid entity type !");
        type = (map_row::entity_type)val;
        return is;
    }

} // namespace serializer
