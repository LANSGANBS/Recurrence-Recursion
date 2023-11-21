#include <bits/stdc++.h>
#define endl '\n'
#define buff ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
using namespace std;
#define ll long long
#define int ll

struct Student
{
    string id;
    int age;
    string name;
    float score;
    string address;
    bool operator<(const Student &other) const
    {
        return score > other.score;
    }
};

signed main()
{
    int n;
    cin >> n;
    vector<Student> students;
    for (Student &s : students)
    {
        cout << "Enter student ID: ";
        cin >> s.id;
        cout << "Enter student age: ";
        cin >> s.age;
        cout << "Enter student name: ";
        cin >> s.name;
        cout << "Enter student score: ";
        cin >> s.score;
        cout << "Enter student address: ";
        cin >> s.address;
    }
    sort(students.begin(), students.end());
    for (const Student &s : students)
    {
        cout << "\nStudent Information:\n";
        cout << "ID: " << s.id << "\n";
        cout << "Age: " << s.age << "\n";
        cout << "Name: " << s.name << "\n";
        cout << "Score: " << s.score << "\n";
        cout << "Address: " << s.address << "\n";
    }
    return 0;
}