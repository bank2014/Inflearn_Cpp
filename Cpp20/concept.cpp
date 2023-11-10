#include <iostream>

using namespace std;

/*################################
			Concept
################################*/
// T의 허용가능한 범위를 설정

class GameObject
{

};

class Knight : public GameObject
{

};


/*################################
	사용자 정의 concept
################################*/

template<typename name_t>
concept MyConcept = !std::is_integral_v<name_t> && std::derived_from<name_t, GameObject>;

template<typename name_t>
concept Addable = requires (name_t a, name_t b)
{
	a + b;
};

template<typename name_t>
concept Comparable = requires (name_t a, name_t b)
{
	{ a == b } -> std::convertible_to<bool>;
	{ a != b } -> std::convertible_to<bool>;
};


/*################################
	concept 사용예시 종류
################################*/

// 1. Require 절
template<typename name_t>
requires std::integral<name_t> 
void TestInt(name_t number)
{
	cout << number << "\n";
}

// 2. Trailing requires 절
template<typename name_t>
void TestInt2(name_t number) requires std::integral<name_t>
{
	cout << number << endl;
}

// 3. Constrained Template parameter
template<std::integral name_t>
void TestInt3(name_t number)
{
	cout << number << endl;
}

// 4. Abbreviated Function template 
void TestInt4(std::integral auto number)
{
	cout << number << endl;
}


int main()
{
	std::ios::sync_with_stdio(false);

	TestInt(3);
	TestInt2(3);
	TestInt3(3);
	TestInt4(3);
	
	constexpr bool check = _Is_any_of_v<int, short, int, long long>;

}
