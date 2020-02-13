class BTree
{
	public:
		Btree(const char *fileName, int blockSize);
		bool insert(int key, int rid);
		void print();
		int* search(int key); // point search
		int* search(int startRange, int endRange); // range search


	private:
		Btree(const char *fileName, int blockSize)
		{

		}

		bool insert(int key, int rid)
		{

		}

		void print()
		{

		}

		int* search(int key)
		{

		}

		int* search(int startRange, int endRange)
		{
			
		}
};

// Test
int main (int argc, char* argv[])
{
	char command = argv[1][0];
	BTree myBtree = new BTree(any parameter);

	switch(command)
	{
		case 'c' :	// create index file
		break;

		case 'i' :	// insert records from [records data file], ex) records.txt
		break;

		case 's' :	// search keys in [input file] and print results to [output file]
		break;

		case 'r' :	// search keys in [input file] and print results to [output file]
		break;

		case 'p' :	// print B+-Tree structure to [output file]
		break;
	}
}