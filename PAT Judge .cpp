#include<iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
struct Test
{
    vector<int> perfectScore;
    explicit Test(vector<int> perfectScores):perfectScore(perfectScores){}
    vector<int> GetProblems() const { return vector<int>(perfectScore.size(),-1); }
    bool IsPerfect(int problemId, int score)const { return perfectScore[problemId] == score; }
};
struct User
{
    Test* test;
    int userId;
    int perfectSize = 0;
    int totalScore = 0;
    bool hasPassed = false;
    vector<int> problems;
    User(Test* test, int userId) :test(test), userId(userId), problems(test->GetProblems()) {}
};
struct RankList
{
    vector<User> users;
    unordered_map<int, int> userIdToIdx;
    Test test;
    explicit RankList(vector<int> perfectScores):test(move(perfectScores)){}
    int GetInnerIdx(int userId)
    {
        if(userIdToIdx.find(userId)==userIdToIdx.end())
        {
            users.emplace_back(&test, userId);
            userIdToIdx[userId] = users.size() - 1;
        }
        return userIdToIdx[userId];
    }
    void Update(int userId,int problemId,int score)
    {
        auto& user = users[GetInnerIdx(userId)];
        user.problems[problemId] = max(0, user.problems[problemId]);
        if (score >= 0)user.hasPassed = true;
        if (score > user.problems[problemId])
        {
            user.totalScore += score - user.problems[problemId];
            user.problems[problemId] = score;
            if (test.IsPerfect(problemId, score))user.perfectSize++;
        }
    }

    static bool GreaterThan(const User& lhs,const User& rhs)
    {
        if(lhs.totalScore==rhs.totalScore)
        {
            if (lhs.perfectSize == rhs.perfectSize)return lhs.userId < rhs.userId;
            return lhs.perfectSize > rhs.perfectSize;
        }
        return lhs.totalScore > rhs.totalScore;
    }
    void Print()
    {
        sort(users.begin(), users.end(), &GreaterThan);
        int rank = 1;
        int preScore = -1;
        int sameSize=0;
        for (auto& user : users)
        {
            if(!user.hasPassed)continue;
            if(user.totalScore!=preScore)
            {
                rank += sameSize;
                sameSize = 1;
                preScore = user.totalScore;
            }
            else sameSize++;
            printf("%d %05d %d", rank, user.userId,user.totalScore);
            for (auto score : user.problems)
            {
                cout << ' ';
                if (score == -1)cout << '-';
                else { cout << score; }
            }
            cout << '\n';
        }
    }
};

int main(int argc, char* argv[])
{
    int userSize;
    int problemSize;
    int commitSize;
    cin >> userSize >> problemSize >> commitSize;
    vector<int> perfectScores(problemSize);
    for (auto& value : perfectScores)cin >> value;
    RankList rankList(perfectScores);
    for (int i = 0; i < commitSize; ++i)
    {
        int userId, problemId, score;
        cin >> userId >> problemId >> score;
        rankList.Update(userId, problemId - 1, score);
    }
    rankList.Print();
}
