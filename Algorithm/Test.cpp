#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <iostream>

using namespace std;

string findWord(const string& str, const int which)
{
    if (which == 1) {
        auto idx = str.find(' ');
        return str.substr(0, idx);
    }
    if (which == 2) {
        return str.substr(idx1 + 1, idx2);
    }
    if (which == 3) {
        return str.substr(idx2 + 1, idx3);
    }

    return "ERROR";
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    map<string, string> id_nick;

    for (auto iter = record.rbegin(); iter != record.rend(); ++iter)
    {
        string action = findWord(*iter, 1);
        string id = findWord(*iter, 2);
        string nickname = findWord(*iter, 3);

        // Change�� ��� & ó�� �߰��� id�� ��� 
        if (action == "Change" && id_nick[id] == "")
        {
            // ���̵�� �ֽ� ���� �ӽ������Ѵ�
            id_nick[id] = nickname;
        }
    }

    // ����
    for (auto iter = record.begin(); iter != record.end(); ++iter) {
        string action = findWord(*iter, 1);
        string id = findWord(*iter, 2);

        if (action == "Enter") {
            answer.emplace_back(id_nick[id] + "���� ���Խ��ϴ�.");
        }
        else if (action == "Leave") {
            answer.emplace_back(id_nick[id] + "���� �������ϴ�.");
        }
        else if (action == "Change") {
            continue;
        }
    }

    return answer;
}

int main() {
    vector<string> record = { "Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan" };
    vector<string> answer = solution(record);

    for (auto& e : answer)
    {
        cout << e << " ";
    }

    return 0;
}
