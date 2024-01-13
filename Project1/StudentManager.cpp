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
  auto input = Utility<uint32>::ReturnInt("[*] 출력(1), 저장(2), 로드(3), 등록(4), 검색(5), 종료(6), 학생랜덤생성(7) 정렬(8) 삭제(9):");

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
    cout << "[ERROR] 정렬할 데이터 없음" << endl;
    return;
  }

  DynamicArray<Student*> darr(list.size);
  for (decltype(list.size) i = 0; i < list.size; ++i) {
    darr.Pushback(list[i]->data);
  }
  SelectionSort::Sort(darr, darr.size);
  cout << "[*] - ID 순으로 정렬 완료" << endl;
  for (decltype(darr.size) i = 0; i < darr.size; ++i) {
    darr[i]->Print();
  }
}

void StudentManager::Find()
{
  auto input = Utility<uint32>::ReturnInt("[*] - ID로 검색(1) 이름으로 검색(2)");

  if (input == 1) {
    auto input = Utility<uint32>::ReturnInt("[*] - 검색할 학생의 ID: ");

    for (decltype(list.size) i = 0; i < list.size; ++i) {
      if (list[i]->data->id == input) {
        list[i]->data->Print();
      }
    }
  }
  else if (input == 2) {
    auto input = Utility<std::string>::ReturnString("[*] - 검색할 학생의 이름: ");

    for (decltype(list.size) i = 0; i < list.size; ++i) {
      if (list[i]->data->name == input) {
        list[i]->data->Print();
      }
    }
  }
  else {
    cout << "[ERROR] 잘못된 입력값" << endl;
  }
}

void StudentManager::Delete()
{
  auto input = Utility<uint32>::ReturnInt("[*] - 삭제할 학생의 ID: ");

  for (decltype(list.size) i = 0; i < list.size; ++i) {
    if (list[i]->data->id == input) {
      list.Delete(i);
    }
  }
  cout << "[*] - 학생 삭제 완료" << endl;
}

void StudentManager::Add()
{
  Student* newStudent = new Student();

  newStudent->name = Utility<std::string>::ReturnString("[*] - 학생 이름: ");
  newStudent->id = Utility<uint32>::ReturnInt("[*] - 학생 ID: ");
  newStudent->kor = Utility<uint32>::ReturnInt("[*] - 국어 점수: ");
  newStudent->eng = Utility<uint32>::ReturnInt("[*] - 영어 점수: ");
  newStudent->math = Utility<uint32>::ReturnInt("[*] - 수학 점수: ");

  newStudent->CalTotalAndAvg();
  list.Pushback(*newStudent);
  cout << "[*] - " << newStudent->name << "학생 등록 완료" << endl;
}

void StudentManager::PrintAll()
{
  cout
    << std::left << std::setw(14) << "ID"
    << std::left << std::setw(14) << "이름"
    << std::left << std::setw(8) << "국어"
    << std::left << std::setw(8) << "영어"
    << std::left << std::setw(8) << "수학"
    << std::left << std::setw(8) << "총점"
    << std::left << std::setw(8) << "평균" << endl;
  cout << "----------------------------------------------------------------------------------" << endl;
  for (decltype(list.size) i = 0; i < list.size; ++i) {
    list[i]->data->Print();
  }
}

void StudentManager::SaveFile(const std::string fileName)
{
  if (list.size == 0) {
    cout << "[ERROR] 저장할 데이터가 없습니다." << endl;
    return;
  }

  FileIO file;
  if (file.SmartOpen(fileName.c_str(), "wb") == error) return;

  fwrite(&list.size, sizeof(list.size), 1, file.file_c);
  for (decltype(list.size) i = 0; i < list.size; ++i) {
    Student* temp = list[i]->data;
    temp->Serialize(file.file_c);
  }

  cout << "[*] - " << list.size << "명 저장 완료" << endl;
}

void StudentManager::LoadFile(const std::string fileName)
{
  FileIO file;
  if (file.SmartOpen(fileName.c_str(), "rb") == error) return;

  list.Clear();

  uint32 listSize = 0;
  fread(&listSize, sizeof(listSize), 1, file.file_c);
  if (listSize == 0) {
    cout << "[ERROR] 불러올 데이터가 없습니다." << endl;
    return;
  }

  for (decltype(listSize) i = 0; i < listSize; ++i) {
    Student* temp = new Student();
    temp->Deserialize(file.file_c);
    list.Pushback(*temp);
  }

  cout << "[*] - " << list.size << "명 불러오기 완료" << endl;
}

void StudentManager::GenerateRandomStudent()
{
  uint32 iter = Utility<uint32>::ReturnInt("[*] - 자동 생성할 학생의 수:");

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