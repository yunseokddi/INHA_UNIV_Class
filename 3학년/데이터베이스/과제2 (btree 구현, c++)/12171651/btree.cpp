#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#define real_block_size(block_size) (block_size-4)/8
#define real_block_location(BID, block_size) (12+((BID-1) * block_size))

using namespace std;

class Block;
class Entry;
class Btree;

string bin_file_name;
int blocksize;
int root_BID;
int depth;
string output;

class Entry
{
public:
	int key;
	int BID;
	int value;
	int parent_BID;


	Entry()
	{
		key = 0;
		BID = 0;
		value = 0;
	}


	friend class Block;
	friend class Btree;
};

class Block
{
public:
	int next_id;
	int next_level_id;
	bool check_leaf; //leaf block인지 non leaf block인지 확인
	int block_id;
	Block* parent;
	Entry *entry;
	int parent_BID;


	Block(int block_size)
	{
		parent = NULL;
		check_leaf = false;
		next_id = 0;
		next_level_id = 0;
		parent_BID = 0;
		entry = new Entry[real_block_size(blocksize)];
		block_id = 0;
	}

	bool block_full() //entry가 full인지 확인 
	{
		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			if (entry[i].key == 0)
			{
				return false;
			}
		}
		return true;
	}
	
	bool insert_leaf_entry(int key, int value) {
		for (int i = 0; i < real_block_size(blocksize); ++i) {
			if (this->entry[i].key == 0) {
				this->entry[i].key = key;
				this->entry[i].value = value;
			\
				break;
			}
		}
		return true;
	}

	bool insert_non_leaf_entry(int key, int BID) {
		for (int i = 0; i < real_block_size(blocksize); ++i) {
			if (this->entry[i].key == 0) {
				this->entry[i].key = key;
				this->entry[i].BID = BID;
			
				break;
			}
		}
		return true;
	}


	friend class BTree;
};





class BTree
{
	
public:
	
	const char *fileName;
	Block *root;
	vector<Block*> parent_path;

	
	
	BTree(const char *fileName, int blocksize)
	{
		this->fileName = fileName;
	}

	Block* root_block_read(int root_BID)
	{
		ifstream read(bin_file_name, ios::in | ios::binary);
		read.seekg(real_block_location(root_BID, blocksize),ios::beg);
		root = new Block(blocksize);
		root->block_id = root_BID;

		if (depth == 0) //root가 leaf인 경우
		{
			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				read.read(reinterpret_cast<char*>(&root->entry[i].key), sizeof(int));
				read.read(reinterpret_cast<char*>(&root->entry[i].value), sizeof(int));
			}

			read.read(reinterpret_cast<char*>(&root->next_id), sizeof(int));

			root->check_leaf = true;
			
		}

		else //root가 non_leaf인 경우
		{
			read.read(reinterpret_cast<char*>(&root->next_level_id), sizeof(int));

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				read.read(reinterpret_cast<char*>(&root->entry[i].key), sizeof(int));
				read.read(reinterpret_cast<char*>(&root->entry[i].BID), sizeof(int));
			}


