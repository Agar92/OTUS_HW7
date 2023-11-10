#include "Interpreter.h"

int main(int argc, char* argv[])
{
  if(argc==2)
  {
    const int bulkSize = std::atoi(argv[1]);
    if(bulkSize>0)
    {
      Interpreter interpreter(bulkSize);
      interpreter.run();
    }
  }
  return 0;
}
