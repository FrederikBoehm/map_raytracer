#ifndef PERFORMANCE_MONITORING_HPP
#define PERFORMANCE_MONITORING_HPP

#define TIME_MONITORING

#include <chrono>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_set>

namespace rt {
  class CPerformanceMonitoring {

    CPerformanceMonitoring() = delete;

  public:
    static void startMeasurement(const std::string&& name) {
#ifdef TIME_MONITORING
      auto time = s_clock.now();
      if (s_currentMeasurements.find(name) == s_currentMeasurements.end()) {
        s_currentMeasurements[name] = time;
      }
#endif // TIME_MONITORING
    }

    static void endMeasurement(const std::string&& name) {
#ifdef TIME_MONITORING
      auto time = s_clock.now();
      if (s_currentMeasurements.find(name) != s_currentMeasurements.end()) {
        std::chrono::duration<double> diff = time - s_currentMeasurements[name];
        s_durations.insert({ name, diff.count() });
        s_currentMeasurements.erase(name);
      }
#endif // TIME_MONITORING
    }

    static std::string toString() {
      std::string output = "";
#ifdef TIME_MONITORING
      std::unordered_set<std::string> keys;
      for (auto it = s_durations.cbegin(); it != s_durations.cend(); ++it) {
        keys.insert(it->first);
      }

      std::ostringstream out;
      out.precision(10);
      for (auto& key : keys) {
        auto range = s_durations.equal_range(key);
        double a = avg(range.first, range.second);
        double s = stdDev(range.first, range.second, a);
        out << std::fixed << a << "," << s;
        output += key + "," + out.str() + "\n";
        out.str("");
        out.clear();
      }
#endif // TIME_MONITORING
      return output;
    }


  private:
    static std::chrono::steady_clock s_clock;
    static std::unordered_map<std::string, std::chrono::time_point<std::chrono::steady_clock>> s_currentMeasurements;
    static std::multimap<std::string, double> s_durations;

    static double avg(std::multimap<std::string, double>::iterator begin, std::multimap<std::string, double>::iterator end) {
      double average = 0.0f;
      size_t count = 0;
      for (auto& it = begin; it != end; ++it) {
        average += it->second;
        ++count;
      }
      return average /= count;
    }

    static double stdDev(std::multimap<std::string, double>::iterator begin, std::multimap<std::string, double>::iterator end, double avg) {
      double variance = 0.0f;
      size_t count = 0;
      for (auto& it = begin; it != end; ++it) {
        double diff = it->second - avg;
        variance += diff * diff;
        ++count;
      }
      return std::sqrt(variance / (count - 1));
    }
  };

}
#endif // !PERFORMANCE_MONITORING_HPP