			root->check_leaf = false;
		}

		read.close();

		return root;
	}

	Block* return_block(Block *parent, int BID, int depth_counter) //block이 leaf인지 non_leaf인지 확인
	{
		ifstream read(bin_file_name, ios::in | ios::binary);
		read.seekg(real_block_location(BID, blocksize), ios::beg);
		Block *target = new Block(blocksize);

		target->block_id = BID;

		if (depth_counter == depth) //block이 leaf인 경우
		{
			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				read.read(reinterpret_cast<char*>(&target->entry[i].key), sizeof(int));
				read.read(reinterpret_cast<char*>(&target->entry[i].value), sizeof(int));
			}

			read.read(reinterpret_cast<char*>(&target->next_id), sizeof(int));

			target->check_leaf = true;

		}

		else //block이 non_leaf인 경우
		{
			read.read(reinterpret_cast<char*>(&target->next_level_id), sizeof(int));

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				read.read(reinterpret_cast<char*>(&target->entry[i].key), sizeof(int));
				read.read(reinterpret_cast<char*>(&target->entry[i].BID), sizeof(int));
			}


			target->check_leaf = false;
		}

		read.close();
		target->parent_BID = parent->block_id;
		target->parent = parent;
		return target;
	}

	int seek_last_BID() //마지막으로 쓰인 block id 확인 
	{
		ifstream open(bin_file_name, ios::in | ios::binary);
		open.seekg(0, ios::end);
		
		int last_block_ID = ((int)open.tellg()-12)/blocksize;

		open.close();

		return last_block_ID;

	}


	bool insert(int key, int rid)
	{
		
		Block* leaf_block;
		int depth_counter = 0;
		leaf_block = root_block_read(root_BID);
		root = leaf_block;
		int leaf_block_BID = root_BID;
		parent_path.clear();

		parent_path.push_back(root);

		while (!leaf_block->check_leaf) //leaf blcok까지 내려가기
		{
			for (int i = 0; i < real_block_size(blocksize); i++) 
			{
				if (key < leaf_block->entry[i].key) //해당 entry보다 key값이 작은 경우
				{
					if (i == 0) //해당 key가 해당 block에 첫번째 entry의 key값보다 작은 경우
					{
						leaf_block = return_block(leaf_block, leaf_block->next_level_id, ++depth_counter);
						leaf_block_BID = leaf_block->next_level_id;
						parent_path.push_back(leaf_block);
					}

					else //해당 key가 해당 block에 첫번째 entry의 key값보다 큰 경우
					{
						leaf_block = return_block(leaf_block, leaf_block->entry[i-1].BID, ++depth_counter);
						leaf_block_BID = leaf_block->entry[i - 1].BID;
						parent_path.push_back(leaf_block);
					}
				}

				else if(leaf_block->entry[i].key == 0)
				{
					leaf_block = return_block(leaf_block, leaf_block->entry[i - 1].BID, ++depth_counter);
					leaf_block_BID = leaf_block->entry[i - 1].BID;
					parent_path.push_back(leaf_block);
				}
			}
		}

		if (leaf_block->block_full()) //leaf block이 꽉차면 split이 일어남
		{
			leaf_block = leaf_split(leaf_block, key);
		}

		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			if (leaf_block->entry[i].key == 0)
			{
				leaf_block->entry[i].key = key;
				leaf_block->entry[i].value = rid;
				break;
			}
		}
		int counter = 0;

		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			if (leaf_block->entry[i].key != 0)
			{
				counter++;
			}
		}

		for (int i = counter - 1; i > 0; i--)
		{
			if (leaf_block->entry[i - 1].key > leaf_block->entry[i].key)
			{
				swap(leaf_block->entry[i], leaf_block->entry[i - 1]);
			}
		}


		fstream open(bin_file_name, ios::in | ios::out | ios::binary);
		open.seekp(real_block_location(leaf_block->block_id, blocksize), ios::beg);


		for (int i = 0; i < real_block_size(blocksize); i++) {
			cout << leaf_block->entry[i].key << " " << leaf_block->entry[i].value << " / ";
		}
		cout << leaf_block->next_id << endl;


		cout << real_block_location(leaf_block_BID, blocksize) << " " << real_block_size(blocksize) << endl;
		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			open.write(reinterpret_cast <char*>(&leaf_block->entry[i].key), sizeof(int));
			open.write(reinterpret_cast <char*>(&leaf_block->entry[i].value), sizeof(int));
	
		}

		open.write(reinterpret_cast <char*>(&leaf_block->next_id), sizeof(int));

		open.close();
		return true;
	}

	Block *non_leaf_split(Block* block, int key)
	{
		Block *parent = block->parent;
		Block *left_block = new Block(blocksize);
		Block *right_block = new Block(blocksize);

		left_block->parent_BID = block->parent_BID;
		right_block->parent_BID = block->parent_BID;

		left_block->check_leaf = false;
		right_block->check_leaf = false;

		right_block->block_id = seek_last_BID() + 1;
		left_block->next_level_id = block->next_level_id;




		if (real_block_size(blocksize) % 2 == 0) //entry 개수가 짝수일때
		{
			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				if (i < real_block_size(blocksize) / 2)
				{
					left_block->entry[i] = block->entry[i]; //left에 할당


				}

				else
				{
					right_block->entry[i] = block->entry[i]; //right에 할당
				}
			}
		}

		else //entry 개수가 홀수일때
		{
			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				if (i < real_block_size(blocksize) / 2)
				{
					left_block->entry[i] = block->entry[i]; //left에 할당
				}

				else
				{
					right_block->entry[i] = block->entry[i];  //right에 할당
				}
			}
		}

		int first_right_key = 0;

		for (int i = 0; i < real_block_size(blocksize)-1; i++)
		{
			if (i = 0)
			{
				first_right_key = right_block->entry[i].key;
				right_block->next_level_id = right_block->entry[0].BID;
			}

			
			right_block->entry[i].key = right_block->entry[i + 1].key;
			right_block->entry[i].BID = right_block->entry[i + 1].BID;


		}



		fstream open(bin_file_name, ios::in | ios::out | ios::binary); //left, right block  정보를 bin파일에 저장
		open.seekp(real_block_location(left_block->block_id, blocksize), ios::beg);


		open.write(reinterpret_cast<char *>(&left_block->next_level_id), sizeof(int));

		//left
		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			open.write(reinterpret_cast<char *>(&left_block->entry[i].key), sizeof(int));
			open.write(reinterpret_cast<char *>(&left_block->entry[i].BID), sizeof(int));
		}

		//right
		open.seekp(real_block_location(right_block->block_id, blocksize), ios::beg);

		open.write(reinterpret_cast<char *>(&right_block->next_level_id), sizeof(int));

		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			open.write(reinterpret_cast<char *>(&right_block->entry[i].key), sizeof(int));
			open.write(reinterpret_cast<char *>(&right_block->entry[i].BID), sizeof(int));
		}

		open.close();

		if (block == root) //block이 root일때 새로운 non leaf node 생성후 헤더 변경
		{
			block = new Block(blocksize);
			block->check_leaf = false;
			block->next_level_id = left_block->block_id;
			block->block_id = seek_last_BID() + 1;
			root = block;
			root_BID = root->block_id;
			depth++;

			fstream open(bin_file_name, ios::in | ios::out | ios::binary);

			open.write(reinterpret_cast <char*> (&blocksize), sizeof(int));
			open.write(reinterpret_cast <char*> (&root_BID), sizeof(int));
			open.write(reinterpret_cast <char*> (&depth), sizeof(int));

			open.seekp(real_block_location(root->block_id, blocksize), ios::beg);

			open.write(reinterpret_cast<char*>(&root->next_level_id), sizeof(int));

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				open.write(reinterpret_cast<char *>(&root->entry[i].key), sizeof(int));
				open.write(reinterpret_cast<char *>(&root->entry[i].BID), sizeof(int));
			}

			open.close();

			parent = root;
			left_block->parent = parent;
			right_block->parent = parent;
			left_block->parent_BID = root_BID;
			right_block->parent_BID = root_BID;
			


		}
		else
		{

			if (parent->block_full())
			{
				parent = non_leaf_split(block, first_right_key);
				delete block;

			}

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				if (right_block->entry[0].key < parent->entry[i].key || parent->entry[i].key == 0)
				{
					parent->entry[i + 1] = parent->entry[i];
					parent->entry[i].key = right_block->entry[0].key;
					parent->entry[i].BID = right_block->block_id;
				}
			}

			fstream open(bin_file_name, ios::in | ios::out | ios::binary);
			open.seekp(real_block_location(parent->block_id, blocksize), ios::beg);

			open.write(reinterpret_cast<char *>(&parent->next_level_id), sizeof(int));

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				open.write(reinterpret_cast<char *>(&parent->entry[i].key), sizeof(int));
				open.write(reinterpret_cast<char *>(&parent->entry[i].BID), sizeof(int));
			}

			open.close();
		}

		if (first_right_key > key)
		{
			return left_block;
		}

		else
		{
			return right_block;
		}

	}


	Block *leaf_split(Block* block, int key)
	{
		Block *parent = block->parent;
		Block *left_block = new Block(blocksize);
		Block *right_block = new Block(blocksize);

		left_block->parent_BID = block->parent_BID;
		right_block->parent_BID = block->parent_BID;
		
		left_block->check_leaf = true;
		right_block->check_leaf = true;

		right_block->block_id = seek_last_BID() + 1;
		cout << "seek_last_BID() + 1; " << seek_last_BID() + 1 << endl;
		right_block->next_id = block->next_id;
		left_block->next_id = right_block->block_id;

	


		if (real_block_size(blocksize) % 2 == 0) //blocksize entry가 짝수일때
		{
			for (int i = 0; i < real_block_size(blocksize); i++) 
			{
				if (i < real_block_size(blocksize) / 2)
				{
					left_block->entry[i] = block->entry[i]; //left에 할당
					

				}

				else
				{
					right_block->entry[i - (real_block_size(blocksize)/2)] = block->entry[i]; //right에 할당
				}
			}
		}


		else //entry 개수가 홀수일때
		{
			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				if (i < real_block_size(blocksize) / 2)
				{
					left_block->entry[i] = block->entry[i]; //left에 할당
				}

				else
				{
					right_block->entry[i - (real_block_size(blocksize/2)-1)] = block->entry[i];  //right에 할당
				}
			}
		}

		cout << "1 ";
		for (int i = 0; i < real_block_size(blocksize); i++) {
			cout << left_block->entry[i].key << " " << left_block->entry[i].value << " / ";
		}
		cout << left_block->next_id << endl;
		cout << "2 ";
		for (int i = 0; i < real_block_size(blocksize); i++) {
			cout << right_block->entry[i].key << " " << right_block->entry[i].value << " / ";
		}
		cout << right_block->next_id << endl;

		fstream open(bin_file_name, ios::in | ios::out | ios::binary); //left, right block  정보를 bin파일에 저장
		open.seekp(real_block_location(left_block->block_id, blocksize), ios::beg);
		
		//left
		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			open.write(reinterpret_cast<char *>(&left_block->entry[i].key), sizeof(int));
			open.write(reinterpret_cast<char *>(&left_block->entry[i].value), sizeof(int));
		}
		open.write(reinterpret_cast<char *>(&left_block->next_id), sizeof(int));

		open.close();

		open.open(bin_file_name, ios::in | ios::out | ios::binary);
		open.seekp(real_block_location(right_block->block_id, blocksize), ios::beg);

		//right
		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			open.write(reinterpret_cast<char *>(&right_block->entry[i].key), sizeof(int));
			open.write(reinterpret_cast<char *>(&right_block->entry[i].value), sizeof(int));
		}
		open.write(reinterpret_cast<char *>(&right_block->next_id), sizeof(int));

		open.close();

		if (block == root) //block이 root일때 새로운 non leaf node 생성후 헤더 변경
		{
			block = new Block(blocksize);
			block->check_leaf = false;
			block->next_level_id = left_block->block_id;
			block->block_id = seek_last_BID() + 1;
			cout << block->block_id << endl;
			root = block;
			root_BID = root->block_id;
			depth++;

			fstream open(bin_file_name, ios::in | ios::out | ios::binary);

			open.write(reinterpret_cast <char*> (&blocksize), sizeof(int));
			open.write(reinterpret_cast <char*> (&root_BID), sizeof(int));
			open.write(reinterpret_cast <char*> (&depth), sizeof(int));

			open.seekp(real_block_location(root->block_id, blocksize), ios::beg);

			open.write(reinterpret_cast<char*>(&root->next_level_id), sizeof(int));

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				open.write(reinterpret_cast<char *>(&root->entry[i].key), sizeof(int));
				open.write(reinterpret_cast<char *>(&root->entry[i].BID), sizeof(int));
			}

			open.close();

			parent = root;
			left_block->parent = parent;
			right_block->parent = parent;
			left_block->parent_BID = root_BID;
			right_block->parent_BID = root_BID;
			

		}

		else
		{
			if (parent->block_full())
			{
				parent = non_leaf_split(block, right_block->entry[0].key);
				delete block; //parent를 non leaf split함수의 return값으로 초기화

			}

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				if (right_block->entry[0].key < parent->entry[i].key || parent->entry[i].key == 0)
				{
					parent->entry[i + 1] = parent->entry[i];
					parent->entry[i].key = right_block->entry[0].key;
					parent->entry[i].BID = right_block->block_id;
				}
			}

			fstream open(bin_file_name, ios::in | ios::out | ios::binary);
			open.seekp(real_block_location(parent->block_id, blocksize), ios::beg);

			open.write(reinterpret_cast<char *>(&parent->next_level_id), sizeof(int));

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				open.write(reinterpret_cast<char *>(&parent->entry[i].key), sizeof(int));
				open.write(reinterpret_cast<char *>(&parent->entry[i].BID), sizeof(int));
			}

			open.close();

		}

		if (right_block->entry[0].key > key)
		{
			return left_block;
		}

		else
		{
			return right_block;
		}

	}

	Block *non_leaf_split()
	{

	}



