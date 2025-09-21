#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

#include "utils.hpp"

bool check_if_is_header(std::string line) {
  return line[0] == '[' && line[line.size() - 1] == ']';
}

bool check_if_is_value_key(std::string line) {
  auto parts = split(line, '=');
  return parts.size() == 2;
}

// TODO: learn how to pass a complete file path for example "~" or "/" what is
// the difference?
const std::string FILE_PATH = "./config.ini";

// TODO: learn how to handle the life cycle of streams what are the "streams" of
// c++ lean the concept (everyhing is text?) (so everyhing can be streamed) (The
// primegean definition)

int main(int argc, char *argv[]) {
  std::fstream file(FILE_PATH);

  if (file.fail()) {
    std::cout << "ERROR this cannot be read!" << "\n";
    return EXIT_FAILURE;
  }

  std::map<std::string, std::map<std::string, std::string>> config;

  std::string last_header_readed;

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;

    bool is_header = check_if_is_header(line);
    bool is_value_key = check_if_is_value_key(line);

    if (is_header) {
      // TODO: Check implementation of substr underground
      std::string header = line.substr(
          1, line.size() - 2); // line.length - 2 "[abb]" (0 -> should ignore
                               // the righth "]" .size returns 5 because is not
                               // 0 based so -2  )
      last_header_readed = header;
      config[header] = {};
    }

    if (is_value_key) {
      if (!last_header_readed.empty()) {
        auto parts = split(line, '=');
        std::string key = parts[0];
        std::string value = parts[1];
        config[last_header_readed][key] = value;
      } else {
        // possible key-value without header
        break;
      }
    }

    if (!is_header && !is_value_key) {
      break;
    }

    // cases:
    // 1. a keyvalue before a section should give a error because dont have
    // "general section"
    // 2. should validate if each pair as in format <key>=<value>
  }

  file.close();

  for (auto &section : config) {
    std::cout << section.first << "\n";
    for (auto &pair : section.second) {
      std::cout << pair.first << ":" << pair.second << "\n";
    }
  }

  return EXIT_SUCCESS;
}
