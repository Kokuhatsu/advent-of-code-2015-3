#include <cassert>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_set>

struct Pos {
    std::int64_t x = 0;
    std::int64_t y = 0;

    bool operator==(const Pos&) const = default;
};

template<>
struct std::hash<Pos> {
    std::size_t operator() (const Pos& pos) const noexcept {
        auto h1 = std::hash<std::int64_t>{}(pos.x);
        auto h2 = std::hash<std::int64_t>{}(pos.y);

        return h1 ^ (h2 << 1);
    }
};

int main() {
    const auto input_data_path = std::filesystem::path(__FILE__).remove_filename() / "input.txt";
    auto input_file = std::fstream(input_data_path, std::ios_base::in);

    assert(input_file.is_open());

    Pos santa_position{};
    Pos robot_position{};
    std::unordered_set<Pos> visited_houses{santa_position};

    std::uint64_t step{0};
    while(input_file.eof() == false) {
        auto direction_char = input_file.get();

        Pos* current_position = (step++) % 2 ? &santa_position : &robot_position;

        switch(direction_char) {
            case '<':
                (current_position->x)--;
                break;
            case '>':
                (current_position->x)++;
                break;
            case 'v':
                (current_position->y)--;
                break;
            case '^':
                (current_position->y)++;
                break;
            default:
                continue;
                break;
        }

        visited_houses.insert(*current_position);
    }

    const auto visited_houses_count = visited_houses.size();

    std::cout << "Visited houses: " << visited_houses_count << std::endl;
    return 0;
}