void print() 
{
		ofstream output(bin_file_name, ios::trunc);
		queue<int> q;

		cout << "a" << endl;

		output << "<0>\n\n";

		if (depth > 0)
		{
			q.push(root->next_level_id);
			
				for (int i = 0; i < real_block_size(blocksize); i++)
				{
					if (root->entry[i].BID != 0)
					{
						q.push(root->entry[i].BID);
						output << root->entry[i].key << ", ";
					}

					else break;
				}
			}
			else
			{
				for (int i = 0; i < real_block_size(blocksize); ++i)
				{
					if (root->entry[i].key != 0)
					{
						output << root->entry[i].value << ", ";
					}

					else
					{
						output.seekp(-2, ios::cur);
						output << " \n";
						break;
					}
				}
			}

			long level(0), breath(0);

			while (!q.empty())
			{
				if (breath == 0)
				{
					breath = q.size();
					output.seekp(-2, ios::end);
					output << " \n\n<" << ++level << ">\n\n";
				}
				
				int BID = q.front(); q.pop();
				--breath;

				if (level < depth)
				{
					Block *v = find_non_leaf_node_by_BID(BID);
					q.push(v->next_level_id);

					for (int i = 0; i < real_block_size(blocksize); ++i)
					{
						if (v->entry[i].BID != 0)
						{
							q.push(v->entry[i].BID);
							output << v->entry[i].key << ", ";
						}
					}
		
					delete v;
				}
				else
				{
					Block *v = find_leaf_node_by_BID(BID);

					for (int i = 0; i < real_block_size(blocksize); ++i)
					{
						if (v->entry[i].value != 0)
						{
							output << v->entry[i].key << ", ";
						}
					}
	
					delete v;
				}
			}
			output.seekp(-2, ios::end);
			output << " \n";
			output.close();
			return;
}
	



	Block* find_non_leaf_node_by_BID(int BID)
	{
		Block *target = new Block(blocksize);
		read_non_leaf_node_by_BID(target, BID);
		return target;
	}

	Block* find_leaf_node_by_BID(int BID)
	{
		Block *target = new Block(blocksize);
		read_leaf_node_by_BID(target, BID);
		return target;
	}


	void read_leaf_node_by_BID(Block *target, int BID)
	{
		ifstream indexFile(bin_file_name, ios::in | ios::binary);

		indexFile.seekg(real_block_location(BID, blocksize), ios::beg);

		for (int i = 0; i < real_block_size(blocksize); ++i)
		{
			int key, value;
			indexFile.read(reinterpret_cast<char*>(&key), sizeof(int));
			indexFile.read(reinterpret_cast<char*>(&value), sizeof(int));
			if (key != 0)
				target->insert_leaf_entry(key, value);
		}
		indexFile.read(reinterpret_cast<char*>(&target->next_id), sizeof(int));
		target->block_id = BID;
		target->check_leaf = false;
		indexFile.close();
	}

	void read_non_leaf_node_by_BID(Block *target, int BID)
	{
		ifstream indexFile(bin_file_name, ios::in | ios::binary);
		indexFile.seekg(real_block_location(BID, blocksize), ios::beg);
		indexFile.read(reinterpret_cast<char*>(&target->next_level_id), sizeof(int));
		for (int i = 0; i < real_block_size(blocksize); ++i) {
			int key, BID;
			indexFile.read(reinterpret_cast<char*>(&key), sizeof(int));
			indexFile.read(reinterpret_cast<char*>(&BID), sizeof(int));
			if (key != 0)
				target->insert_non_leaf_entry(key, BID);
		}
		target->block_id = BID;
		target->check_leaf = true;
		indexFile.close();
	}

	




	int search(int key)
	{

		Block* leaf_block = root_block_read(root_BID);
		find_leaf_block(key, &leaf_block);

		int value = 0;

		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			if (leaf_block->entry[i].key == key)
			{
				value = leaf_block->entry[i].value;
				break;
			}
		}

		return value;
	}

	Block* example(int key, Block* leaf_block)
	{
		int depth_counter = 0;
		while (!leaf_block->check_leaf) //leaf blcok까지 내려가기
		{
			int BID = return_BID(key, leaf_block);
			leaf_block = return_block(leaf_block, BID, ++depth_counter);
		}
		return leaf_block;
	}

	int return_BID(int key, Block* leaf_block) {
		for (int i = 0; i < real_block_size(blocksize); i++)
		{

			if (key < leaf_block->entry[i].key && leaf_block->entry[i].key != 0) //해당 entry보다 key값이 작은 경우
			{
				if (i == 0) //해당 key가 해당 block에 첫번째 entry의 key값보다 작은 경우
				{
					return leaf_block->next_level_id;
				}

				else //해당 key가 해당 block에 첫번째 entry의 key값보다 큰 경우
				{
					return leaf_block->entry[i - 1].BID;
				}
			}

			else if (leaf_block->entry[i].key == 0)
			{
				return leaf_block->entry[i - 1].BID;
			}
		}
	}

	int* search(int startRange, int endRange)
	{

	}

	void find_leaf_block(int key, Block **leaf_block)
	{
		Block *tmp = root;

		for (int i = 0; i < depth - 1; i++)
		{
			int BID;
			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				if (tmp->entry[i].key != 0 && tmp->entry[i].key > key)
				{
					if (i != 0)
					{
						BID = tmp->entry[i - 1].BID;
						break;
					}
					BID = tmp->next_level_id;
					break;
				}

				else if (tmp->entry[i].key == 0)
				{
					BID = tmp->entry[i - 1].BID;
					break;
				}
			}

			ifstream open(bin_file_name, ios::in | ios::binary);
			open.seekg(real_block_location(BID, blocksize), ios::beg);
			open.read(reinterpret_cast<char*>(&tmp->next_level_id), sizeof(int));

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				int key;
				int BID;
				open.read(reinterpret_cast<char*>(&key), sizeof(int));
				open.read(reinterpret_cast<char*>(&BID), sizeof(int));
				if (key != 0)
				{
					allocation_non_leaf_block(tmp, key, BID);
				}
			}
			tmp->block_id = BID;
			tmp->check_leaf = false;
			open.close();
		}
		
		if (depth > 0) {
			int BID;
			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				if (tmp->entry[i].key != 0 && tmp->entry[i].key > key)
				{
					if (i != 0)
					{
						BID = tmp->entry[i - 1].BID;
						break;
					}
					BID = tmp->next_level_id;
					break;
				}

				else if (tmp->entry[i].key == 0)
				{
					BID = tmp->entry[i - 1].BID;
					break;
				}
			}

			ifstream _open(bin_file_name, ios::in | ios::binary);

			_open.seekg(real_block_location(BID, blocksize), ios::beg);

			for (int i = 0; i < real_block_size(blocksize); i++)
			{
				int key;
				int value;
				_open.read(reinterpret_cast<char*>(&key), sizeof(int));
				_open.read(reinterpret_cast<char*>(&value), sizeof(int));
				if (key != 0)
				{
					allocation_leaf_block(tmp, key, value);
				}
			}
			_open.read(reinterpret_cast<char*>(&tmp->next_id), sizeof(int));
			//tmp->block_id = BID;
			tmp->check_leaf = true;
			_open.close();
		}
		*leaf_block = tmp;
	}

	void allocation_leaf_block(Block* block, int key, int value)
	{
		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			if (block->entry[i].key == 0)
			{
				block->entry[i].key = key;
				block->entry[i].value = value;
				break;
			}
		}
	}

	void allocation_non_leaf_block(Block* block, int key, int BID)
	{
		for (int i = 0; i < real_block_size(blocksize); i++)
		{
			if (block->entry[i].key == 0)
			{
				block->entry[i].key = key;
				block->entry[i].BID = BID;
				break;
			}
		}
	}
};


