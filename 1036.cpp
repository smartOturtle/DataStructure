#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Student
{
	string name;
	string class_;
	int score;
	Student(const string& name,const string& class_,int score ):
	name(name),class_(class_),score(score)
	{ }
	bool operator <(const Student& student)const
	{
		return score < student.score;
	}
};
int main(int argc, char* argv[])
{
	int size;
	cin >> size;
	vector<Student> girls;
	vector<Student> boys;
	for (int i = 0; i < size; ++i)
	{
		string name;
		char sex;
		string class_;
		int score;
		cin >> name >> sex >> class_ >> score;
		if (sex == 'M')boys.emplace_back(name, class_, score);
		else { girls.emplace_back(name, class_, score); }
	}
	auto femaleHighest = max_element(girls.begin(), girls.end());
	if (girls.empty())cout << "Absent\n";
	else { cout << femaleHighest->name << " " << femaleHighest->class_<<'\n'; }
	auto maleLowest = min_element(boys.begin(), boys.end());
	if(boys.empty())cout << "Absent\n";
	else { cout << maleLowest->name << " " << maleLowest->class_<<'\n'; }
	if (boys.empty() || girls.empty())cout << "NA";
	else cout << femaleHighest->score - maleLowest->score;
}
