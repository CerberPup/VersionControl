#include <QtTest/QtTest>
#include <iostream>
#include <list>

#define N 10000
namespace 
{
    int compareFile(FILE* f1, FILE* f2) {

        char buf1[N];
        char buf2[N];

        do {
            size_t r1 = fread(buf1, 1, N, f1);
            size_t r2 = fread(buf2, 1, N, f2);

            if (r1 != r2 ||
                memcmp(buf1, buf2, r1)) {
                return 0;  // Files are not equal
            }
        } while (!feof(f1) && !feof(f2));

        return feof(f1) && feof(f2);
    }

}
struct testInfo
{
    QString Base;
    QString Second;
    QString Gold;
    QString Output;
    testInfo(QString _base, QString _second, QString _gold, QString _output) :Base(_base), Second(_second), Gold(_gold), Output(_output) {};
};

class Tester : public QObject
{
    Q_OBJECT

private:
    std::list<testInfo> filesGenerate;
    std::list<testInfo> filesApply;
private slots:
    void initTestCase();
    void cleanupTestCase();

    void DiffGenerator();
    void DiffApply();
};

void Tester::initTestCase()
{
    QString path = QDir().absolutePath();
    std::cout << "Test file location: " << path.toStdString() << std::endl;
    {
        QDirIterator it(path + "/TestCases", QStringList() << "diffgen_*_base.txt", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            QFileInfo f(it.next());
            QString fileName = f.completeBaseName();
            fileName.resize(fileName.size() - 5);
            QString second = f.path() + "/" + fileName + "_second.txt";
            QString gold = f.path() + "/" + fileName + "_wgold.diff";
            QString output = f.path() + "/Generated/" + fileName + ".diff";
            if (QFileInfo(gold).exists())
            {
                filesGenerate.push_back(testInfo(f.absoluteFilePath(), second, gold, output));
            }
            else
            {
                qDebug() << "Missing gold: " << gold;
            }

        }
    }
    {
        QDirIterator it(path + "/TestCases", QStringList() << "diffapply_*_base.txt", QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            QFileInfo f(it.next());
            QString fileName = f.completeBaseName();
            fileName.resize(fileName.size() - 5);
            QString second = f.path() + "/" + fileName + "_second.diff";
            QString gold = f.path() + "/" + fileName + "_wgold.txt";
            QString output = f.path() + "/Generated/" + fileName + ".txt";
            if (QFileInfo(gold).exists())
            {
                filesApply.push_back(testInfo(f.absoluteFilePath(), second, gold, output));
            }
            else
            {
                qDebug() << "Missing gold: " << gold;
            }

        }
    }
        
}

void Tester::cleanupTestCase()
{
}

void Tester::DiffGenerator()
{
    QString program;
#ifdef _WIN32
    if (QFileInfo("VCL.exe").exists())
    {
        program = QFileInfo("VCL.exe").absoluteFilePath();
    }
#else
    if (QFileInfo("VCL").exists())
    {
        program = QFileInfo("VCL").absoluteFilePath();
    }
#endif // _win32
    else
    {
        QFAIL("File not found: VCL[.exe]");
    }
    QProcess *myProcess = new QProcess(this);
    for (testInfo test : filesGenerate )
    {
        
        QStringList arguments;
        arguments << "-Generate" << "Program" << "-Input" << test.Base << "-Second" << test.Second << "-Output" << test.Output << "-nogui";
        QString forDebug;
        for (auto arg : arguments)
        {
            forDebug += " " + arg;
        }
        myProcess->start(program, arguments);
        myProcess->waitForFinished(30000);
        FILE* gold = fopen(test.Gold.toStdString().c_str(), "r");
        FILE* out = fopen(test.Output.toStdString().c_str(), "r");
        std::cout << std::boolalpha << (test.Base).toStdString() << " produces valid output: " << (compareFile(gold, out) == 1) << "\n";
    }
}

void Tester::DiffApply()
{
    QString program;
#ifdef _WIN32
    if (QFileInfo("VCL.exe").exists())
    {
        program = QFileInfo("VCL.exe").absoluteFilePath();
    }
#else
    if (QFileInfo("VCL").exists())
    {
        program = QFileInfo("VCL").absoluteFilePath();
    }
#endif // _win32
    else
    {
        QFAIL("File not found: VCL[.exe]");
    }

    QProcess *myProcess = new QProcess(this);
    for (testInfo test : filesApply)
    {

        QStringList arguments;
        arguments << "-dump" << test.Output << "-Input" << test.Base << "-Second" << test.Second << "-nogui";
        myProcess->start(program, arguments);
        myProcess->waitForFinished(300000);
        FILE* gold = fopen(test.Gold.toStdString().c_str(), "r");
        FILE* out = fopen(test.Output.toStdString().c_str(), "r");
        std::cout << std::boolalpha << (test.Base).toStdString() << " produces valid output: " << (compareFile(gold, out) == 1) << "\n";
    }
}

QTEST_MAIN(Tester)
#include "GeneratedFiles\release\main.moc"