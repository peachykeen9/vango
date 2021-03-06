#include <stdio.h>
#include <tclap/CmdLine.h>
#include "Processor.h"

using namespace TCLAP;

std::string imgFile;
std::string styleFile;
std::string outFile;
bool actuallyWrite; 
bool verby;

Processor processor; 

void parseCommandLine(int argc, char** argv){
    try {
        CmdLine cmd("Vango Process", ' ', "0.001");

        SwitchArg verbyArg("v", "verbose", "enable debugging information");
        cmd.add(verbyArg);

        ValueArg<string> outFileName("o", "output", "output yaml file to write the canvas information to", false, "", "string");
        cmd.add(outFileName);

        ValueArg<string> styleFileName("s", "style", "style file defining stylistic parameters", true, "style.yaml", "string");
        cmd.add(styleFileName);

        ValueArg<string> imgFileName("i", "image", "image file to process", true, "image.png", "string");
        cmd.add(imgFileName);

        cmd.parse(argc, argv);

        imgFile = imgFileName.getValue();
        styleFile = styleFileName.getValue();
        outFile = outFileName.getValue();
        verby = verbyArg.getValue();       
 
        actuallyWrite = (outFile != "");
    } 
    catch (ArgException &e) { 
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
    }
}   

int main(int argc, char** argv) {
    parseCommandLine(argc, argv);

    std::cout << "running on " << imgFile << " using " << styleFile << std::endl;
    
    processor.initialize(imgFile, styleFile, verby);

    processor.processImage();
    
    if(actuallyWrite){
        std::cout << "writing to " << outFile << std::endl;
        processor.saveToFile(outFile);    
    }
}
