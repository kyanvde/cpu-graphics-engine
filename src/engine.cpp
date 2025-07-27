#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "io/parsers/JsonSceneParser.h"
#include "io/parsers/SceneParser.h"
#include "io/writers/BMPWriter.h"
#include "model/Image.h"

using ParserFactory = std::function<std::unique_ptr<SceneParser>()>;

std::unique_ptr<SceneParser> createParserForSceneFile(
    const std::string& sceneFile) {
  const std::string extension =
      std::filesystem::path(sceneFile).extension().string();

  if (extension == ".json") {
    return std::make_unique<JsonSceneParser>();
  }

  throw std::runtime_error("Unsupported sceneFile extension: " + extension);
}

int main(int argc, char* argv[]) {
  try {
    std::vector<std::string> args(argv + 1, argv + argc);

    // If no filenames are provided in the program arguments
    if (args.empty()) {
      std::ifstream fileIn("filelist");
      if (!fileIn) {
        std::cerr << "Error: Could not open 'filelist'" << '\n';
        return EXIT_FAILURE;
      }

      std::string filelistName;
      while (std::getline(fileIn, filelistName)) {
        if (!filelistName.empty()) {
          args.push_back(filelistName);
        }
      }
    }

    // Render each scene
    for (const std::string& sceneFile : args) {
      try {
        std::unique_ptr<SceneParser> parser =
            createParserForSceneFile(sceneFile);

        Scene scene = parser->parse(sceneFile);
        Image image = scene.render();
        std::string outputFileName =
            sceneFile.substr(0, sceneFile.find_last_of('.')) + ".bmp";
        if (BMPWriter writer; !image.writeTo(outputFileName, writer)) {
          throw std::runtime_error("Error writing to file: " + outputFileName);
        }
      } catch (const std::exception& e) {
        std::cerr << "Failed to render scene (" << sceneFile
                  << "): " << e.what() << '\n';
      }
    }

    return EXIT_SUCCESS;
  } catch (const std::bad_alloc&) {
    std::cerr << "Error: insufficient memory" << '\n';
    return EXIT_FAILURE;
  }
}
