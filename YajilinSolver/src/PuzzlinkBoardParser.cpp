#include "PuzzlinkBoardParser.h"

#include <array>

YajilinBoard PuzzlinkBoardParser::Parse(std::string s)
{
    auto parts = SplitString(s, '/');
    std::string data = parts.top();
    parts.pop();
    int32_t h = atoi(parts.top().c_str());
    parts.pop();
    int32_t w = atoi(parts.top().c_str());

    YajilinBoard board(w, h);

    const std::array<Direction, 4> directionsFromPuzzlink = { UP, DOWN, LEFT, RIGHT };

    int32_t pos = 0;
    for (int i = 0; i < data.length(); i++) {
        uint8_t c = data[i];
        if (c >= '0' && c <= '4') {
            if (i + 1 >= data.length()) break;

            Direction direction = directionsFromPuzzlink[ParseHex(c) - 1];
            int32_t value = ((data[i + 1] != '.') ? ParseHex(data[i + 1]) : 0);

            board.AddClue(pos, Clue(direction, value));

            i++;
        }
        else if (c >= '5' && c <= '9') {
            if (i + 2 >= data.length()) break;

            Direction direction = directionsFromPuzzlink[ParseHex(c) - 5];
            int32_t value = ParseHex(data.substr(i + 1, 2));

            board.AddClue(pos, Clue(direction, value));

            i += 2;
        }
        else if (c == '-') {
            if (i + 4 >= data.length()) break;

            Direction direction = directionsFromPuzzlink[ParseHex(data[i + 1])];
            int32_t value = ParseHex(data.substr(i + 2, 3));

            board.AddClue(pos, Clue(direction, value));

            i += 4;
        }
        else if (c >= 'a' && c <= 'z') {
            int32_t d = (int32_t)c - (int32_t)'a';
            pos += d;
        }
        pos++;
        if (pos > w * h) break;
    }

    return board;
}

std::stack<std::string> PuzzlinkBoardParser::SplitString(std::string& s, char delimiter)
{
    std::stack<std::string> parts;
    parts.push("");
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != delimiter)
            parts.top() += s[i];
        else
            parts.push("");
    }
    if (parts.top() == "") parts.pop();

    return parts;
}

int32_t PuzzlinkBoardParser::ParseHex(std::string s)
{
    int32_t ret = 0;
    for (int i = 0; i < s.length(); i++) {
        ret *= 16;
        ret += ParseHex(s[i]);
    }
    return ret;
}

int32_t PuzzlinkBoardParser::ParseHex(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}
