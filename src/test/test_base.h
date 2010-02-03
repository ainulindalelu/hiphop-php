/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef __TEST_BASE_H__
#define __TEST_BASE_H__

#include <string>
#include <assert.h>
#include <lib/hphp.h>
#include <cpp/base/types.h>
#include <test/test.h>

using namespace HPHP;
///////////////////////////////////////////////////////////////////////////////

class TestBase {
 public:
  TestBase();
  virtual ~TestBase() {}

  virtual bool onTest() { return true;}
  virtual bool RunTests(const std::string &which) = 0;

 protected:
  bool Count(bool result);
  bool VerifySame(const char *exp1, const char *exp2,
                  CVarRef v1, CVarRef v2);
  bool VerifyClose(const char *exp1, const char *exp2,
                   double v1, double v2);
  bool array_value_exists(CVarRef var, CVarRef value);
};

///////////////////////////////////////////////////////////////////////////////
// macros

#define RUN_TEST(test)                                                  \
  if (!which.empty() && which != #test) {                               \
  } else if (onTest() && test()) {                                      \
    if (!Test::s_quiet) {                                               \
      printf(#test " passed\n");                                        \
    }                                                                   \
  } else {                                                              \
    printf(#test " failed\n");                                          \
    ret = false;                                                        \
  }                                                                     \

#define VERIFY(exp)                                                     \
  if (!(exp)) {                                                         \
    printf("%s:%d: [" #exp "] is false\n", __FILE__, __LINE__);         \
    return Count(false);                                                \
  }                                                                     \

#define VS(e1, e2)                                                      \
  if (!VerifySame(#e1, #e2, e1, e2)) {                                  \
    printf("%s:%d: VerifySame failed.\n", __FILE__, __LINE__);          \
    return Count(false);                                                \
  }                                                                     \

#define VC(e1, e2)                                                      \
  if (!VerifyClose(#e1, #e2, e1, e2)) {                                 \
    printf("%s:%d: VerifyClose failed.\n", __FILE__, __LINE__);         \
    return Count(false);                                                \
  }                                                                     \

///////////////////////////////////////////////////////////////////////////////

#endif // __TEST_BASE_H__
