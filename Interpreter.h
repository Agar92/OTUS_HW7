#pragma once

#include <fstream>
#include <stack>
#include <queue>

using std::string, std::ofstream, std::queue, std::stack;

enum class STATE
{
  EMPTY = 0, STATIC = 1, DYNAMIC = 2
};

class Interpreter
{
public:
  Interpreter(const size_t& batchSize) : batchSize(batchSize) {};
  void run();
  void process();
  void OpenLog();
  void WriteLog(const string& log);
  void CloseLog();
private:
  const string startOfBlock="{";
  const string endOfBlock  ="}";
  bool CmdIsStartOfBlock(const string& cmd);
  bool CmdIsEndOfBlock(const string& cmd);
  ofstream log;
  string logName;
  STATE state=STATE::EMPTY;
  const size_t batchSize;    
  queue<string> commands;
  stack<string> brackets;
};
