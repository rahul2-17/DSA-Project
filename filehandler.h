#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "avl.h"
#include <fstream>
#include <string>

class FileHandler {
public:
    static void processFile(const std::string& filename, AVL& tree);
};

#endif
