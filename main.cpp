#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<stack>
using namespace std;
struct Huffman
{
	/*
	This struct saving every character's occurrence number and it's Huffman code.
	*/
	int first;//occurrence number
	char second;//the character itself
	string third;//its Huffman code
};
class HuffmanNode
{
	friend class HuffmanTree;
public:
	HuffmanNode();
private:
	HuffmanNode* p_Parent, *p_LeftChild, *p_RightChild;
	 Huffman  Data;
};
HuffmanNode::HuffmanNode()
{
	p_Parent = NULL;
	p_LeftChild = NULL;
	p_RightChild = NULL;
}

class HuffmanTree
{
	/*
	note:
	You may find that Merge() is not used in this program,but i'm not gonna to delete it.
	*/
public:
	HuffmanTree();
	HuffmanNode* GetLeftChild(HuffmanNode* p);
	HuffmanNode* GetRightChild(HuffmanNode* p);
	HuffmanNode* GetParent(HuffmanNode* p);
	HuffmanNode* GetRoot();
	HuffmanTree* Merge(HuffmanNode* root1,HuffmanNode* root2,HuffmanNode* root);
	void SetNodeValue(HuffmanNode* p,  Huffman  data);
	void SetLeftChild(HuffmanNode* parent, HuffmanNode* leftChild);
	void SetRightChild(HuffmanNode* parent, HuffmanNode* rightChild);
	void SetRoot(HuffmanNode * newRoot);
	Huffman GetNodeValue(HuffmanNode* p);
private:
	HuffmanNode* p_Root;
};

HuffmanTree::HuffmanTree()
{
	p_Root = NULL;
}

HuffmanNode * HuffmanTree::GetLeftChild(HuffmanNode * p)
{
	return p->p_LeftChild;
}

HuffmanNode * HuffmanTree::GetRightChild(HuffmanNode * p)
{
	return p->p_RightChild;
}

HuffmanNode * HuffmanTree::GetParent(HuffmanNode * p)
{
	return p->p_Parent;
}

HuffmanNode * HuffmanTree::GetRoot()
{
	return p_Root;
}

HuffmanTree * HuffmanTree::Merge(HuffmanNode * root1, HuffmanNode * root2, HuffmanNode * root)
{
	root1->p_Parent = root;
	root2->p_Parent = root;
	root->p_LeftChild = root1;
	root->p_RightChild = root2;
	p_Root = root;
	return this;
}

void HuffmanTree::SetNodeValue(HuffmanNode*  p,  Huffman  data)
{
	p->Data = data;
}

void HuffmanTree::SetLeftChild(HuffmanNode * parent, HuffmanNode * leftChild)
{
	parent->p_LeftChild = leftChild;
	leftChild->p_Parent = parent;
}

void HuffmanTree::SetRightChild(HuffmanNode * parent, HuffmanNode * rightChild)
{
	parent->p_RightChild = rightChild;
	rightChild->p_Parent = parent;
}

void HuffmanTree::SetRoot(HuffmanNode* newRoot)
{
	p_Root = newRoot;
}

 Huffman  HuffmanTree::GetNodeValue(HuffmanNode * p)
{
	return p->Data;
}

