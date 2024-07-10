#include "../headers/DocGenerator.h"
#include <SQLiteCpp/SQLiteCpp.h>
#include <vector>
#include <cstdio>
#include "../../external/Randomizer/Randomizer.h"


void DocGenerator::generateDoc(bool in_PDF, bool oneFile, int nbCopies, const std::string& frontPage)
{
    if (in_PDF)
    {
        generatePDF(oneFile, nbCopies, frontPage);
    } else {
        int dozen = 0;

        std::string docName = "QCM-";

        bool oneFileSwitch = false;
        std::string oneFileSwitchName;

        for (int i(0); i < nbCopies; i++)
        {
            if (i == 10) { dozen++; i-=10; nbCopies-=10;}

            if (oneFile && !oneFileSwitch)
            {
                oneFileSwitch = true;
                generateDocx(docName + "00", frontPage, oneFileSwitchName);
                oneFileSwitchName = "QCM-00";
            }
            else if (oneFile && oneFileSwitch)
            {
                oneFileSwitch = false;
                generateDocx("tempQCM", frontPage, oneFileSwitchName);
                oneFileSwitchName = "tempQCM";
            }
            else
            {
                generateDocx(docName + std::to_string(dozen) + std::to_string(i), frontPage, "");
            }
        }

        remove("tempQCM.docx");
    }
}


void DocGenerator::generateDocx(const std::string& docxName, const std::string& frontPage, const std::string& multiCopy)
{
    docx::Document document(docxName + ".docx");

    if (!multiCopy.empty()) { document.Open(multiCopy + ".docx"); document.AppendPageBreak(); std::cout << "J'ouvre !\n";}
    if (!frontPage.empty()) { document.Open(frontPage + ".docx"); }

    SQLite::Database db("database.db", SQLite::OPEN_READONLY);

    std::vector<std::string> randomQtnNumber;

    SQLite::Statement incrQuery(db, "SELECT seq FROM sqlite_sequence;");
    incrQuery.executeStep();
    int incrementNumber = incrQuery.getColumn(0).getInt();

    for (int i(1); i < incrementNumber; i++)
    {
        randomQtnNumber.push_back(std::to_string(i));
    }

    randomQtnNumber = randomize(randomQtnNumber);

    SQLite::Statement contentQuery(db, "SELECT * FROM datas WHERE key=?");

    for (int i(1); i < incrementNumber; i++)
    {
        contentQuery.bind(1, randomQtnNumber.back());

        randomQtnNumber.pop_back();
        contentQuery.executeStep();

        std::string content = contentQuery.getColumn(1).getText();

        docx::Paragraph question = document.AppendParagraph();
        question.SetBeforeSpacingAuto();
        question.SetAfterSpacing(0);
        question.AppendRun(std::to_string(i) + ".  [" + content + "] " + contentQuery.getColumn(2).getText());
        question.SetFont("Calibri Light");
        question.SetFontSize(12);


        int asrIncr(4);
        content = contentQuery.getColumn(3).getText();
        int letterIncr = 0;
        while (!content.empty() && asrIncr <= 13)
        {
            std::string prgString = "□ ";
            char letter = char(65 + letterIncr);
            prgString.push_back(letter);
            prgString += ". ";
            prgString += content;

            docx::Paragraph answer = document.AppendParagraph();
            answer.SetAfterSpacing(0);
            answer.SetLeftIndent(500);
            answer.AppendRun(prgString);
            answer.SetFont("Calibri Light");
            answer.SetFontSize(12);

            asrIncr++;
            letterIncr++;

            content = contentQuery.getColumn(asrIncr).getText();
        }

        contentQuery.reset(); contentQuery.clearBindings();
        contentQuery = {db, "SELECT * FROM datas WHERE key=?"};

        if (!(i % 8) && i+1 < incrementNumber) {document.AppendPageBreak();}
    }

    document.Save();
}


void DocGenerator::generatePDF(bool oneFile, int nbCopies, const std::string& frontPage)
{
    int dozen = 0;

    // pdf

    for (int i(0); i < nbCopies; i++)
    {
        if (!frontPage.empty())
        {
            // ouverture page de garde pdf
            // ajouter page de garde
        }

        // code

        if (!oneFile)
        {
            if (!i % 11)
            {
                dozen++;
            }
            // "QCM-" + std::to_string(dozen) + std::to_string(i % 10) + ".docx";
            // nouveau pdf
        }
    }
}