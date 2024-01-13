template<typename T>
class Utility
{
public:
  static std::string ReturnString(std::string message);
  static T ReturnInt(std::string message);
};

template<typename T>
inline std::string Utility<T>::ReturnString(std::string message)
{
  static_assert(std::is_same<T, std::string>::value, "T�� ���ڿ��� �ƴմϴ�");
  std::string inputStr;

  while (true) {
    cout << message;
    std::cin >> inputStr;

    // ���� ����
    //inputStr.erase(std::remove_if(inputStr.begin(), inputStr.end(), [](unsigned char c) { return c == ' '; }), inputStr.end());

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "[ERROR] �߸��� �Է°�: " << endl;
      continue;
    }
    break;
  }
  return inputStr;
}

template<typename T>
inline T Utility<T>::ReturnInt(std::string message)
{
  // T�� �������϶��� ����
  static_assert(std::is_same<T, int32>::value ||
    std::is_same<T, int64>::value ||
    std::is_same<T, uint32>::value ||
    std::is_same<T, uint64>::value,
    "T�� �������� �ƴմϴ�");

  T returnValue{};
  std::string inputStr;
  bool isSigned = std::numeric_limits<T>::is_signed;

  while (true) {
    try {
      cout << message;
      std::cin >> inputStr;

      // ���� ����
      //inputStr.erase(std::remove_if(inputStr.begin(), inputStr.end(), [](unsigned char c) { return c == ' '; }), inputStr.end());

      //signed�ε� �Է��� ������ ���
      if (inputStr[0] == '-' && isSigned) {
        throw std::invalid_argument("������ �Է��� �� �����ϴ�");
      }
      // ���ڰ� �ƴ� ���ڰ� ������ �߸��� �Է°�
      for (char c : inputStr) {
        if (!std::isdigit(c)) {
          throw std::invalid_argument("���ڰ� �ƴ� ���ڰ� �ֽ��ϴ�");
        }
      }

      // ���ڿ��� ���ڷ� ��ȯ
      if (isSigned) {
        long long num = std::stoll(inputStr);
        if (num < std::numeric_limits<T>::min() || num > std::numeric_limits<T>::max()) {
          throw std::out_of_range("���� �ʰ�");
        }
        returnValue = static_cast<T>(num);
      }
      else {
        unsigned long long num = std::stoull(inputStr);
        if (num < std::numeric_limits<T>::min() || num > std::numeric_limits<T>::max()) {
          throw std::out_of_range("���� �ʰ�");
        }
        returnValue = static_cast<T>(num);
      }

      break;
    }
    catch (const std::exception& e) {
      cout << "[ERROR] �߸��� �Է°�: " << e.what() << endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
  }

  return returnValue;
}
