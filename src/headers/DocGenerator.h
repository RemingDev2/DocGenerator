#ifndef KUESTO_DOCGENERATOR_H
#define KUESTO_DOCGENERATOR_H

#include <string>
#include <minidocx.hpp>

class DocGenerator {
public:
    static void generateDoc(bool in_PDF, bool oneFile, int nbCopies, const std::string& frontPage);

private:
    static void generateDocx(const std::string& docxName, const std::string& frontPage, const std::string& multiCopy);
    static void generatePDF(bool oneFile, int nbCopies, const std::string& frontPage);
};


#endif //KUESTO_DOCGENERATOR_H
