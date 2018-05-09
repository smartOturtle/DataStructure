#include <iostream>
#include <functional>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
struct Node
{
    int data;
    int weight;
    Node* left{};
    Node* right{};
    explicit  Node(int d, int w, Node*l = nullptr, Node*r = nullptr) :data(d), weight(w), left(l), right(r) {}
    bool IsLeaf()const { return left == nullptr&&right == nullptr; }
    constexpr static int not_char = -1;
};
using PriorityQueue = priority_queue<Node*, vector<Node*>, function<bool(Node*, Node*)>>;
class Huffman
{
    int total_length_{};
    void BuildCode(Node*n, string s)
    {
        if (n->IsLeaf())
        {
            charCodeFreqMap.insert({ static_cast<char>(n->data),{ s,n->weight } });
            total_length_ += s.length()*n->weight;
            return;
        }
        BuildCode(n->left, s + '0');
        BuildCode(n->right, s + '1');
    }
public:
    unordered_map<char, pair<string, int>> charCodeFreqMap;
    explicit Huffman(PriorityQueue& table)
    {
        while (table.size()>1)
        {
            auto first{ table.top() };
            table.pop();
            auto parent{ new Node{ Node::not_char,table.top()->weight + first->weight,first,table.top() } };
            table.pop();
            table.push(parent);
        }
        BuildCode(table.top(), {});
    }
    int GetTotalLength() const { return total_length_; }
};
int main()
{
    int charCount, submCount;
    cin >> charCount;
    PriorityQueue table([](Node* one, Node* other) { return one->weight > other->weight; });
    for (int i = 0; i < charCount; ++i)
    {
        char c;
        int fre;
        cin >> c >> fre;
        table.push(new Node(c, fre));
    }
    Huffman huffman(table);
    cin >> submCount;
    for (int i = 0; i < submCount; ++i)
    {
        int length{};
        bool hasSamePre{ false };
        vector<string> vs;
        for (int j = 0; j < charCount; ++j)
        {
            char c;
            string s;
            cin >> c >> s;
            for (auto& x : vs)
            {
                auto* longer = &s;
                auto* shorter = &x;
                if (longer->size() < shorter->size())swap(longer, shorter);
                if (mismatch(shorter->begin(),shorter->end(),longer->begin()).first==shorter->end())
                {
                    hasSamePre = true;
                    break;
                }
            }
            vs.push_back(s);
            length += huffman.charCodeFreqMap[c].second*s.size();
        }
        if (length == huffman.GetTotalLength() && !hasSamePre)cout << "Yes\n";
        else { cout << "No\n"; }
    }
}
