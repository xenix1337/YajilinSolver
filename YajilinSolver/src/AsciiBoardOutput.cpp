#include "AsciiBoardOutput.h"

std::string AsciiBoardOutput::Format(YajilinBoard board)
{
    std::string ret = "";

    int w = board.GetWidth();
    int h = board.GetHeight();

    if (w == 0 || h == 0) {
        return "";
    }

    for (int y = 0; y < h * 4 + 1; y++) {
        if (y % 4 == 0) {
            ret += VerticalLine(w) + "\n";
            continue;
        }

        for (int x = 0; x < w * 4 + 1; x++) {
            if (x % 4 == 0) {
                ret += "|";
                continue;
            }

            Tile t = board.GetTile(x / 4, y / 4);
            if (t == Tile::BLOCKADE) {
                ret += "X";
                continue;
            }

            if (t == Tile::BLOCKADE_GIVEN) {
                // TODO: Get clue and draw it
                Clue c = board.GetClue(x / 4, y / 4);
                if (c.direction == Direction::UNDEFINED) {
                    ret += ".";
                    continue;
                }

                if (y % 4 == 2 && x % 4 == 2) ret += ('0' + c.value); //TODO: Support larger hints than 9
                else if (y % 4 == 1 && x % 4 == 2 && c.direction == UP) ret += "^";
                else if (y % 4 == 2 && x % 4 == 3 && c.direction == RIGHT) ret += ">";
                else if (y % 4 == 3 && x % 4 == 2 && c.direction == DOWN) ret += "v";
                else if (y % 4 == 2 && x % 4 == 1 && c.direction == LEFT) ret += "<";
                else ret += " ";
                continue;
            }

            if (t == Tile::EMPTY) {
                ret += " ";
                continue;
            }

            if (t == Tile::INVALID) {
                ret += "?";
                continue;
            }

            // Line fragment drawing:
            if (y % 4 == 2 && x % 4 == 2) ret += "*"; //middle
            else if (y % 4 == 1 && x % 4 == 2 && t & 0x1) ret += "*";
            else if (y % 4 == 2 && x % 4 == 3 && t & 0x2) ret += "*";
            else if (y % 4 == 3 && x % 4 == 2 && t & 0x4) ret += "*";
            else if (y % 4 == 2 && x % 4 == 1 && t & 0x8) ret += "*";
            else ret += " ";
        }
        ret += "\n";
    }

    return ret;
}

std::string AsciiBoardOutput::VerticalLine(int n)
{
    //TODO: Less allocations
    std::string s = "+";
    for (int x = 0; x < n; x++) s += "---+";
    return s;
}
