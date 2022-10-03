#include <iostream>
#include <fstream>

#include "ArgumentParser.h"

#include "WordCodeBoardParser.h"
#include "PuzzlinkBoardParser.h"

#include "AsciiBoardOutput.h"

#include "YajilinSolver.h"

void print_help() {
	std::ifstream helpFile("help.txt");
	if (!helpFile.good()) {
		std::cerr << "help.txt not found" << std::endl;
	}

	std::cout << helpFile.rdbuf();
}

int main(int argc, char** argv) {
	ArgumentParser argumentParser(argc, argv);
	if (argumentParser.GetBool("h") || argumentParser.GetBool("help")) {
		print_help();
		return 0;
	}

	BoardParser* parser;
	std::string parserType = argumentParser.GetString("input", "puzzlink");
	if (parserType == "code") parser = new WordCodeBoardParser();
	else if (parserType == "puzzlink") parser = new PuzzlinkBoardParser();
	else {
		std::cerr << "Unknown input parser: " << parserType << std::endl;
		std::cerr << "Supported input parsers: code, puzzlink" << std::endl;
		return 0;
	}

	std::string input = argumentParser.GetArgument();
	if (input.empty()) {
		std::cerr << "No input specified." << std::endl;
		print_help();
		return 0;
	}

	auto board = parser->Parse(input);

	YajilinSolver solver(argumentParser.GetInt("depth", 5));
	solver.Solve(&board);

	BoardOutput* output;
	std::string outputType = argumentParser.GetString("output", "ascii");
	if (outputType == "ascii") output = new AsciiBoardOutput();
	else {
		std::cerr << "Unknown output format: " << outputType << std::endl;
		std::cerr << "Supported output formats: ascii" << std::endl;
		return 0;
	}

	std::cout << output->Format(board);
	return 0;
}