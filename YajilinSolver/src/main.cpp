#include <iostream>

#include "ArgumentParser.h"
#include "WordCodeBoardParser.h"
#include "AsciiBoardOutput.h"
#include "YajilinSolver.h"

void print_help() {
	//TODO: Rewrite this to more fit the typical style
	std::cout << "Yajilin Solver by xenix1337" << std::endl;
	std::cout << "Usage: yajilinsolver [-h] [-i inputString] [-o type] [-d recursionDepth]" << std::endl;
	std::cout << "	-h: Shows help" << std::endl;
	std::cout << "	-i inputString: Provides input in format described below:" << std::endl;
	std::cout << "TODO" << std::endl;
	std::cout << "	-o type: Changes the output format to one of the possible: " << std::endl;
	std::cout << "		ascii - draws solved ASCII Yajilin board" << std::endl;
	std::cout << "		code - outputs every cell as its code, each cell divided by space" << std::endl;
	std::cout << "	-d recursionDepth: Defines max depth of recursive search. Higher values might solve harder Yajilins, but it may take significantly longer. As recursion is used as a last method, when every other fails, easier Yajilins shouldn't be impacted by this option." << std::endl;
}

int main(int argc, char** argv) {
	ArgumentParser argumentParser(argc, argv);
	if (argumentParser.GetBool("h") || argumentParser.GetBool("help")) {
		print_help();
		return 0;
	}

	BoardParser* parser;
	std::string parserType = argumentParser.GetString("i", "code");
	if (parserType == "code") parser = new WordCodeBoardParser();
	else if (parserType == "puzzlink") { throw std::runtime_error("Not implemented"); return 0; }
	else {
		std::cerr << "Unknown input parser: " << parserType << std::endl;
		std::cerr << "Supported input parsers: code, puzzlink" << std::endl;
		return 0;
	}
	//auto board = parser->Parse("5 5 0 0 0 0 0 0 0 0R 0 0 0 0 0 2L 0 0R 0 0 0 0 0 0 0 0 0");
	auto board = parser->Parse("10 10 0 0 0 0 0 2L 0 0 0 0 0 0 0 0 0 0 0 0 0 3D 0 0 0 0 0 0 2D 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 2L 0 0 0 0 0 0 0 0 0 0 0 2R 0 0 0 0 0 0 0 0 2D 0 0 0 0 0 2U 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1L 0 0 0 0 0 0 0 0 0 0 0 0 0");

	YajilinSolver solver(argumentParser.GetInt("d", 5));
	solver.Solve(&board);

	BoardOutput* output = new AsciiBoardOutput();
	std::cout << output->Format(board);
	return 0;
}