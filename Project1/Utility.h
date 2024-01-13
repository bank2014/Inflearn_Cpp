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
  static_assert(std::is_same<T, std::string>::value, "T가 문자열이 아닙니다");
  std::string inputStr;

  while (true) {
    cout << message;
    std::cin >> inputStr;

    // 공백 제거
    //inputStr.erase(std::remove_if(inputStr.begin(), inputStr.end(), [](unsigned char c) { return c == ' '; }), inputStr.end());

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "[ERROR] 잘못된 입력값: " << endl;
      continue;
    }
    break;
  }
  return inputStr;
}

template<typename T>
inline T Utility<T>::ReturnInt(std::string message)
{
  // T가 정수형일때만 동작
  static_assert(std::is_same<T, int32>::value ||
    std::is_same<T, int64>::value ||
    std::is_same<T, uint32>::value ||
    std::is_same<T, uint64>::value,
    "T가 정수형이 아닙니다");

  T returnValue{};
  std::string inputStr;
  bool isSigned = std::numeric_limits<T>::is_signed;

  while (true) {
    try {
      cout << message;
      std::cin >> inputStr;

      // 공백 제거
      //inputStr.erase(std::remove_if(inputStr.begin(), inputStr.end(), [](unsigned char c) { return c == ' '; }), inputStr.end());

      //signed인데 입력이 음수일 경우
      if (inputStr[0] == '-' && isSigned) {
        throw std::invalid_argument("음수는 입력할 수 없습니다");
      }
      // 숫자가 아닌 문자가 있으면 잘못된 입력값
      for (char c : inputStr) {
        if (!std::isdigit(c)) {
          throw std::invalid_argument("숫자가 아닌 문자가 있습니다");
        }
      }

      // 문자열을 숫자로 변환
      if (isSigned) {
        long long num = std::stoll(inputStr);
        if (num < std::numeric_limits<T>::min() || num > std::numeric_limits<T>::max()) {
          throw std::out_of_range("범위 초과");
        }
        returnValue = static_cast<T>(num);
      }
      else {
        unsigned long long num = std::stoull(inputStr);
        if (num < std::numeric_limits<T>::min() || num > std::numeric_limits<T>::max()) {
          throw std::out_of_range("범위 초과");
        }
        returnValue = static_cast<T>(num);
      }

      break;
    }
    catch (const std::exception& e) {
      cout << "[ERROR] 잘못된 입력값: " << e.what() << endl;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
  }

  return returnValue;
}
