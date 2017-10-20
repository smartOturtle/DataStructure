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
	explicit  Node(int d, int w,Node*l=nullptr,Node*r=nullptr) :data(d), weight(w),left(l),right(r) {}
	bool IsLeaf()const { return left == nullptr&&right == nullptr; }
	constexpr static int not_char = -1;
};
using CharFreqTable = priority_queue<Node*,vector<Node*>,function<bool (Node*,Node*)>>;
class Huffman
{
	int total_length_{};
	unordered_map<char, pair<string,int>> code_table_;
	void BuildCode(Node*n,string s)
	{
		if(n->IsLeaf())
		{
			code_table_.insert({ static_cast<char>(n->data),{ s,n->weight } });
			total_length_ += s.length()*n->weight;
			return;
		}
		BuildCode(n->left, s + '0');
		BuildCode(n->right, s + '1');
	}
public:
	explicit Huffman(CharFreqTable& table)
	{
		while (table.size()>1)
		{
			auto temp{ table.top() };
			table.pop();
			auto parent{ new Node{ Node::not_char,table.top()->weight + temp->weight,temp,table.top() } };
			table.pop();
			table.push(parent);
		}
		BuildCode(table.top(), {});
	}
	int GetTotalLength() const { return total_length_; }
	const decltype(code_table_)& GetCodeTable() const { return code_table_; }
};
int main()
{
	int charCount,submCount;
	cin >> charCount;
	CharFreqTable table([](Node* one, Node* other) { return one->weight > other->weight; });
	for (int i = 0; i < charCount; ++i)
	{
		char c;
		int fre;
		cin >> c >> fre;
		table.push(new Node( c,fre ));
	}
	Huffman huffman(table);
	cin >> submCount;
	for (int i = 0; i < submCount; ++i)
	{
		int length{};
		bool hasSamePre{ false };
		vector<string> vs;
		vs.reserve(charCount);
		for (int j = 0; j < charCount; ++j)
		{
			char c;
			string s;
			cin >> c >> s;
			for(const auto& x:vs)
			{
				if(s.size()<=x.size()&&s[0] == x[0] && x.find(s) == 0)
				{ 
					hasSamePre = true;
					break; 
				}
			}
			vs.push_back(s);
			length += huffman.GetCodeTable().at(c).second*s.size();
		}
		if (length==huffman.GetTotalLength()&&!hasSamePre)cout << "Yes\n";
		else { cout << "No\n"; }
	}
}
