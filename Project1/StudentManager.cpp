#include "stdafx.h"
#include "StudentManager.h"

StudentManager::StudentManager()
{
  srand((uint32)time(0));
  recentEvent = Event::Nothing;
  exitFlag = false;
}

StudentManager::~StudentManager()
{
}

void StudentManager::Run()
{
	while (!exitFlag) {
		DisplayMenu();
		ProcessEvent();
	}
}

void StudentManager::ProcessEvent()
{
  switch (recentEvent)
  {
  case Event::Nothing:
    break;

  case Event::Print:
    PrintAll();
    break;

  case Event::Save:
    SaveFile();
    break;

  case Event::Load:
    LoadFile();
    break;

  case Event::Add:
    Add();
    break;

  case Event::Find:
    Find();
    break;

  case Event::Exit:
    exitFlag = true;
    break;

  case Event::GenerateRandom:
    GenerateRandomStudent();
    break;

  case Event::Sort:
    Sort();
    break;

  case Event::Delete:
    Delete();
    break;

  default:
    break;
  }
}

void StudentManager::DisplayMenu()
{
  recentEvent = Event::Nothing;
  auto input = Utility<uint32>::ReturnInt("[*] ���(1), ����(2), �ε�(3), ���(4), �˻�(5), ����(6), �л���������(7) ����(8) ����(9):");

  if (input >= static_cast<uint32>(Event::Nothing) && input <= static_cast<uint32>(Event::NumOfEvents)) {
    recentEvent = static_cast<Event>(input);
  }
  else {
    recentEvent = Event::Nothing;
  }
}

void StudentManager::Sort()
{
  if (list.size == 0) {
    cout << "[ERROR] ������ ������ ����" << endl;
    return;
  }

  DynamicArray<Student*> darr(list.size);
  for (decltype(list.size) i = 0; i < list.size; ++i) {
    darr.Pushback(list[i]->data);
  }
  SelectionSort::Sort(darr, darr.size);
  cout << "[*] - ID ������ ���� �Ϸ�" << endl;
  for (decltype(darr.size) i = 0; i < darr.size; ++i) {
    darr[i]->Print();
  }
}

void StudentManager::Find()
{
  auto input = Utility<uint32>::ReturnInt("[*] - ID�� �˻�(1) �̸����� �˻�(2)");

  if (input == 1) {
    auto input = Utility<uint32>::ReturnInt("[*] - �˻��� �л��� ID: ");

    for (decltype(list.size) i = 0; i < list.size; ++i) {
      if (list[i]->data->id == input) {
        list[i]->data->Print();
      }
    }
  }
  else if (input == 2) {
    auto input = Utility<std::string>::ReturnString("[*] - �˻��� �л��� �̸�: ");

    for (decltype(list.size) i = 0; i < list.size; ++i) {
      if (list[i]->data->name == input) {
        list[i]->data->Print();
      }
    }
  }
  else {
    cout << "[ERROR] �߸��� �Է°�" << endl;
  }
}

void StudentManager::Delete()
{
  auto input = Utility<uint32>::ReturnInt("[*] - ������ �л��� ID: ");

  for (decltype(list.size) i = 0; i < list.size; ++i) {
    if (list[i]->data->id == input) {
      list.Delete(i);
    }
  }
  cout << "[*] - �л� ���� �Ϸ�" << endl;
}

void StudentManager::Add()
{
  Student* newStudent = new Student();

  newStudent->name = Utility<std::string>::ReturnString("[*] - �л� �̸�: ");
  newStudent->id = Utility<uint32>::ReturnInt("[*] - �л� ID: ");
  newStudent->kor = Utility<uint32>::ReturnInt("[*] - ���� ����: ");
  newStudent->eng = Utility<uint32>::ReturnInt("[*] - ���� ����: ");
  newStudent->math = Utility<uint32>::ReturnInt("[*] - ���� ����: ");

  newStudent->CalTotalAndAvg();
  list.Pushback(*newStudent);
  cout << "[*] - " << newStudent->name << "�л� ��� �Ϸ�" << endl;
}

void StudentManager::PrintAll()
{
  cout
    << std::left << std::setw(14) << "ID"
    << std::left << std::setw(14) << "�̸�"
    << std::left << std::setw(8) << "����"
    << std::left << std::setw(8) << "����"
    << std::left << std::setw(8) << "����"
    << std::left << std::setw(8) << "����"
    << std::left << std::setw(8) << "���" << endl;
  cout << "----------------------------------------------------------------------------------" << endl;
  for (decltype(list.size) i = 0; i < list.size; ++i) {
    list[i]->data->Print();
  }
}

void StudentManager::SaveFile(const std::string fileName)
{
  if (list.size == 0) {
    cout << "[ERROR] ������ �����Ͱ� �����ϴ�." << endl;
    return;
  }

  FileIO file;
  if (file.SmartOpen(fileName.c_str(), "wb") == error) return;

  fwrite(&list.size, sizeof(list.size), 1, file.file_c);
  for (decltype(list.size) i = 0; i < list.size; ++i) {
    Student* temp = list[i]->data;
    temp->Serialize(file.file_c);
  }

  cout << "[*] - " << list.size << "�� ���� �Ϸ�" << endl;
}

void StudentManager::LoadFile(const std::string fileName)
{
  FileIO file;
  if (file.SmartOpen(fileName.c_str(), "rb") == error) return;

  list.Clear();

  uint32 listSize = 0;
  fread(&listSize, sizeof(listSize), 1, file.file_c);
  if (listSize == 0) {
    cout << "[ERROR] �ҷ��� �����Ͱ� �����ϴ�." << endl;
    return;
  }

  for (decltype(listSize) i = 0; i < listSize; ++i) {
    Student* temp = new Student();
    temp->Deserialize(file.file_c);
    list.Pushback(*temp);
  }

  cout << "[*] - " << list.size << "�� �ҷ����� �Ϸ�" << endl;
}

void StudentManager::GenerateRandomStudent()
{
  uint32 iter = Utility<uint32>::ReturnInt("[*] - �ڵ� ������ �л��� ��:");

  while (iter) {
    std::string name{"N/A"};
    for (int32 i = 0; i < 3; ++i) {
      name[i] = rand() % 26 + 65;
    }

    Student *newStudent = new Student(
      name,
      [](){ return static_cast<uint32>(rand() + 1); },  //id
      [](){ return static_cast<uint32>(rand() % 100 + 1); },    //kor
      [](){ return static_cast<uint32>(rand() % 100 + 1); },    //eng
      [](){ return static_cast<uint32>(rand() % 100 + 1); });   //math

    list.Pushback(*newStudent);
    --iter;
  }
}