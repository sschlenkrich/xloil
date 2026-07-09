#include "CppUnitTest.h"
#include <xlOil/ExcelCall.h>
#include <xlOil-XLL/ExcelCallMapping.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace xloil;
using std::wstring;
using std::unique_ptr;

namespace Tests
{
  TEST_CLASS(TestExcelCall)
  {
  public:

    TEST_METHOD(TestExcelCallNameLookup)
    {
      Assert::AreEqual(excelFuncNumber("onWindow"), msxll::xlcOnWindow);
      Assert::AreEqual(excelFuncNumber("foobar"), -1);
      Assert::AreEqual(excelFuncName(999), nullptr);
      Assert::AreEqual(excelFuncNumber("n"), msxll::xlfN);

      for (auto entry: FuncMap::sortedNames) 
      {
        auto num = excelFuncNumber(entry.name);
        Assert::AreEqual((int)entry.number, num, utf8ToUtf16(entry.name).c_str());
        if ((num & msxll::xlSpecial) != 0)
          continue; // We don't cover the reverse map for the specials
        auto name = excelFuncName(entry.number);
        if (!name && ((num & msxll::xlCommand) != 0))
          continue; // We don't cover some of the higher numbered commands
        Assert::AreEqual(entry.name, excelFuncName(entry.number));
      }
    }
  };
}