bool wordInput(istream& input1, int times[])
{
	/*
	Input:A passage waiting to be coded in inputfile01.txt

	Output:An array times[] saving how many times that every character appears.

	ps:
	times[0] to times[25] saving 'a'to 'z',
	and times[26] to times[51] saving 'A'to 'Z'.
	*/
	char InputChar;
	while (input1)
	{
		InputChar = input1.get();
		if (InputChar >= 'a'&&InputChar <= 'z')
		{
			times[InputChar - 97]++;
		}
		if (InputChar >= 'A'&&InputChar <= 'Z')
		{
			times[InputChar - 39]++;
		}
	}
	return true;
}
bool createHuffman(Huffman Func[],HuffmanTree& Tree,HuffmanNode InputNode[])
{
	/*
	Input:
	An array of Huffman struct Func[52] 
	Empty HuffmanTree Tree (quotation called)
	Uninitialized array of HuffmanNode struct InputNode[103]

	Output:
	Filled HuffmanTree Tree
	Organized and filled array of HuffmanNode struct InputNode[103]

	ps£º
	InputNode[0] to InputNode[51] saves 'a'to'z' and 'A'to'Z' (leaf node)
	InputNode[52] to InputNode[102] saves ' '(if used) or '#'(if not used) 
	*/
	HuffmanNode *p1=InputNode, *p2;
	Huffman Init;//the initial value of InputNode.
	Init.first = 0;
	Init.second = '#';
	for (int i = 0; i < 103; i++)
	{
		Tree.SetNodeValue(p1, Init);
		p1++;
	}//Initialize InputNode
	p1 = InputNode;
	for (int i = 0; i < 52; i++)
	{
		Tree.SetNodeValue(p1, Func[i]);
		p1++;
	}//Fill InputNode
	HuffmanNode*count,*newElePos=InputNode+52;
	for (int i = 0; i < 52; i++)
	{
		p1 = NULL;
		p2 = NULL;
		for (int j = 0; j < 103; j++)
		{
			count = InputNode + j;
			if (Tree.GetNodeValue(count).second=='#')break;
			if (p1 == NULL)
			{
				if (Tree.GetNodeValue(count).first != 0 && Tree.GetParent(count) == NULL)
				{
					p1 = count;
				}
				else continue;
			}
			else if (p1 != NULL&&p2 == NULL)
			{
				if (Tree.GetNodeValue(count).first != 0 && Tree.GetParent(count) == NULL)
				{
					if (Tree.GetNodeValue(count).first < Tree.GetNodeValue(p1).first)
					{
						p2 = p1;
						p1 = count;
					}
					else 
					{ 
						p2 = count; 
					}
				}
				else continue;
			}
			else if (p1 != NULL&&p2 != NULL)
			{
				if (Tree.GetNodeValue(count).first != 0 && Tree.GetParent(count) == NULL)
				{
					if (Tree.GetNodeValue(count).first <= Tree.GetNodeValue(p1).first)
					{
						p2 = p1;
						p1 = count;
						break;
					}
				}
				else continue;
			}
		}//find two of the smallest elements in InputNode.
		if (p2 == NULL)
		{
			Tree.SetRoot(p1);
			break;
		}
		//if there hasn't two operating elements,set the last element to the tree's root,then break;
		Huffman InsertEle;
		InsertEle.first = Tree.GetNodeValue(p1).first + Tree.GetNodeValue(p2).first;
		InsertEle.second = ' ';
		Tree.SetNodeValue(newElePos, InsertEle);
		Tree.SetLeftChild(newElePos, p1);
		Tree.SetRightChild(newElePos, p2);
		newElePos++;
		//if there has two operating elements,conbine them and insert the new element to the InputNode[]
	}
	return true;
}
bool findCode(HuffmanTree& Tree, HuffmanNode* p)
{
	/*
	Input:
	HuffmanTree Tree(quotation called)
	HuffmanNode currentPtr p

	Output:
	Fill struct Huffman's third data(the code)

	ps:Like the binary tree's preorder traverse
	*/
	if (p == NULL)return true;
	if (p != Tree.GetRoot())
	{
		HuffmanNode* pParent = Tree.GetParent(p);
		Huffman nowCode = Tree.GetNodeValue(p);
		string parentCode = Tree.GetNodeValue(pParent).third;
		nowCode.third = parentCode;
		if (Tree.GetLeftChild(pParent) == p)
		{
			nowCode.third.push_back('0');
			Tree.SetNodeValue(p,nowCode);
		}
		else if (Tree.GetRightChild(pParent) == p)
		{
			nowCode.third.push_back('1');
			Tree.SetNodeValue(p, nowCode);
		}
	}
	findCode(Tree, Tree.GetLeftChild(p));
	findCode(Tree, Tree.GetRightChild(p));
	return true;
	
}
bool outputCode(ostream&output1, Huffman Func[])
{
	/*
	Input:
	An array of Huffman struct Func[]

	Output:
	Print every character's occurance number and Huffman code in outputfile01.txt
	*/
	for (int i = 0; i < 52; i++)
	{
		if (Func[i].first == 0)continue;
		else
		{
			output1 << Func[i].second << ' ' << Func[i].first << ' ' << Func[i].third << endl;
		}
	}
	return true;
}

