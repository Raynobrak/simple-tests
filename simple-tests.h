//
// Created by lcsch on 28.03.2023.
//

#ifndef SIMPLE_TESTS_SIMPLE_TESTS_H
#define SIMPLE_TESTS_SIMPLE_TESTS_H

#include <string>
#include <ostream>

enum class VerbosityLevel {
   All,
   FailedOnly
};

class TestGroup {
private:
   static const char LINE_CHAR = '=';
   static constexpr std::string_view HALF_LINE = "=========================";
public:
   TestGroup(std::ostream& outputStream, VerbosityLevel verbosity = VerbosityLevel::All)
       : os_(outputStream),
         verbosityLevel_(verbosity),
         totalTestsCount_(0),
         failedCount_(0) {}

   void print_test_summary() {
      os_ << "[TESTS SUMMARY] : " << totalTestsCount_ - failedCount_ << "/" << totalTestsCount_ << " tests passed." << std::endl;
      os_ << HALF_LINE << LINE_CHAR << "[ Results end ]" << LINE_CHAR << HALF_LINE << std::endl;
   }

   void print_line(std::string text) {
      if(totalTestsCount_ == 1) { // Print summary header if first output
         os_ << HALF_LINE << "[ Tests results ]" << HALF_LINE << std::endl;
      }
      os_ << text << std::endl;
   }

   void print_test_result(std::string testLabel, bool passed) {
      if(!passed || verbosityLevel_ == VerbosityLevel::All)
         print_line("[" + testLabel + "] : " + std::string(passed ? "PASSED" : "FAILED"));
   }

   void assert_true(std::string testLabel, bool condition) {
      ++totalTestsCount_;
      if(!condition)
         ++failedCount_;

      print_test_result(testLabel, condition);
   }

   void assert_equal(std::string testLabel, const auto& result, const auto& expected) {
      assert_true(testLabel, result == expected);
   }
private:
   VerbosityLevel verbosityLevel_;

   std::size_t totalTestsCount_;
   std::size_t failedCount_;

   std::ostream& os_;
};

#endif//SIMPLE_TESTS_SIMPLE_TESTS_H
