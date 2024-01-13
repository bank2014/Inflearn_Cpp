#pragma once
#include "Student.h"
#include "LinkedList.h"
#include "FileIO.h"
#include "Utility.h"
#include "DynamicArray.h"
#include "SelectionSort.h"

enum class Event : uint32 {
  Nothing = 0,
  Print,
  Save,
  Load,
  Add,
  Find,
  Exit,
  GenerateRandom,
  Sort,
  Delete,
  NumOfEvents
};

class StudentManager
{
private:
  LinkedList<Student> list;
  Event recentEvent;
  bool exitFlag;

public:
  StudentManager();
  ~StudentManager();

  void Run();
  void ProcessEvent();
  void DisplayMenu();
  void PrintAll();
  void Sort();
  void Find();
  void Delete();
  void Add();
  void SaveFile(const std::string fileName = "save");
  void LoadFile(const std::string fileName = "save");
  void GenerateRandomStudent();
};