bool Coding(istream& input1, ostream& output2, Huffman Func[])
{
	/*
	Input:
	An article waiting for coding in inputfile01.txt
	An array of struct Huffman

	Output:
	The coded article in inputfile02.txxt
	*/
	char InputChar;
	while (input1)
	{
		InputChar = input1.get();
		if (InputChar >= 'a'&&InputChar <= 'z')
		{
			output2<<Func[InputChar - 97].third;
		}
		else if (InputChar >= 'A'&&InputChar <= 'Z')
		{
			output2<<Func[InputChar - 39].third;
		}
		else
		{
			output2 << InputChar;
		}//like ',' '.' ' ' ,etc.
	}
	return true;
}
bool deCoding(istream& input2, ostream& output3, HuffmanTree& Tree)
{
	/*
	Input:The coded article in inputfile02.txt
	HuffmanTree Tree

	Output:
	The decoded article in outputfile02.txt
	*/
	HuffmanNode* p=Tree.GetRoot();
	char InputChar;
	while (input2)
	{
		InputChar = input2.get();
		if (InputChar == '0' || InputChar=='1')
		{
			if (InputChar == '0')
			{
				p = Tree.GetLeftChild(p);
			}
			else if (InputChar == '1')
			{
				p = Tree.GetRightChild(p);
			}
			if (Tree.GetNodeValue(p).second != ' ')//means the leaf node
			{
				output3 << Tree.GetNodeValue(p).second;
				p = Tree.GetRoot();
			}
			continue;
		}
		else
		{
			output3 << InputChar;
			continue;
		}
	}
	return true;
}
int main()
{
	bool OperSucc;//a symbol to point the success of every operation
	ifstream input1("inputfile01.txt");
	int times[52];
	for (int i = 0; i < 52; i++)times[i] = 0;
	wordInput(input1, times);
	input1.close();
	 Huffman Func[52];
	for (int i = 0; i < 52; i++)
	{
		if (i < 26)
		{
			Func[i].first = times[i];
			Func[i].second = (char)(i + 97);
		}
		else
		{
			Func[i].first = times[i];
			Func[i].second = (char)(i + 39);
		}
	}//filling the Func[]
	HuffmanTree Tree;
	HuffmanNode InputNode[103];//103 is the maximum number of this Huffman tree's element
	OperSucc = createHuffman(Func,Tree,InputNode);
	if (!OperSucc)
	{
		cout << "Creating Huffman Tree failed";
		return 0;
	}
	HuffmanNode* p = Tree.GetRoot();
	OperSucc = findCode(Tree, p);
	if (!OperSucc)
	{
		cout << "Creating Code list failed";
		return 0;
	}
	p = InputNode;
	for (int i = 0; i < 52; i++)
	{
		Func[i] = Tree.GetNodeValue(p);
		p++;
	}
	ofstream output1("outputfile01.txt");
	OperSucc=outputCode(output1, Func);
	if (!OperSucc)
	{
		cout << "Outputing Code list failed";
		return 0;
	}
	output1.close();
	ofstream output2("inputfile02.txt");
	ifstream input3("inputfile01.txt");
    OperSucc=Coding(input3, output2, Func);
	if (!OperSucc)
	{
		cout << "Coding article failed";
		return 0;
	}
	output2.close();
	ifstream input2("inputfile02.txt");
	ofstream output3("outputfile02.txt");
	OperSucc=deCoding(input2, output3, Tree);
	if (!OperSucc)
	{
		cout << "Decoding operation failed";
		return 0;
	}
	return 0;
}