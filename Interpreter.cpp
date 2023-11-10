#include "Interpreter.h"

#include <iostream>
#include <sstream>

using std::getline, std::stringstream, std::cout, std::endl;

void Interpreter::run()
{
  string cmd;
  while(getline(std::cin, cmd))
  {
    if(CmdIsStartOfBlock(cmd))
    {            
      brackets.push(startOfBlock);
      OpenLog();
      if(state==STATE::EMPTY)
        state=STATE::DYNAMIC;
      if(state==STATE::STATIC)
      {
        process();
        state=STATE::DYNAMIC;
      } 
    }
    else if(CmdIsEndOfBlock(cmd))
    {
      if(state==STATE::EMPTY)
        commands.push(endOfBlock);
      if(state==STATE::STATIC)
      {
        commands.push(endOfBlock);
        if(commands.size()==batchSize) process();
      }
      if(state==STATE::DYNAMIC)
      {
        brackets.pop();
        if(brackets.size()==0)
        {
          process();
          state=STATE::EMPTY;
        }
      }   
    }
    else 
    {
      if(state==STATE::EMPTY)
      {
        OpenLog();
        commands.push(cmd);
        state=STATE::STATIC;
      }
      else if(state==STATE::STATIC)
      {
        commands.push(cmd);
        if(commands.size()==batchSize) process();
      }
      else
        commands.push(cmd);
    }
  }
  if(state==STATE::STATIC)
    process();
  else if(state==STATE::DYNAMIC)
    CloseLog();
}

void Interpreter::process()
{
  stringstream ss;
  if(!commands.empty()) 
  {
    ss<<"bulk: ";
    while(!commands.empty()) 
    {
      ss<<commands.front();
      commands.pop();
      if(!commands.empty()) ss<<", ";
    }
    ss<<endl;
  }
  WriteLog(ss.str());
  cout<<ss.str();
}

void Interpreter::OpenLog()
{
  auto Time=time(nullptr);
  stringstream ss;
  ss<<"bulk"<<Time<<".log";
  logName=ss.str();
}

void Interpreter::CloseLog()
{
  if(log.is_open()) log.close();
}

void Interpreter::WriteLog(const string& logmessage)
{
  log.open(logName);
  if(log.is_open()) log<<logmessage;
  else throw "Error! Unable to open log file!";    
}

bool Interpreter::CmdIsStartOfBlock(const string& cmd)
{
  return (cmd==startOfBlock);
}

bool Interpreter::CmdIsEndOfBlock(const string& cmd)
{
  return (cmd==endOfBlock);
}

