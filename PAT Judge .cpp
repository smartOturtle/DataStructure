#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
vector<int> proList;
struct User
{
	int perfectNum{};
	int id;
	vector<int> problems;
	int score{};
	bool hasPassed{};
	User(int id_,int size):id(id_),problems(size,-2){}
	bool operator >(User const& one)const
	{
		if (score > one.score)return true;
		if(score==one.score)
		{
			if (perfectNum > one.perfectNum)return true;
			if (perfectNum == one.perfectNum)return id < one.id;
		}
		return false;
	}
	void Print(int rank)const
	{
		cout << rank << " ";
		printf("%05d %d", id + 1,score);
		for(auto partScore:problems)
		{
			if (partScore == -2)cout << " -";
			else if (partScore == -1)cout << " 0";
			else { cout << " " << partScore; }
		}
		cout << "\n";
	}
	void Submit(int proId,int partScore)
	{
		auto& thisProblem = problems[proId - 1];
		if (partScore >= 0)hasPassed = true;
		if(thisProblem<partScore)
		{
			if (thisProblem > 0)score += (partScore - thisProblem);
			else if(partScore>0){ score += partScore; }
			if (partScore == proList[proId - 1])perfectNum++;
			thisProblem = partScore;
		}
	}
};
vector<User> users;
void SortAndPrint()
{
	sort(users.begin(), users.end(), greater<User>());
	int rank = 1,offset=0,currentScore=users[0].score;
	for(auto& user:users)
	{
		if(!user.hasPassed)continue;
		if(user.score!=currentScore)
		{
			rank += offset;
			offset = 0;
			currentScore = user.score;
		}
		offset++;
		user.Print(rank);
	}
}
int main()
{
	int userSize,submSize,proSize;
	cin >>userSize >>proSize>>submSize;
	for (int i = 0; i < proSize; ++i)
	{
		int score;
		cin >> score;
		proList.push_back(score);
	}
	users.reserve(userSize);
	for (int i = 0; i < userSize; ++i)
		users.push_back({ i,proSize });
	for (int i = 0; i < submSize; ++i)
	{
		int id, proId, partScore;
		cin >> id >> proId >> partScore;
		users[id - 1].Submit(proId, partScore);
	}
	SortAndPrint();
}
