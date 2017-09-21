#include <stdio.h>
#include <string.h>

#ifndef MAIN_C
  #define MAIN_C

  // ================= DEFINITIONS ====================
  //processes 0-15 with three on each
  #define SCHEDULER_MAX_PROCESSES 48
  #define PRIORITY_LEVELS 16 // 0 -15
  #define TIME_QUANTUM 8

  // ================= TYPEDEFS ====================

  // ================= PROTOTYPES ====================
  int main(int argc, char* argv[]);
  void createProcess();
  char hasProcesses();
  void swapProcesses();
  void executeActiveProcess();
  void ageProcesses();
#endif
