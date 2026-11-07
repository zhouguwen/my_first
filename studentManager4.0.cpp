#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <windows.h>

using namespace std;

// =====================
// Student
// =====================

class Student
{
public:

    string name;
    int id;
    int score;

    Student()
    {
        name = "";
        id = 0;
        score = 0;
    }

    Student(string n, int i, int s)
    {
        name = n;
        id = i;
        score = s;
    }

    bool operator<(const Student& other) const
    {
        return id < other.id;
    }
};

// =====================
// operator<<
// =====================

ostream& operator<<(ostream& os, const Student& stu)
{
    os << "姓名: "
       << stu.name
       << " 学号: "
       << stu.id
       << " 成绩: "
       << stu.score;

    return os;
}

// =====================
// StudentManager
// =====================

class StudentManager
{
private:

    map<int, Student> students;

public:

    void addStudent()
    {
        string name;
        int id;
        int score;

        while (true)
        {
            cout << "\n请输入 姓名 学号 成绩 (输入0结束)\n";

            cin >> name;

            if (name == "0")
            {
                break;
            }

            cin >> id >> score;

            auto it = students.find(id);

            if (it != students.end())
            {
                cout << "学号重复，请重新输入\n";
                continue;
            }

            students.insert(
            {
                id,
                Student(name, id, score)
            });

            cout << "添加成功\n";
        }
    }

    void removeStudent()
    {
        int id;

        cout << "请输入要删除的学号:\n";
        cin >> id;

        auto it = students.find(id);

        if (it == students.end())
        {
            cout << "未找到该学生\n";
            return;
        }

        students.erase(it);

        cout << "删除成功\n";
    }

    void searchStudent()
    {
        int id;

        cout << "请输入学号:\n";
        cin >> id;

        auto it = students.find(id);

        if (it != students.end())
        {
            cout << it->second << endl;
        }
        else
        {
            cout << "未找到学生\n";
        }
    }

    void showStudents()
    {
        if (students.empty())
        {
            cout << "暂无学生信息\n";
            return;
        }

        for (const auto& item : students)
        {
            cout << item.second << endl;
        }
    }

    void sortByScore()
    {
        vector<Student> temp;

        for (const auto& item : students)
        {
            temp.push_back(item.second);
        }

        sort(
            temp.begin(),
            temp.end(),
            [](const Student& a, const Student& b)
            {
                return a.score > b.score;
            });

        cout << "\n===== 成绩排行榜 =====\n";

        for (const auto& stu : temp)
        {
            cout << stu << endl;
        }
    }

    void findExcellentStudent()
    {
        vector<Student> temp;

        for (const auto& item : students)
        {
            temp.push_back(item.second);
        }

        auto it =
            find_if(
                temp.begin(),
                temp.end(),
                [](const Student& stu)
                {
                    return stu.score >= 90;
                });

        if (it != temp.end())
        {
            cout << "\n找到优秀学生:\n";
            cout << *it << endl;
        }
        else
        {
            cout << "没有优秀学生\n";
        }
    }

    void countExcellentStudents()
    {
        vector<Student> temp;

        for (const auto& item : students)
        {
            temp.push_back(item.second);
        }

        int count =
            count_if(
                temp.begin(),
                temp.end(),
                [](const Student& stu)
                {
                    return stu.score >= 90;
                });

        cout << "优秀学生人数: "
             << count
             << endl;
    }

    void improveScores()
    {
        vector<Student> temp;

        for (const auto& item : students)
        {
            temp.push_back(item.second);
        }

        transform(
            temp.begin(),
            temp.end(),
            temp.begin(),
            [](Student stu)
            {
                if (stu.score < 60)
                {
                    stu.score += 10;
                }

                return stu;
            });

        cout << "\n===== 加分后结果 =====\n";

        for (const auto& stu : temp)
        {
            cout << stu << endl;
        }
    }
};

// =====================
// main
// =====================

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    StudentManager manager;

    int choice;

    while (true)
    {
        cout << "\n===== 学生管理系统4.0 =====\n";

        cout << "1.添加学生\n";
        cout << "2.删除学生\n";
        cout << "3.查询学生\n";
        cout << "4.显示所有学生\n";
        cout << "5.按成绩排序\n";
        cout << "6.查找第一个优秀学生\n";
        cout << "7.统计优秀学生人数\n";
        cout << "8.给不及格学生加10分\n";
        cout << "0.退出\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            manager.addStudent();
            break;

        case 2:
            manager.removeStudent();
            break;

        case 3:
            manager.searchStudent();
            break;

        case 4:
            manager.showStudents();
            break;

        case 5:
            manager.sortByScore();
            break;

        case 6:
            manager.findExcellentStudent();
            break;

        case 7:
            manager.countExcellentStudents();
            break;

        case 8:
            manager.improveScores();
            break;

        case 0:
            return 0;

        default:
            cout << "输入错误\n";
        }
    }

    return 0;
}