void allocation_init(string filename)
{
	ifstream input(filename, ios::in | ios::binary);

	if (input.is_open())
	{

		input.read((char*)&blocksize, sizeof(int));
		input.read((char*)&root_BID, sizeof(int));
		input.read((char*)&depth, sizeof(int));

		
	}
	input.close();
}



// Test
int main(int argc, char* argv[])
{

	char command = argv[1][0];
	bin_file_name = argv[2];

	switch (command)
	{
	case 'c':
	{
		BTree *myBtree = new BTree(argv[2], atoi(argv[3]));
		std::ofstream os(argv[2], std::ios::binary|ios::trunc);

		int block_size = atoi(argv[3]);
		int root_id = 1;
		int depth = 0;
		os.write(reinterpret_cast<const char*>(&block_size), sizeof(int));
		os.write(reinterpret_cast<const char*>(&root_id), sizeof(int));
		os.write(reinterpret_cast<char*>(&depth), sizeof(int));
		os.close();
		break;
	}
	
	

	case 'i':	// insert records from [records data file], ex) records.txt
	{

		string line;
	

		BTree bt(argv[2], blocksize);

		allocation_init(argv[2]);

		ifstream record(argv[3], ios::in);
		
		if (record.is_open())
		{
			while (getline(record, line))
			{
				cout << "A" << endl;
				stringstream cutting(line);
				string key;
				string ID;

				getline(cutting, key, ',');
				getline(cutting, ID);
				bt.insert(atoi(key.c_str()), atoi(ID.c_str()));
			}

			
		}		
		record.close();

		
		

		break;
	}
	

	case 's':	// search keys in [input file] and print results to [output file]
	{
		string line;


		BTree bt(argv[2], blocksize);

		allocation_init(argv[2]);

		ifstream record(argv[3], ios::in);
		ofstream output(argv[4], ios::out);

		if (record.is_open())
		{
			while (getline(record, line))
			{
				int value = bt.search(atoi(line.c_str()));

				output << value << "\n";
			}




		}
		record.close();
	}
		break;

	case 'r':	// search keys in [input file] and print results to [output file]
	{
		int blocksize = 0;
	}
		break;

	case 'p':	// print B+-Tree structure to [output file]
	{
		BTree bt(argv[2], blocksize);
		output = argv[3];
		bt.print();

	}
		break;
	}

	return 0;
}

